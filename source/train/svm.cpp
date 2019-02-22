#include"svm.h"
#include"util.h"
#include "opencv2/objdetect.hpp"

const string  has_train = "../TrainData/svm/has/train/";
const string  has_test = "../TrainData/svm/has/test/";
const string  no_train = "../TrainData/svm/no/train/";
const string  no_test = "../TrainData/svm/no/test/";

CSvmTrain::CSvmTrain()
{
}

CSvmTrain::~CSvmTrain()
{
}

CSvmTrain::CSvmTrain(const string folder, const string model_xml)
	:svm_train_folder(folder), svm_model_xml(model_xml)
{
	this->ExtractFeature = getHistomPlusColoFeatures;  //重载特征提取函数
	this->GetTrainData(svm_train_folder);        //取得训练数据
}
void CSvmTrain::TrainModel()
{
	// Train the SVM
	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::C_SVC);
	svm->setKernel(SVM::LINEAR);
	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));

	if (TrainList.size() == 0)
	{
		cout << "Data Path error,Please check it" << endl;
	}

	cout << "Train SVM model begin ,Please wait ..." << endl;

	auto train_data = GetImgData();
	// 训练分类器
	svm->train(train_data);
	//保存模型
	svm->save(svm_model_xml);
	cout << "SVM Train have finshed" << endl;
}

void  CSvmTrain::GetTrainData(string folder)
{
	auto has_file_train_list = GetSubFile(has_train);
	std::random_shuffle(has_file_train_list.begin(), has_file_train_list.end());

	auto has_file_test_list = GetSubFile(has_test);
	std::random_shuffle(has_file_test_list.begin(), has_file_test_list.end());

	auto no_file_train_list = GetSubFile(no_train);
	std::random_shuffle(no_file_train_list.begin(), no_file_train_list.end());

	auto no_file_test_list = GetSubFile(no_test);
	std::random_shuffle(no_file_test_list.begin(), no_file_test_list.end());

	cout << " Collection img path ok ..." << endl;

	for (auto filepath : has_file_train_list)
		TrainList.push_back({filepath,Positive });

	for (auto filepath : no_file_train_list)
		TrainList.push_back({ filepath,Negative });

    for (auto filepath : has_file_test_list)
		TestList.push_back({ filepath,Positive });

	for (auto filepath : no_file_test_list)
		TestList.push_back({ filepath,Negative });

	cout << " Load Train and Test Data ok ..." << endl;
   
}

Ptr<TrainData> CSvmTrain::GetImgData()
{
	Mat samples;
	vector<int> responses;

	int ItemNum = TrainList.size();
	cout << "Train Data Number :" << ItemNum << endl;
	//data_mat为所有训练样本的特征向量组成的矩阵，行数等于所有样本的个数，列数等于HOG描述子维数
	//行、列、类型；第二个参数，即矩阵的列是由下面的descriptors的大小决定的，可以由descriptors.size()得到，且对于不同大小的输入训练图片，这个值是不同的   
	Mat data_mat = Mat::zeros(ItemNum, 11340, CV_32FC1);
	//类型矩阵,存储每个样本的类型标志      
	//labels_mat为训练样本的类别向量，行数等于所有样本的个数，列数等于1；暂时，后面会修改，比如样本0，就为0
	Mat label_mat = Mat::zeros(ItemNum, 1, CV_32SC1);

	Mat TrainImg = Mat(Size(136,36),CV_8UC3);

	//处理HOG特征   
	int i = 0;
	for (auto f : TrainList)
	{
		auto image = imread(f.file);
		if (!image.data) {
			cout<<" Invalid image: "<< f.file<<  "  ignore.\n"<<endl;
			continue;
		}
		vector<float>descriptors;//存放结果    为HOG描述子向量   

		resize(image , TrainImg, TrainImg.size());
		ExtractFeature(TrainImg, descriptors);

		for (int k = 0; k < descriptors.size(); k++)
		{
			data_mat.at<float>(i, k) = descriptors[k];
		}
		label_mat.at<int>(i, 0) = TrainList[i].lable;
		i++;
	}

	return cv::ml::TrainData::create(data_mat, cv::ml::SampleTypes::ROW_SAMPLE, label_mat);
}