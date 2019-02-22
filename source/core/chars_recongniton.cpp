#include"chars_recongnition.h"
#include"process.h"
	//! using ostu algotithm the segment chars in plate
int CCharsSegment::charsSegment(Mat input, vector<Mat>& resultVec, Color color )
{
	if (input.empty()) return 1;
	Mat input_grey;
	cvtColor(input, input_grey, COLOR_BGR2GRAY);

	Mat img_threshold;
	img_threshold = input_grey.clone();
	spatial_ostu(img_threshold, 8, 2, color);
	if(!ClearSimpleBlob(img_threshold)) return 2;

	Mat img_contours;
	img_threshold.copyTo(img_contours);
	vector<vector<Point>> contours;

	findContours(img_contours,contours, CV_RETR_EXTERNAL , CV_CHAIN_APPROX_NONE);
	vector<vector<Point>>::iterator ite = contours.begin();
	vector<Rect> vecRect;

	while (ite != contours.end())
	{
		Rect img = boundingRect(*ite);
		Mat auxRoi(img_threshold, img);

		if (verifyCharSizes(auxRoi)) vecRect.push_back(img);
		++ite;
	}
	if (vecRect.size() == 0) return 0x03;
	vector<Rect> sortedRect(vecRect);
	sort(sortedRect.begin(), sortedRect.end(),
		[](const Rect& r1, const Rect& r2) { return r1.x < r2.x; });

	vector<Rect> AdjustRect;
	float adjustratio = 1.15;
	ReAdjustRectSize(sortedRect, AdjustRect, adjustratio); //重新调整分割窗口大小

	for (int i = 0; i< AdjustRect.size(); i++)
	{
		Rect img = AdjustRect[i];
		Mat auxRoi(img_threshold, img);
		resultVec.push_back(auxRoi);
	}
	return 0;
}

	//! using methods to segment chars in plate
int CCharsSegment::charsSegmentUsingOSTU(Mat input, vector<Mat>& resultVec, vector<Mat>& grayChars, Color color )
{
	return 1;
}

int CCharsSegment::charsSegmentUsingMSER(Mat input, vector<Mat>& resultVec, vector<Mat>& grayChars, Color color )
{
	return 1;
}

	//! using project 
int CCharsSegment::projectSegment(const Mat& input, Color color, vector<int>& out_indexs)
{
	return 1;
}

bool CCharsSegment::verifyCharSizes(Mat r) {
	// Char sizes 45x90
	float aspect = 45.0f / 90.0f;
	float charAspect = (float)r.cols / (float)r.rows;
	float error = 0.7f;
	float minHeight = 10.f;
	float maxHeight = 35.f;
	// We have a different aspect ratio for number 1, and it can be ~0.2
	float minAspect = 0.05f;
	float maxAspect = aspect + aspect * error;
	// area of pixels
	int area = cv::countNonZero(r);
	// bb area
	int bbArea = r.cols * r.rows;
	//% of pixel in area
	int percPixels = area / bbArea;

	if (percPixels <= 1 && charAspect > minAspect && charAspect < maxAspect &&
		r.rows >= minHeight && r.rows < maxHeight)
		return true;
	else
		return false;
}

	// find the best chinese binaranzation method
void CCharsSegment::judgeChinese(Mat in, Mat& out, Color plateType)
{
}
void CCharsSegment::judgeChineseGray(Mat in, Mat& out, Color plateType)
{
}

Mat CCharsSegment::preprocessChar(Mat in)
{
	return Mat();
}

	//! to find the position of chinese
Rect CCharsSegment::GetChineseRect(const Rect rectSpe)
{
	return Rect();
}

	//! find the character refer to city, like "suA" A
int CCharsSegment::GetSpecificRect(const vector<Rect>& vecRect)
{
	return 1;
}

	//! Do two things
	//  1.remove rect in the left of city character
	//  2.from the city rect, to the right, choose 6 rects
int CCharsSegment::RebuildRect(const vector<Rect>& vecRect, vector<Rect>& outRect, int specIndex)
{
	return 1;
}

int CCharsSegment::SortRect(const vector<Rect>& vecRect, vector<Rect>& out)
{
	return 1;
}