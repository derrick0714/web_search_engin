#ifndef __ANALYSIS_CTRL_
#define __ANALYSIS_CTRL_

#include "utility/display.h"
#include "utility/gzip.h"
#include "models/original_index.h"
#include "models/TempLexicon.h"
#include "models/WordMap.h"
#include "parser/parser.h"
#include "models/StreamBuffer.h"
#include "models/Docmap.h"
#include <ctime>

#include <string>


struct status
{
	int _deal_docs;
	int _deal_words;

	status()
	{
		_deal_docs = 0;
		_deal_words= 0;
	}
};

struct DataSet
{
	std::string	_index;
	std::string _data;
	std::string _path;
	int 		_file_num;

	DataSet(std::string path)
	{
		_path = path;
	}
	void set_num(int num)
	{
		_file_num = num;
		char temp[64] = {0};
		sprintf ( temp, "%d_index", num );
		_index = _path+temp;
		sprintf ( temp, "%d_data", num );
		_data = _path+temp;
	}
};

class analysis_ctrl : d_key_event
{
public:
	analysis_ctrl();
	~analysis_ctrl();

	bool start();
	void stop();

	/*key input callback*/
	void input_event( char* key );

private:
	void do_it();
	bool save_index(char* index_data, int len, original_index& index, int file_num);
	bool parse_data(char* html_data, int len, original_index& index);
	bool save_data(int doc_id, char* save_data, int len);
	bool get_next_file_name(DataSet& data_set);		//get next  file name
	int  get_doc_id(std::string doc_name,int file_num, int offset, int len);
	int  get_word_id(std::string word);
	bool parse();
	bool get_one_word(char* source, int& pos,string& str);


private:
	
	status			_status;
	std::string		_dataset_path;	
	int 			_file_now;
	int 			_file_start;
	int 			_file_end;
	int 			_doc_id;
	int 			_word_id;
	StreamBuffer* 	buffer;
	time_t 			_time_now ; 


	WordMap			_word_map;
	DocMap 			_docs_map;
	map<string,int>	_checker;

};


#endif