#ifndef __SEARCHING_ALGORIM_H__
#define __SEARCHING_ALGORIM_H__
#include <iostream>
#include <fstream>
#include <string>
#include "models/StreamBuffer.h"
using namespace std;


class SearchingAlgorim
{
public:
	SearchingAlgorim();
	~SearchingAlgorim();
public:
	void init_data();
	bool init_buffer_from_file(string file_name, StreamBuffer* buffer);
	//void do_searching(string key_word);
private:
	//DocMap 		_doc_map;
};


#endif //__SEARCHING_ALGORIM_H__