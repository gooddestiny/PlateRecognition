#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include"process.h"

void clearLiuDingOnly(Mat &img) {
	const int x = 7;
	Mat jump = Mat::zeros(1, img.rows, CV_32F);
	for (int i = 0; i < img.rows; i++) {
		int jumpCount = 0;
		int whiteCount = 0;
		for (int j = 0; j < img.cols - 1; j++) {
			if (img.at<char>(i, j) != img.at<char>(i, j + 1)) jumpCount++;

			if (img.at<uchar>(i, j) == 255) {
				whiteCount++;
			}
		}

		jump.at<float>(i) = (float)jumpCount;
	}

	for (int i = 0; i < img.rows; i++) {
		if (jump.at<float>(i) <= x) {
			for (int j = 0; j < img.cols; j++) {
				img.at<char>(i, j) = 0;
			}
		}
	}
}

Mat ColorMatch(const Mat &src, Mat &match, const Color r, const bool adaptive_minsv)
{

	// if use adaptive_minsv
	// min value of s and v is adaptive to h
	const float max_sv = 150;
	const float minref_sv = 64;
	const float minabs_sv = 64; //95;  大概率0.35~1

	// H range of blue 
	const int min_blue = 100;  // 100   颜色范围0~360度，为保存为8bit，数值分别减半
	const int max_blue = 140;  // 140

	// H range of yellow
	const int min_yellow = 15;  // 15
	const int max_yellow = 40;  // 40

	// H range of white
	const int min_white = 0;   // 15
	const int max_white = 30;  // 40

	Mat src_hsv;
	
	// convert to HSV space
	cvtColor(src, src_hsv, COLOR_BGR2HSV);

	vector<Mat> hsvSplit;

	split(src_hsv, hsvSplit);  
	equalizeHist(hsvSplit[2], hsvSplit[2]);   //直方图均衡化
	merge(hsvSplit, src_hsv);
	
	// match to find the color
	int min_h = 0;
	int max_h = 0;
	switch (r) 
	{
		case BLUE:
			min_h = min_blue;
			max_h = max_blue;
			break;
		case YELLOW:
			min_h = min_yellow;
			max_h = max_yellow;
			break;
		case WHITE:
			min_h = min_white;
			max_h = max_white;
			break;
		default:
			// Color::UNKNOWN
			break;
	}

	float diff_h = float((max_h - min_h) / 2);
	float avg_h = min_h + diff_h;

	int channels = src_hsv.channels();
	int nRows = src_hsv.rows;

	// consider multi channel image
	int nCols = src_hsv.cols * channels;
	if (src_hsv.isContinuous())    //判断是否连续存储
	{
		nCols *= nRows;
		nRows = 1;
	}
	float s_all = 0;
	float v_all = 0;
	float count = 0;

	for (int i = 0; i < nRows; ++i) {
		uchar* p = src_hsv.ptr<uchar>(i);
		for (int j = 0; j < nCols; j += 3) {
			int H = int(p[j]);      // 0-180
			int S = int(p[j + 1]);  // 0-255
			int V = int(p[j + 2]);  // 0-255

			//s_all += S;
			//v_all += V;
			//count++;

			bool colorMatched = false;

			if (H > min_h && H < max_h) 
			{
				float Hdiff = 0;
				if (H > avg_h)
					Hdiff = H - avg_h;
				else
					Hdiff = avg_h - H;

				float Hdiff_p = float(Hdiff) / diff_h;

				float min_sv = 0;
				if (true == adaptive_minsv)
					min_sv = minref_sv - minref_sv / 2 * (1 - Hdiff_p);  // inref_sv - minref_sv / 2 * (1 - Hdiff_p)
				else
					min_sv = minabs_sv;  // add

				if ((S > min_sv && S < max_sv) && (V > min_sv && V < max_sv))  //S与V 都需要满足要求
					colorMatched = true;
			}
			//依次扫描所有点，满足范围要求置1，则置0
			p[j] = 0;
			p[j + 1] = 0;
			if (colorMatched == true) 
			{
				p[j + 2] = 255;
			}
			else 
			{
				p[j + 2] = 0;
			}
		}
	}

	// get the final binary image
	Mat src_grey;
	vector<Mat> hsvSplit_done;
	split(src_hsv, hsvSplit_done);
	src_grey = hsvSplit_done[2];

	match = src_grey;

	return src_grey;
}

bool calcSafeRect(const RotatedRect &roi_rect, const Mat &src,Rect_<float> &safeBoundRect) 
{
	Rect_<float> boudRect = roi_rect.boundingRect();

	float tl_x = boudRect.x > 0 ? boudRect.x : 0;
	float tl_y = boudRect.y > 0 ? boudRect.y : 0;

	float br_x = boudRect.x + boudRect.width < src.cols
		? boudRect.x + boudRect.width - 1
		: src.cols - 1;
	float br_y = boudRect.y + boudRect.height < src.rows
		? boudRect.y + boudRect.height - 1
		: src.rows - 1;

	float roi_width = br_x - tl_x;
	float roi_height = br_y - tl_y;

	if (roi_width <= 0 || roi_height <= 0) return false;

	//  a new rect not out the range of mat

	safeBoundRect = Rect_<float>(tl_x, tl_y, roi_width, roi_height);

	return true;
}

