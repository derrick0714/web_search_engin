"""
Created on Feb 2, 2013

@author: derrick

This is a downloader
"""

from models.html import Html 
from include.thread_pool import ThreadPool
from include.log import Log
import urllib.request
import urllib.parse


class Downloader(object):
	def __init__(self, num_thread):
	    self.__num_threads	  	 = num_thread
	    self._download_workers	 = ThreadPool(num_thread)
	    

	def queue_download_task(self, html_task , callback):

		self._download_workers.queue_task(self.download_page , html_task , callback )

		#callback( result )

	def start(self):
		 self._download_workers.start()

	def stop(self):
		 self._download_workers.stop()

	def download_page(sefl, html_task, callback):
		#print (html_task._url)
		req = urllib.request.Request(html_task._url)
		data = urllib.request.urlopen(req)
		html_task._data = data.read()#.decode('utf-8')
		#print (html_task._data)
		callback( html_task )



#test
if __name__ == "__main__":

  downloader = Downloader(setting())
  print(downloader.download())