/*Author: derrick*/
#ifndef ___Time_H_
#define ___Time_H_

#pragma warning (push)
#pragma warning (disable:4996)
#pragma warning (disable:4244)
#include <memory.h>
#include <time.h>
#include <stdio.h>

const time_t _day	= 60 * 60 * 24;
const time_t _hour	= 60 * 60 ;
const time_t _min	= 60 ;

template <typename T>
class time_ex
{
public:
	time_ex(void):_time_point(0){memset(_time_format , 0 , 128);}
	~time_ex(void){}
public:
	void	set_time_point(){ _time_point = (T)time(NULL);}

	T		get_time_point(){ return _time_point;}

	T		get_time_span() { return (T)time(NULL) - _time_point ;}

	char*	get_span_string(T span_time)
	{

		int count = 0;
		time_t t = (time_t)span_time;

		*_time_format = '\0';
		if( t > _day && count < 2)
		{
			sprintf(_time_format , "%d day(s)" , t / _day);
			t = t % _day;
			count++;
		}
		if( t > _hour && count < 2)
		{
			sprintf(_time_format , "%s %02d hour(s)" ,_time_format , t / _hour);
			t = t % _hour;
			count++;
		}
		if( t > _min && count < 2)
		{
			sprintf(_time_format , "%s %02d min(s)" ,_time_format , t / _min);
			t = t % _min;
			count++;
		}
		if( count < 2)
		sprintf(_time_format , "%s %02d sec(s)" ,_time_format , t );

		return _time_format;
	}


	char*	get_time_string(T time)
	{
		time_t t = (time_t)time;
		tm* p = localtime(&t); 
		sprintf(_time_format , "%04d-%02d-%02d %02d:%02d:%02d" , p->tm_year + 1900 , p->tm_mon + 1
			, p->tm_mday , p->tm_hour , p->tm_min , p->tm_sec );
		return _time_format;
		
	}

	T		get_time_now()
	{
		return (T)time(NULL);
	}

private:
	char	_time_format[128];
	T		_time_point;
};
static time_ex<long>	_Time32;
static time_ex<time_t>	_Time64;

#pragma warning (pop)
#endif //___Time_H_