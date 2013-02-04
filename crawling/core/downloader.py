"""
Created on Feb 2, 2013

@author: derrick

This is a downloader
"""


from include.setting import setting
from include.thread_pool import ThreadPool
from include.log import Log
import urllib.request
import urllib.parse


class Downloader:
	def __init__(self, setting):
	    self.__num_threads   = 3
	    self.__workers_pool	 = ThreadPool(self.__num_threads)
	    

	def download(self, resoure ):
		__workers_pool.start()
	def stop(self):
		__workers_pool.start()

	def download_one(sefl, url):
		req = urllib.request.Request(url)
		data = urllib.request.urlopen(req)
		return data.read().decode('utf-8')

	def get_pages(self):
		pass


#test
if __name__ == "__main__":

  downloader = Downloader(setting())
  print(downloader.download())