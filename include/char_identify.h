#ifndef CHARS_IDENTIFY_H
#define CHARS_IDENTIFY_H

#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>

#include"cppheader.h"
#include"process.h"

using namespace cv;

class CCharidentify
{
public:
	CCharidentify() {};
	~CCharidentify() {};
	int CharIdentify(Mat &src, string &plateLicense);
	string identifychinses(const Mat &src);
	string identifyEnglish(const Mat &src);
private:

};


#endif