#ifndef SVM_H
#define SVM_H
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include <opencv2/ml.hpp>

#include"cppheader.h"
#include"feature.h"

using namespace cv;
using namespace cv::ml;

typedef enum {
	Negative = 0,
	Positive = 1
}SvmLabel;

typedef struct
{
	string file;
	SvmLabel lable;
} SvmTrainItem;

/*********************************************************
类  名：CSvmTrain
描  述：分类训练
日  期：2018/12/27
**********************************************************/
class CSvmTrain
{
public:
	CSvmTrain();
	~CSvmTrain();
	CSvmTrain(const string folder, const string model_xml);

	void TrainModel();
	void GetTrainData(string folder);
	Ptr<TrainData> GetImgData();
private:
	const string svm_train_folder;
	string svm_model_xml;
	Ptr<SVM> svm;

	vector<SvmTrainItem> TestList;
	vector<SvmTrainItem> TrainList;

	SvmCallFunc ExtractFeature;

};


#endif