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
	int len;
};

class original_index
{
public:
	bool put(int id, string url, int offset, int len)
	{
		if(_original_index.find(id) != _original_index.end())
			return false;
		original_index_content one;
		one.url = url;
		one.offset = offset;
		one.len = len;
		_original_index[id] = one;
	}
	bool get(int id, original_index_content & content)
	{
		if( _original_index.find(id) == _original_index.end())
			return false;	
		content = _original_index[id];
	}
	void set_to_start()
	{
		_it = _original_index.begin();
	}

	bool get_next(int& id,original_index_content& content)
	{
		if( _it == _original_index.end())
			return false;
		content = _it->second;
		id = _it->first;
		_it++;
		return true;
	}

private:
	//key=> doc_id
	//value original_index_content[ "html url", "doc offset start posistion", "data len"]
	map<int , original_index_content> _original_index;
	map<int , original_index_content>::iterator _it;
};

#endif //__ORIGINAL_INDEX_H__