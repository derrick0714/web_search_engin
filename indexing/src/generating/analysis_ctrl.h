#ifndef __ANALYSIS_CTRL_
#define __ANALYSIS_CTRL_

#include "utility/display.h"
#include <iostream>
using namespace std;

class analysis_ctrl : d_key_event
{
public:
	analysis_ctrl();
	~analysis_ctrl();

	bool start();
	void stop();

	/*key input callback*/
	void input_event( char* key );

};


#endif