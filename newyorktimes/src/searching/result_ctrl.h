#ifndef __RESULT_CTRL_H_
#define __RESULT_CTRL_H_

#include <string>
#include <iostream>
using namespace std;
struct STRU_RESULT
{
	std::string _url;
	std::string _title;
	int _time;
	float _bm25;
	int _doc_id;
	int _pos;

	STRU_RESULT()
	{
		_url = "";
		_title = "";
		_time=0;
		_bm25=0.0;
		_doc_id=0;
		_pos=0;
	}
};

class ResultCrtl
{
public:
	ResultCrtl();
	~ResultCrtl();
public:
	void clear();
	void add_one(STRU_RESULT& res); 
	void print();
private:
	STRU_RESULT* 	_result;
	int 			_max;
	int 			_now;

};


#endif //__RESULT_CTRL_H_
