"""
Created on Feb 2, 2013

@author: derrick

This is a downloader
"""

import time
from models.html import Html 
from include.thread_pool import ThreadPool
from include.log import Log
from include.setting import Setting
import urllib #python2.7
#import urllib.request #python3.3
#import urllib.parse #python3.3


class Downloader(object):
	
	def __init__(self, num_thread):
		self._num_threads	  	 = num_thread
		self._download_workers	 = ThreadPool(num_thread)
		self._log = Log()

	def queue_download_task(self, html_task, callback):		
		"""assign the tasks(function, parameter, and callback) to the workers(thread pool)"""
		self._download_workers.queue_task(self.download_page , html_task , callback )


	def start(self):
		self._download_workers.start()

	def stop(self):
		self._download_workers.stop()

	def download_page(self, html_task, callback):
		#req = urllib.request.Request(html_task._url) #python3.3
		#data = urllib.request.urlopen(req) #python3.3
		#html_task._data = data.read()#.decode('utf-8') #python3.3

		"""pull html data,fill the info into html model"""
		netowrk_object 			= urllib.urlopen(html_task._url)
		html_task._data 		= netowrk_object.read()
		html_task._crawled_time = time.time() 
		html_task._return_code	= netowrk_object.getcode()
		html_task._data_size	= len(html_task._data)
		netowrk_object.close()

		callback(html_task)

