"""
Created on Feb 5, 2013

@author: derrick

"""
#from queue import deque #python3.3
from collections import deque
from threading import Condition
from threading import Lock

class SafeQueue( object ):
	def __init__(self):
		self._data_queue = deque()
		self._lock  = Condition(Lock())


	def append(self, data ):
		self._lock.acquire()
		try:
			self._data_queue.append( data )
		finally:
			self._lock.release()
		

	def pop_left(self):
		self._lock.acquire()
		try:
			if ( len(self._data_queue) == 0 ):
				return None
			return self._data_queue.popleft()
		finally:
			self._lock.release()

	def clear(self):
		self._lock.acquire()
		try:
			self._data_queue.clear()
		finally:
			self._lock.release()
			
	def has_value(self,value):
			if value in self._data_queue:
				return True
			else:
				return False
