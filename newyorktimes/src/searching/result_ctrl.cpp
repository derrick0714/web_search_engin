#include "result_ctrl.h"

ResultCrtl::ResultCrtl()
{
	_max = 10;
	_now =0;
	_result = new STRU_RESULT[_max];

}
ResultCrtl::~ResultCrtl()
{
	if(_result != NULL)
		delete _result;
}

void ResultCrtl::clear()
{
	_now = 0;
}

void ResultCrtl::add_one(STRU_RESULT& res)
{
	if( _now >= _max)
		return;
	_result[_now++] = res;
}

void ResultCrtl::print()
{
//	for(int i = 0 ; i < _now; i++)
//		_result[i].print();
}