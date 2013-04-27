/*Author: derrick*/
#ifndef D_DISPLAY_H
#define D_DISPLAY_H

#include "system_ex.h"
#include <string>
#include <map>

class d_key_event
{
public:
	virtual void input_event( char* key ) = 0;
};


class display
{

private:
	display();
	~display();
public:
	static display* get_instance();
	void run();
	void set_input_call_back(d_key_event* p_call_back , int type = 0 );
	void stop();
private:
	static void show(void*);
	void show();
	void title();
	void body();
	void command();
	void reg_commond(char* com_name , char* describe);
public:
	std::string _progrma;
	std::string _version;
	std::string _extern;
private:
	bool				_state;
	int					_call_back_type;
	static display*		_this;
	d_key_event*		_p_call_back;	
	std::map<std::string , std::string> _commond_all;

};


#endif //D_DISPLAY_H