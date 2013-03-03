#ifndef __ORIGINAL_INDEX_H__
#define __ORIGINAL_INDEX_H__


#include <string>
#include <map>
#include <iostream>
using namespace std;

struct original_index_content
{
	string url;
	int offset;
};

class original_index
{
public:
	bool put(int id, string url, int offset)
	{
		if(_original_index.find(id) != _original_index.end())
			return false;
		original_index_content one;
		one.url = url;
		one.offset = offset;
		_original_index[id] = one;
	}
	bool get(int id, original_index_content & content)
	{
		if( _original_index.find(id) == _original_index.end())
			return false;	
		content = _original_index[id];
	}
	void show()
	{
		for (map<int , original_index_content>::iterator it=_original_index.begin(); it!=_original_index.end(); ++it)
    		std::cout << it->first << " => " << it->second.url << " "<<it->second.offset<<'\n';
	}

private:
	map<int , original_index_content> _original_index;
};

#endif //__ORIGINAL_INDEX_H__