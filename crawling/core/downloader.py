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
		self.__task_queue_max = 10
		self.__workers_pool	 = ThreadPool(self.__num_threads,self.__task_queue_max)
		
	def download(self, resoure):
		self.__workers_pool.start()
	def stop(self):
		self.__workers_pool.start()

	def download_one(self, url):
		req = urllib.request.Request(url)
		data = urllib.request.urlopen(req)
		return data

	def get_pages(self):
		pass


#test
if __name__ == "__main__":
	downloader = Downloader(setting())
	print(downloader.download_one("http://cis.poly.edu/cs6913/"))