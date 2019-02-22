#pragma   once 
#ifndef __LOCATION_H__
#define __LOCATION_H__

#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>

//#include"cppheader.h"
#include"common.h"

using namespace cv;

class CPlate {
public:
	CPlate() {
		m_score = -1;
		m_plateStr = "";
		m_plateColor = UNKNOWN;
	}
	inline void setPlateMat(Mat param) { m_plateMat = param; }
	inline Mat getPlateMat() const { return m_plateMat; }

	inline void setPlatePos(RotatedRect param) { m_platePos = param; }
	inline RotatedRect getPlatePos() const { return m_platePos; }

	inline void setPlateColor(Color param) { m_plateColor = param; }
	inline Color getPlateColor() const { return m_plateColor; }

private:
	//! plate mat
	Mat m_plateMat;

	//! plate rect
	RotatedRect m_platePos;

	//! plate color type
	Color m_plateColor;

	//! plate license
	String m_plateStr;


	//! scale ratio
	float m_scale;

	//! plate likely
	double m_score;

};

class CPlateLocation {
public:
	CPlateLocation();

	~CPlateLocation() {};

	inline void setGaussianBlurSize(int param) { m_GaussianBlurSize = param; }
	inline int getGaussianBlurSize() const { return m_GaussianBlurSize; }

	inline void setMorphSizeWidth(int param) { m_MorphSizeWidth = param; }
	inline int getMorphSizeWidth() const { return m_MorphSizeWidth; }

	inline void setMorphSizeHeight(int param) { m_MorphSizeHeight = param; }
	inline int getMorphSizeHeight() const { return m_MorphSizeHeight; }

	
	int sobelSecSearch(Mat &bound, Point2f refpoint, vector<RotatedRect> &outRects);
	int sobelOperT(const Mat &in, Mat &out, int blurSize, int morphW, int morphH);
	int sobelSecSearchPart(Mat &bound, Point2f refpoint, vector<RotatedRect> &outRects);
	int plateSobelLocate(Mat src, vector<CPlate> &candPlates, int index);
	int sobelFrtSearch(const Mat &src, vector<Rect_<float>> &outRects);
	int sobelOper(const Mat &in, Mat &out, int blurSize, int morphW, int morphH);
	bool rotation(Mat &in, Mat &out, const Size rect_size, const Point2f center, const double angle);
	bool isdeflection(const Mat &in, const double angle, double &slope);
	void affine(const Mat &in, Mat &out, const double slope);
	bool VerifySizes(RotatedRect mr);
	int colorSearch(const Mat &src, const Color r, Mat &out,vector<RotatedRect> &outRects);

	int deskew(const Mat &src, const Mat &src_b, vector<RotatedRect> &inRects,
		vector<CPlate> &outPlates, bool useDeteleArea, Color color);
	int plateColorLocate(Mat src, vector<CPlate> &candPlates, int index =0);
	void plateLocate(Mat src, vector<Mat> &resultVec, int index =0);


	inline void setDebug(bool param) { m_debug = param; }


	inline bool getDebug() { return m_debug; }

private:
	Mat srcImage;//原图
	Mat gaussImage;//高斯滤波后的图像
	Mat sobelImage;//sobel计算后的图像
	Mat binImage;//二值化图像
	Mat closeImage;//闭运算后图像
	Mat markedImage;//标记

	vector<Point> maxArea;//最大区域

	float m_error;
	float m_aspect;

	int m_verifyMin;
	int m_verifyMax;

	int m_debug;
	int m_angle;

	int m_GaussianBlurSize;

	int m_MorphSizeWidth;
	int m_MorphSizeHeight;

};

class MyClasses
{
public:
	MyClasses() {};
	~MyClasses() {};

private:

};



#endif