#include "analysis_ctrl.h"
#include <iostream>
using namespace std;

analysis_ctrl::analysis_ctrl()
{

}

analysis_ctrl::~analysis_ctrl()
{

}

bool analysis_ctrl::start()
{
   
    display::get_instance()->set_input_call_back(this);
    _praser.parse();
    return true;
}

void analysis_ctrl::stop()
{
   	//stop display
    display::get_instance()->stop();

}

void analysis_ctrl::input_event( char* key )
{

	if( strcmp(key,"quit") == 0)
		stop();
	else
		cout<<"press 'quit' to exit"<<endl;
}

