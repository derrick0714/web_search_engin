/*Author: derrick*/
#ifndef D_TIMER_H
#define D_TIMER_H

#include "lock.h"
#include "system_ex.h"
#include <list>

class timer
{
	typedef void (*func)(void*);

	struct struct_func
	{
		func			_p_func;
		unsigned short	_times;
		unsigned short	_now;
		void*			_data;
	};

private:
	timer();
	~timer();
public:
	static timer* get_instance();
	void do_register( func , void* ,  unsigned short times);
	void do_unregister( func );
private:
	static void thread( void *p);
	void thread();

private:
	static timer*			_this;
	static lock				_instance_lock;
	lock					_thread_lock;
	lock					_list_lock;
	bool					_is_close;
	int						_reference;
	std::list<struct_func>	_func_list;
	

};

#endif //D_TIMER_H