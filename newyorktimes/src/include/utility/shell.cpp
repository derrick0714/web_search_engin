/*Author: derrick*/
#include "shell.h"
#include "iostream"
using namespace std;
#pragma warning ( disable:4996 )

shell::shell()
{
	_save_count = 50;
	_cmd_pos = 0;
	_history_cmd.resize(50,"");
}

shell::~shell()
{

}
void shell::test()
{
	start();
	
}

void shell::start()
{
	_System.create_thread( fire_recv_thread , this );
}

void shell::stop()
{

}

void shell::reg_command( std::string cmd_text , ...)
{
	
}

void shell::fire_recv_thread(void *p)
{
	((shell*)p)->thread_recv();
}

void shell::thread_recv()
{
	int ch;
	while( true )
	{

		ch = getchar();
		//printf("%d\r\n",ch);

		switch( ch )
		{
			case	shell_arrow		:	
				{
					ch = getchar();
					switch ( ch )
					{
						case	shell_up	:	get_prev_command();show_current_command();break;
						case	shell_down	:	get_next_command();show_current_command();break;
					}
					break;
				}
			case	shell_backspace	:	backspace();break;
			case	shell_tab		:	break;

			case	shell_enter		: show_ch(ch);inster_command(ch);add_command();break;
			default					: show_ch(ch);inster_command(ch);break;
		}
		
	}
}

void shell::show_ch(int ch)
{
	printf( "%c" , (char)ch );
}
void shell::show_current_command()
{
	clear_line();
	printf( "%s" , _current_cmd.c_str() );
}

void shell::add_command()
{
	_history_cmd[ ++_cmd_pos ] = _current_cmd ;
	_current_cmd = "";
	clear_line();
}
void shell::backspace()
{

}

void shell::get_next_command()
{
	if( _cmd_pos < _history_cmd.size() )
		_current_cmd = _history_cmd[ ++_cmd_pos] ;
}

void shell::get_prev_command()
{
	if( _cmd_pos > 1 )
		_current_cmd = _history_cmd[ --_cmd_pos] ;
}

void shell::inster_command( int ch )
{
	_current_cmd.push_back( (char)ch );
}

void shell::clear_line()
{
	printf("\r\t\t\t\t\t\r");
}