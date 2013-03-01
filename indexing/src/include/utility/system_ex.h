/*Author: derrick*/
#ifndef D_SYSTEM_H
#define D_SYSTEM_H

#ifdef WIN32
#include <atlbase.h>
class system_win
{
public:
	void create_thread(void(*progarm)(void*), void* parameter)
	{
		::CreateThread(NULL , 0 ,(LPTHREAD_START_ROUTINE)progarm ,parameter ,0 , NULL);
	}
	 
};

#else
#include <pthread.h>
class system_linux
{
	public:
	void create_thread(void(callback_func)(void*), void* param)
	{
		pthread_t thread;
		pthread_create(&thread, NULL , reinterpret_cast<void*(*)(void*)>(callback_func), param);
		//pthread_create(&thread, 0, &callback_func, 0);
	}

};

#endif



#ifdef WIN32
typedef system_win		_system;
#else
typedef system_linux	_system;
#endif

static _system _System;
#endif //D_SYSTEM_H