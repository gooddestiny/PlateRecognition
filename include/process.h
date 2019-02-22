#ifndef PROCESS_H
#define PROCESS_H
#include<opencv2/core.hpp>

#include"cppheader.h"
#include"common.h"

using namespace cv;



void clearLiuDingOnly(Mat &img);

Mat ColorMatch(const Mat &src, Mat &match, const Color r, const bool adaptive_minsv);
//const atuo BuildKv(const string &str);

bool calcSafeRect(const RotatedRect &roi_rect, const Mat &src, Rect_<float> &safeBoundRect);

bool bFindLeftRightBound(Mat &bound_threshold, int &posLeft, int &posRight);

Mat scaleImage(const Mat &image, const Size &maxSize, double &scale_ratio);

void spatial_ostu(InputArray _src, int grid_x, int grid_y, Color type = BLUE);

bool ClearSimpleBlob(Mat &img);//清除图像里的小斑点

void ReAdjustRectSize(vector<Rect> &src, vector<Rect> &retrect, float adjustratio);//调整窗口大小

#endif