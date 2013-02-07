"""
Created on Feb 2, 2013

@author: derrick

This is a downloader
"""

from models.html import Html 
from include.thread_pool import ThreadPool
from include.log import Log
from include.setting import Setting
import urllib.request
import urllib.parse


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
		req = urllib.request.Request(html_task._url)
		data = urllib.request.urlopen(req)
		html_task._data = data.read()#.decode('utf-8')
		callback(html_task)

#test
if __name__ == "__main__":
	downloader = Downloader(Setting())
	print(downloader.download())