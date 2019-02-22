#ifndef KV_H
#define KV_H

#include"cppheader.h"


class KV {
public:
	KV();

	void load(const string &file);

	string get(const string &key);

	void add(const string key, const string value);

	void remove(const string &key);

	void clear();

private:
	std::map<string, string> data_;
};

#endif