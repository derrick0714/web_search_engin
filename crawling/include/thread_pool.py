
"""
Created on Feb 2, 2013

@author: derrick

This is a thread pool
"""
from queue import deque
from threading import Thread
from threading import Condition
from threading import Lock
from time import sleep

class Worker(Thread):
    """request new task to execute from ThreadPool"""

    def __init__(self, thread_pool, worker_id):
        """initial data and start myself as a new thread""" 
        Thread.__init__(self)
        self._pool          = thread_pool
        self._woker_id      = worker_id;
        self._is_dying      = False
        self._work_times    = 0
        self._rest_time     = 0.01
        

    def run(self):
        """ask and do works from task pool  """
        while (self._is_dying == False):
            func, args = self._pool.get_new_task()      
            if func == None: #no task, have a rest
                sleep(self._rest_time)
            else:
                try:
                    func(args)
                except (Exception) as e: 
                    print (e) #change to log in the further
                ++self._work_times

    def goaway(self):
        """ stop myself """
        self._is_dying = True;


class ThreadPool():
    """ Consuming tasks using threads in poll"""
    def __init__(self, threads_num, task_queue_max=None):
        self._threads_num   = threads_num
        self._tasks         = deque()
        self._threads       = []
        self._task_num      = 0
        self._task_lock     = Condition(Lock())
        self._thead_lock    = Condition(Lock())


    def start(self):
        """start all threads """
        self._thead_lock.acquire()
        try:
            for i in range(self._threads_num): 
                new_thread = Worker(self, i)
                self._threads.append(new_thread)
                #start new thread
                new_thread.start()
        finally:
            self._thead_lock.release()

    def stop(self):
        """stop all threads """
        self._thead_lock.acquire()
        try:
            for one_thread in self._threads: 
                one_thread.goaway()
            self._threads.clear()
            self._threads_num = 0
        finally:
            self._thead_lock.release()

        #clear the task
        self._task_lock.acquire()
        try:
            self._tasks.clear(); 
        finally:
            self._task_lock.release()

    def queue_task(self, task, args=None):
        self._task_lock.acquire()
        try:
            self._task_num += 1
            self._tasks.append((task, args))
        finally:
            self._task_lock.release()

    def get_new_task(self):
        self._task_lock.acquire()
        try:
            if (self._task_num <= 0):
                return ( None, None )
            else:
                self._task_num -= 1
                return self._tasks.popleft()
        finally:
            self._task_lock.release()

    

#test
if __name__ == "__main__":

    def test_task1(num):
        print("this is taks 1: do {0}".format(num))

    def test_task2(data):
        print("this is taks 2")

    pool = ThreadPool(3, 10)

    pool.start()
    for i in range(10):  
        pool.queue_task(test_task1,i)
        i += 1
    sleep(0.5)
    input('press any key to exit')
    pool.stop()

