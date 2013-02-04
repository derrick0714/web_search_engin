
"""
Created on Feb 2, 2013

@author: derrick

"""
	    
	    
from include import log, setting, status
from core.downloader import Downloader
from core.parse import Parse
from queue import deque

class Engine(object):
	def __init__( self, setting ):
		self._seed 			= []
		#self._stauts		= Status()
		self._downloader	= Downloader( int(setting.get_param("Downloader","Threadnum")) )
		self._parse			= Parse()
		self._url_pool		= deque()

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

	def finish_download(self, data):
		print("finish download")


		