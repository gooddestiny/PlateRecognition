#include"menu.h"
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>

#include"cppheader.h"
#include"common.h"
#include"test.h"



void testmain()
{
	shared_ptr<KV> kv(new KV);
	kv->load("../resources/text/province_map.txt");

	PrintFile("../resources/text/test_menu.txt");  //测试菜单
	cout << "请选择输入操作： ";

	bool isRepeat = true;
	int SelectNum = 0;
	while (isRepeat)
	{
		cin >> SelectNum;
		isRepeat = false;
		TestPlate Test;
		switch (SelectNum)
		{
		case 1: Test.test_plate_locate();
			break;
		case 2:Test.test_plate_judge(); //空，有待添加功能
			break;
		case 3:Test.test_chars_segment();
			break;
		case 4:Test.test_chars_identify();
			break;


			break;

		default:
			isRepeat = true;
			break;
		}

	}
}

