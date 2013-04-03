#ifndef __SEARCHING_ALGORIM_H__
#define __SEARCHING_ALGORIM_H__
#include <iostream>
#include <fstream>
#include <string>
#include "models/Docmap.h"
#include "models/WordMap.h"
#include "result_ctrl.h"
#include "utility/gzip.h"
#include <vector>
#include "4ops.h"
//#include "vbyte.h"

using namespace std;


class SearchingAlgorim
{
public:
	SearchingAlgorim();
	~SearchingAlgorim();
public:
	void init_data();
	char* init_buffer_from_file(string file_name,int& size);
	void do_searching(string words);
private:
	DocMap 		_doc_map;
	WordMap		_word_map;
	ResultCrtl	_result;
	float 		k1;
	float 		b;
	int       	d_agv;
	int 		N;


};


#endif //__SEARCHING_ALGORIM_H__