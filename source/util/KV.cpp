#include"KV.h"


KV::KV()
{

}


void KV::load(const string &file)
{
	this->clear();
	ifstream readtxt(file);
	assert(readtxt);

	if (readtxt.is_open())
	{
		string key, value;
		while (readtxt >> key>> value)
		{
			data_.insert(make_pair(key, value)); //保存拼音与中文的对应关系
		}	
	}
	/*
	map<string, string>::iterator iter = data_.begin();
	for (; iter != data_.end(); iter++)
	{
		cout << iter->first <<" "<< iter->second << endl;
	}
	*/

	readtxt.close();
}

string KV::get(const string &key = "")
{
	if (data_.find(key) != data_.end())
	{
		return data_[key];
	}
	cerr << "[KV] cannot find :" << key << endl;
	return "";
}

void KV::add(const string key, const string value)
{
	data_.insert(make_pair(key, value));
}

void KV::remove(const string &key)
{
	if (data_.find(key) != data_.end()) 
	{
		data_.erase(key);		
	}
	cerr << "[Kv] cannot find :" << key << endl;
}

void KV::clear()
{
	data_.clear();
}