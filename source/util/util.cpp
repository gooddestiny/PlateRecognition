#include"util.h"
#include<opencv2/core.hpp>
//#include<opencv2/imgproc.hpp>
//#include<opencv2/highgui.hpp>
#include <io.h>

using namespace cv;

void PrintFile(const string &file)   //打印文本
{
	ifstream reader(file);
	assert(reader);

	if (reader.is_open())
	{
		while (!reader.eof())
		{
			string line;
			getline(reader, line);
			if (line.empty()) continue;
			cout << line << endl;
		}
	}

	reader.close();
}

vector<string> GetSubFile(string path) //获取所有子目录的文件
{

	if (_access(path.c_str(),0) == -1)
	{
		cout << "path is error \n" << endl;
		return vector<string>();
	}
	//Directory dir;
	vector<string> SubFile;
	vector<String> files;     //存放文件路径  

	glob(path, files, true);     //读取文件夹下所有符合要求的文件路径

	for (int i = 0; i < files.size(); i++)
	{
		SubFile.push_back( files[i]);
		//cout << "第" << i + 1 << "个文件的路径是：" <<  files[i] << endl;
	}
	return SubFile;
}