"""
Created on Feb 2, 2013

@author: derrick

This is a downloader
"""


from include.thread_pool import ThreadPool
from include.log import Log
import urllib.request
import urllib.parse


class Downloader(object):
	def __init__(self, num_thread):
	    self.__num_threads	  	 = num_thread
	    self._download_workers	 = ThreadPool(num_thread)
	    

	def queue_download_task(self, url, callback):
		result = self.download_page(url)
		#result = self._download_workers.queue_task(, url)
		callback( result )

	def start(self):
		 self._download_workers.start()

	def stop(self):
		 self._download_workers.stop()

	def download_page(sefl, url):
		req = urllib.request.Request(url)
		data = urllib.request.urlopen(req)
		return data.read().decode('utf-8')

	def get_pages(self):
		pass


#test
if __name__ == "__main__":

  downloader = Downloader(setting())
  print(downloader.download())