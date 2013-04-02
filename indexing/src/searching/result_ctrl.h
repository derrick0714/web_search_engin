#ifndef __RESULT_CTRL_H_
#define __RESULT_CTRL_H_

#include <string>
#include <iostream>
using namespace std;
struct STRU_RESULT
{
	std::string _url;
	std::string _title;
	std::string _round_text;
	float _bm25;
	void print()
	{
		cout<<_url<<endl;
		cout<<_title<<endl;
		cout<<_round_text<<endl;
		cout<<_bm25<<endl;
	}
	STRU_RESULT()
	{
		_url = "";
		_title = "";
		_round_text="";
		_bm25=0.0;
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
