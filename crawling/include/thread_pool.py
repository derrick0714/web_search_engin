
from queue import Queue
from threading import Thread
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
        
        #start new thread
        self.start()

    def run(self):
        """ask and do works from task pool  """
        while (self._is_dying == False):
            func, args = self._pool.get_new_task()        
            if func == None:
                sleep(self._rest_time)
            try:
                func(args)
            except (Exception) as e: 
                print (e) #change to log in the further

            self._work_times+=1

    def stop(self):
        """ stop myself """
        self._is_dying = True;


class ThreadPool():
    """ Consuming tasks using threads in poll"""
    def __init__(self, threads_num, task_queue_max):
        self._pool   = threads_num
        self._tasks  = []
        self.task_num = 0

        #start threads
        for i in range(threads_num): 
            Worker(self, i)

    def queue_task(self, task, args=None):
        self.task_num += 1
        self._tasks.append((task, args))

    def get_new_task(self):
        if --self.task_num == 0:
            return ( None, None )
        else:
            return self._tasks.pop()

#test
if __name__ == "__main__":

    def test_task1(num):
        print("this is taks 1: do num %")%int(num)

    def test_task2(data):
        print("this is taks 2")

    pool = ThreadPool(3, 10)

    for i in range(10): 
        pool.queue_task(test_task1,i)
        i += 1
