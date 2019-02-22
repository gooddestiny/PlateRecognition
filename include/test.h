#ifndef TEST__H
#define TEST__H

//包含一些基本操作的头文件
#include"cppheader.h"


class TestPlate
{
public:
	 TestPlate(){};
	~TestPlate() {};
	void test_plate_locate(); // 车牌定位);
	void test_plate_judge(); //车牌判断);
	void test_plate_detect(); //车牌检测);
	void test_chars_segment(); //字符分隔);
	void test_chars_identify(); //字符鉴别);
	void test_chars_recognise(); //字符识别);
	void test_plate_recognize(); //车牌识别);
	void test_all(); //测试全部);



private:

};



#endif

