#include "analysis_ctrl.h"

analysis_ctrl::analysis_ctrl()
{

}

analysis_ctrl::~analysis_ctrl()
{

}

bool analysis_ctrl::start()
{
   cout<<"i am start"<<endl;
    display::get_instance()->set_input_call_back(this);
    return true;
}

void analysis_ctrl::input_event( char* key )
{
	cout<<"there is a input:"<<key<<endl;

}

