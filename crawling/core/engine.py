
"""
Created on Feb 2, 2013

@author: derrick

"""
	    
	    
from include import log, setting, status
from core.downloader import Downloader
from core.parse import Parse
from queue import deque
from models.html import Html 
from time import time

class Engine(object):
	def __init__( self, setting ):
		self._seed 			= []
		#self._stauts		= Status()
		self._downloader	= Downloader( int(setting.get_param("Downloader","Threadnum")) )
		self._parse			= Parse()
		self._url_pool		= deque()
		self.start_time		= time() # for 
		self.download_times	= 0 # for test


	def add_seed( self, url ):
		self._seed.append(url)
		self._downloader.queue_download_task( url, self.finish_download)
	def start(self):
		self._downloader.start()
		self._parse.start()

	def stop(self):
		self._downloader.stop()
		self._parse.stop()

	def pause(self):
		pass

	def finish_download(self, html):
		self.download_times+=1
		print("finish download:{0} {1}".format(self.download_times, time()-self.start_time))
		
	

		
		#print(html._data)


		