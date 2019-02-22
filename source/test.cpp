#include"test.h"
#include"location.h"
#include"char_identify.h"
#include"chars_recongnition.h"


//using namespace cv;

void TestPlate::test_plate_locate()// 车牌定位);
{
	cout << "test_plate_locate" << endl;
	const string file = "../resources/image/plate_locate.jpg";
	Mat src = imread(file);
	vector<Mat> ResultVec;

	CPlateLocation plate;

    plate.plateLocate(src, ResultVec);
	if (ResultVec.size() != 0) 
	{
		size_t num = ResultVec.size();
		for (size_t j = 0; j < num; j++) {
			Mat resultMat = ResultVec[j];
			imshow("plate_locate", resultMat);
			waitKey(0);
		}
		destroyWindow("plate_locate");
	}
	


}

void TestPlate::test_plate_judge()//车牌判断
{
}

void TestPlate::test_plate_detect()//车牌检测);
{
}

void TestPlate::test_chars_segment() //字符分隔);
{
	cout << "test_chars_segment" << endl;

	Mat src = imread("../resources/image/chars_segment.jpg");

	vector<Mat> resultVec;
	CCharsSegment plate;

	int result = plate.charsSegment(src, resultVec);
	if (result == 1) {
		size_t num = resultVec.size();
		for (size_t j = 0; j < num; j++)
		{
			Mat resultMat = resultVec[j];
			imshow("chars_segment", resultMat);
			waitKey(0);
		}
		destroyWindow("chars_segment");
	}
}
void TestPlate::test_chars_identify() //字符鉴别);
{
	cout << "test_chars_identify" << endl;

	Mat src = imread("../resources/image/chars_segment.jpg");

	vector<Mat> resultVec;
	CCharidentify plate;
	string plateLicense = "";

	int result =  plate.CharIdentify(src, plateLicense);
	if (result == 0) 
	{
		cout << "CharIdentify Result : " << plateLicense << endl;
	}
}
void TestPlate::test_chars_recognise() //字符识别);
{
}
void TestPlate::test_plate_recognize() //车牌识别);
{
}
void TestPlate::test_all()//测试全部);
{
}