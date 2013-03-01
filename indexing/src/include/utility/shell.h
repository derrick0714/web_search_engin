/*Author: derrick*/
#ifndef D_SHELL_H
#define D_SHELL_H

#include <string>
#include <deque>
//#include <conio.h>
#include "system_ex.h"

const int shell_backspace	= 8;
const int shell_tab			= 9;
const int shell_enter		= 13;

const int shell_arrow		= 224;
const int shell_up			= 72;
const int shell_down		= 80;
const int shell_left		= 75;
const int shell_right		= 78;

class shell
{
public :
	shell();
	~shell();
	void test();
	void start();
	void stop();
public:
	void reg_command( std::string cmd_text , ...);
private:
	static void fire_recv_thread(void *p);
	void thread_recv();
	void inster_command( int ch );
	//void 

	void show_ch(int ch);
	void show_current_command();
	void add_command();
	void backspace();
	void clear_line();

	void get_next_command();
	void get_prev_command();
private:
	std::deque<std::string>		_history_cmd;
	std::string					_current_cmd;
	unsigned short				_save_count;
	unsigned short				_cmd_pos;
	
};

#endif //D_SHELL_H