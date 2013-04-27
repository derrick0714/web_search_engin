/*Author: derrick*/
#ifndef D_LOCK_H
#define D_LOCK_H

#ifdef WIN32
#include <windows.h>


class win_lock
{
public:
	win_lock()
	{
		InitializeCriticalSection(&_section);
	}

	~win_lock()
	{
		DeleteCriticalSection(&_section);
	}

	void Enter()
	{
		
		 EnterCriticalSection(&_section);
	}
	
	void Leave()
	{
		LeaveCriticalSection(&_section);
	}

private:
	CRITICAL_SECTION	_section;
};


typedef win_lock lock;
#else
#include <pthread.h>

class linux_lock
{
public:
	linux_lock()
	{
		pthread_mutex_init(&_mutex, NULL);
	}

	~linux_lock()
	{
		pthread_mutex_destroy(&_mutex);
	}

	void Enter()
	{
		 pthread_mutex_lock(&_mutex);
	}
	
	void Leave()
	{
		pthread_mutex_unlock(&_mutex);
	}
private:
	 pthread_mutex_t _mutex;
};

typedef linux_lock lock;

#endif

class none_lock
{
public:
	none_lock(){}
	~none_lock(){}
	void Enter(){}
	void Leave(){}
};

class lock_helper
{
public:
	lock_helper(lock& alock) : _lock(alock)
	{
		
		_lock.Enter();
	}	
	~lock_helper()
	{
	
		_lock.Leave();
	}
private:
	lock& _lock;
};


#define LockHelper(T) lock_helper loHelper(T)


#endif //D_LOCK_H