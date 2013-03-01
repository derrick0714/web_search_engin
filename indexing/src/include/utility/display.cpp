/*Author: derrick*/

#include "display.h"
#include "time_ex.h"
//#include "conio.h"
#include <unistd.h>

using namespace std;
#pragma warning (disable:4996)

display*	display::_this = NULL;

display::display()
:_state(false)
,_progrma("")
,_version("")
,_extern("")
,_p_call_back(NULL)
{
	
}

display::~display()
{
	if( _this != NULL)
		delete _this;
	_this = NULL;
}

display* display::get_instance()
{
	if( _this == NULL )
		_this = new display;
	return _this;
}

void display::run()
{
	_state = true;

//	reg_commond("?","","for help");
	//reg_commond("error","","");
	_Time32.set_time_point();

	_System.create_thread(show , this);

	command();
}

void display::show(void* p)
{
	display *pthis = (display*)p;
	pthis->show();
}

void display::show()
{
	while(_state)
	{
		title();
	
		body();

		sleep(500);
	}
}

void display::title()
{
	char temp_show[255];
	sprintf(temp_show , "%s" , _progrma.c_str() );
	
	sprintf(temp_show , "%s | %s " , temp_show , _version.c_str());

	sprintf(temp_show , "%s | %s " , temp_show ,_Time32.get_span_string(_Time32.get_time_span()));

	if( _extern != "")
	sprintf(temp_show , "%s | %s " , temp_show , _extern.c_str());

	//SetConsoleTitle(temp_show);
	
}


void display::body()
{
	
}

void display::stop()
{
	_state = false;
}

void display::set_input_call_back(d_key_event* p_call_back , int type )
{
	_p_call_back	= p_call_back;
	_call_back_type	= type;
}

void display::command()
{
	if( _p_call_back == NULL)
	{
		while( _state )
		{
			sleep(50);
		}
		return;
	}
	
	char buf[255];
	string last_com;
	bool state = true;
	while( _state )
	{

		if( _call_back_type == 0 )
		{
			printf(">");
			scanf("%s" , buf);
			_p_call_back->input_event( buf );
		}
		else if ( _call_back_type == 1)
		{
			char c = getchar();
			_p_call_back->input_event( &c );
		}
		
	}
}

void display::reg_commond(char* com_name , char* describe)
{
	_commond_all[com_name] = describe;
}