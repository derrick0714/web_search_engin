/*Author: derrick*/
#include "timer.h"

timer*	timer::_this	= NULL;
lock	timer::_instance_lock;

timer::timer()
:_reference( 0 )
,_is_close( false)
{

}

timer::~timer()
{

}

timer* timer::get_instance()
{
	LockHelper( _instance_lock );
	if( _this ==  NULL)
	{
		_this = new timer;
	}

	return _this;
}

void timer::do_register( func f , void* data ,  unsigned  short times)
{
	LockHelper( _list_lock );

	struct_func new_func;
	new_func._now		= 0 ;
	new_func._p_func	= f ;
	new_func._times		= times;
	new_func._data		= data;
	_func_list.push_back( new_func );

	if( _reference == 0 )
	{
		_is_close = false;
		_System.create_thread( thread , this);
	}

	++_reference;
}

void timer::do_unregister( func f )
{
	{
		LockHelper( _list_lock );
		std::list<struct_func>::iterator iter ; 
		for( iter = _func_list.begin() ; iter != _func_list.end() ; )
		{
			if((*iter)._p_func ==  f)
			{
				_func_list.erase( iter++ ); 
				
				_is_close = --_reference <= 0;
			
				break;
			}
			else
			{
				iter++;
			}
		}
	}

	if(_is_close)
	{
		LockHelper( _thread_lock );
	}
	
}

void timer::thread( void *p)
{
	((timer*)p)->thread();
}

void timer::thread()
{
	LockHelper( _thread_lock );

	while( !_is_close )
	{
		LockHelper( _list_lock );

		std::list<struct_func>::iterator iter = _func_list.begin(); 
		while( iter != _func_list.end() )
		{
			if( ++iter->_now >= iter->_times )
			{
				iter->_p_func(iter->_data);
				iter->_now = 0; 
			}
			iter++;
		}

		sleep(20);
	}
}