bool bFindLeftRightBound(Mat &bound_threshold, int &posLeft, int &posRight) {


	float span = bound_threshold.rows * 0.2f;

	for (int i = 0; i < bound_threshold.cols - span - 1; i += 2) {
		int whiteCount = 0;
		for (int k = 0; k < bound_threshold.rows; k++) {
			for (int l = i; l < i + span; l++) {
				if (bound_threshold.data[k * bound_threshold.step[0] + l] == 255) {
					whiteCount++;
				}
			}
		}
		if (whiteCount * 1.0 / (span * bound_threshold.rows) > 0.36) {
			posLeft = i;
			break;
		}
	}
	span = bound_threshold.rows * 0.2f;


	for (int i = bound_threshold.cols - 1; i > span; i -= 2) {
		int whiteCount = 0;
		for (int k = 0; k < bound_threshold.rows; k++) {
			for (int l = i; l > i - span; l--) {
				if (bound_threshold.data[k * bound_threshold.step[0] + l] == 255) {
					whiteCount++;
				}
			}
		}

		if (whiteCount * 1.0 / (span * bound_threshold.rows) > 0.26) {
			posRight = i;
			break;
		}
	}

	if (posLeft < posRight) {
		return true;
	}
	return false;
}

Mat scaleImage(const Mat &image, const Size &maxSize, double &scale_ratio)
{
	Mat ret;

	if (image.cols > maxSize.width || image.rows > maxSize.height) {
		double widthRatio = image.cols / (double)maxSize.width;
		double heightRatio = image.rows / (double)maxSize.height;
		double m_real_to_scaled_ratio = max(widthRatio, heightRatio);

		int newWidth = int(image.cols / m_real_to_scaled_ratio);
		int newHeight = int(image.rows / m_real_to_scaled_ratio);

		cv::resize(image, ret, Size(newWidth, newHeight), 0, 0);
		scale_ratio = m_real_to_scaled_ratio;
	}
	else {
		ret = image;
		scale_ratio = 1.0;
	}

	return ret;
}

// this spatial_ostu algorithm are robust to 
// the plate which has the same light shine, which is that
// the light in the left of the plate is strong than the right.
void spatial_ostu(InputArray _src, int grid_x, int grid_y, Color type) {
	Mat src = _src.getMat();

	int width = src.cols / grid_x;
	int height = src.rows / grid_y;

	// iterate through grid
	for (int i = 0; i < grid_y; i++) {
		for (int j = 0; j < grid_x; j++) {
			Mat src_cell = Mat(src, Range(i * height, (i + 1) * height), Range(j * width, (j + 1) * width));
			if (type == BLUE) {
				threshold(src_cell, src_cell, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
			}
			else if ((type == YELLOW)||(type == WHITE)) {
				threshold(src_cell, src_cell, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY_INV);
			}
			else {
				threshold(src_cell, src_cell, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
			}
		}
	}
}

bool ClearSimpleBlob(Mat &img) 
{
	vector<float> fJump;
	int whiteCount = 0;
	const int x = 7;

	Mat jump = Mat::zeros(1, img.rows, CV_32F);
	for (int i = 0; i < img.rows; i++) {
		int jumpCount = 0;
		for (int j = 0; j < img.cols - 1; j++) {
			if (img.at<char>(i, j) != img.at<char>(i, j + 1)) jumpCount++;

			if (img.at<uchar>(i, j) == 255) 
			{
				whiteCount++;
			}
		}
		jump.at<float>(i) = (float)jumpCount; //记录每行黑白过度交替的次数
	}

	int iCount = 0;
	for (int i = 0; i < img.rows; i++) {
		fJump.push_back(jump.at<float>(i));
		if (jump.at<float>(i) >= 16 && jump.at<float>(i) <= 45) {

			// jump condition
			iCount++;
		}
	}

	// if not is not plate
	if (iCount * 1.0 / img.rows <= 0.40)  //水平方向黑白交替不足，可以判断不是车牌
	{
		return false;  
	}

	if (whiteCount * 1.0 / (img.rows * img.cols) < 0.15 ||
		whiteCount * 1.0 / (img.rows * img.cols) > 0.50) 
	{
		return false;    //白色前景过大或过小，都不是真正的车牌
	}

	for (int i = 0; i < img.rows; i++) //过滤不满足条件的水平条
	{
		if (jump.at<float>(i) <= x) {
			for (int j = 0; j < img.cols; j++) {
				img.at<char>(i, j) = 0;
			}
		}
	}
	return true;
}

void ReAdjustRectSize(vector<Rect> &src, vector<Rect> &retrect,float adjustratio)
{
	int MeanWidth  = 0;
	int MeanHeight = 0;
	int Meany = 0;
	for (int i = 0; i < src.size(); i++)
	{
		MeanWidth += src[i].width;
		MeanHeight += src[i].height;
		Meany += src[i].y;
	}
	MeanWidth = (((float)(MeanWidth) )/ src.size())*adjustratio; //求取最大概率的窗口大小
	MeanHeight = (((float)(MeanHeight)) / src.size())*adjustratio;
	Meany = (((float)(Meany)) / src.size());

	for (int i = 0; i < src.size(); i++)
	{
		Rect rec(src[i].x-1, Meany-2, MeanWidth, MeanHeight);
		retrect.push_back(rec);

	}

}
