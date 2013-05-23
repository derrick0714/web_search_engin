#ifndef __ANALYSIS_CTRL_
#define __ANALYSIS_CTRL_

#include "utility/display.h"
#include "utility/gzip.h"
#include "utility/path_finder.h"
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
	int  get_doc_id(std::string doc_name, std::string doc_path,std::string doc_title,std::string doc_url,std::string doc_location,int doc_date, int doc_len  );
	int  get_word_id(std::string word);
	bool parse_xml(std::string file_path, char* buf, int buf_len,std::string& title,string& url, string& location,int& date, int& doc_len);
	bool get_one_word(char* source, int& pos,string& str);
	bool get_new_info(char* source, int max, int& start_pos, std::string key_start, std::string key_end, string& content);
	int find(char* source, int max_len, int start, std::string key_words);
private:
	
	status			_status;
	std::string		_dataset_path;	
	int 			_file_now;
	int 			_file_start;
	int 			_file_end;
	int 			_doc_id;
	int 			_word_id;
	StreamBuffer* 	_intermediate;
	time_t 			_time_now ; 


	WordMap			_word_map;
	DocMap 			_docs_map;
	map<string,int>	_checker;
	PathFinder 		_finder;

};


#endif