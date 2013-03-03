#ifndef __ANALYSIS_CTRL_
#define __ANALYSIS_CTRL_

#include "utility/display.h"
#include "utility/gzip.h"
#include "models/original_index.h"

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

	DataSet(std::string path)
	{
		_path = path;
	}
	void set_num(int num)
	{
		char temp[64] = {0};
		sprintf ( temp, "down1_%d_index.gz", num );
		_index = _path+temp;
		sprintf ( temp, "down1_%d.gz", num );
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
	bool save_index(char* index_data, int len);
	bool save_data(char* html_data);
	bool get_next_file_name(DataSet& data_set);		//get next  file name
	int  get_new_doc_id();
	int  get_new_word_id();
	bool parse();
	void get_one_word(char* source, int& pos,string& str);


private:
	
	status			_status;
	std::string		_dataset_path;	
	int 			_file_num;
	int 			_doc_id;
	original_index _original_index;
};


#endif