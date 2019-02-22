#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>


#include <algorithm>
#include <io.h>


#include"location.h"
#include"menu.h"
#include"common.h"
#include"svm.h"
//#include"locateprocess.h"

//#include"location.h"

using namespace cv;
const string to_search = "../TrainData/svm/has/test/";        //欲查找的文件，支持通配符
const string modelxml = "../model/test/svm.xml";        //欲查找的文件，支持通配符

//int main()
//{
//	CSvmTrain svm(to_search, modelxml);
//	svm.TrainModel();
//	return 0;
//}
#if 1
int main()
{
	PrintFile("../resources/text/main_menu.txt");  //主菜单
	cout << "请选择输入操作： " ;
	bool isRepeat = true;
	int SelectNum = 0;
	while (isRepeat)
	{
		isRepeat = false;
		cin >> SelectNum;  //选择操作类型
		switch (SelectNum)
		{
		case 1: testmain();  //测试选项(定位、检测、识别......)
			break;
		case 2:

		case 3: {
				CSvmTrain svm(to_search, modelxml);
				svm.TrainModel();
				break;
				}
			
		default:
			isRepeat = true;
			break;
		}


	}
	 waitKey();

	return 0;
}
#elif 0

int main()
{
	CPlateLocation lpr;//也可以LPR lpr(path);
	lpr.load("../resources/image/test.jpg");
	
	lpr.ShowSrcImage();
	lpr.processing();
	//PrintFile("../resources/text/main_menu.txt");
	waitKey();

	return 0;
}
#endif

