#pragma once
#ifndef FEATURE_H
#define FEATURE_H

#include<opencv2/core.hpp>
#include"cppheader.h"

using namespace cv;

//! 用于从车牌的image生成svm的训练特征features
typedef void(*SvmCallFunc)(const Mat& image, vector<float> &feature);

void getHistomPlusColoFeatures(const Mat& image, vector<float> &feature);

#endif
