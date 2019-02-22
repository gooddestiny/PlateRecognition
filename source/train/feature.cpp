#include"feature.h"
#include "opencv2/objdetect.hpp"

void getHistomPlusColoFeatures(const Mat& image, vector<float> &feature) {
	// TODO
	Mat feature1, feature2;

	//检测窗口(64,128),块尺寸(16,16),块步长(8,8),cell尺寸(8,8),直方图bin个数9  ，需要修改
	HOGDescriptor *hog = new HOGDescriptor(Size(128, 32), Size(32, 32), Size(16, 16), Size(16, 16), 9);
	//vector<float>descriptors;//存放结果    为HOG描述子向量    
	hog->compute(image, feature, Size(1, 1), Size(0, 0)); //Hog特征计算，检测窗口移动步长(1,1)     
	//cout << "HOG描述子向量个数    : " << descriptors.size() << endl;

}