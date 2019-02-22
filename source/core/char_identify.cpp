#include"char_identify.h"
#include"chars_recongnition.h"

int CCharidentify::CharIdentify(Mat &src, string &plateLicense)
{
	
	vector<Mat> resultVec;
	CCharsSegment plate;

	int result = plate.charsSegment(src, resultVec);

	if (result == 0) {
		size_t num = resultVec.size();
		for (size_t j = 0; j < num; j++)
		{
			Mat resultMat = resultVec[j];
			string str = "";
			if (j == 0)
			{
				str = identifychinses(resultMat);
			}
			else
			{
				str = identifyEnglish(resultMat);
			}
			plateLicense.append(str);
		}

	}
	
	return 0;// result;
}

string CCharidentify::identifychinses(const Mat &src)
{
	return "";
}

string CCharidentify::identifyEnglish(const Mat &src)
{
	return "";
}


