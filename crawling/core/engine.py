
"""
Created on Feb 2, 2013

@author: derrick

"""
	    
from threading import Thread	    
from include import log, setting, status
from core.downloader import Downloader
from core.parse import Parse
from models.html import Html
from models.safe_queue import SafeQueue
from time import time, sleep

class Engine(object):
	def __init__( self, setting ):
		self._seed 			= []
		self._istart		= False
		#self._stauts		= Status()
		self._downloader	= Downloader( int(setting.get_param("Downloader","Threadnum")) )
		self._parse			= Parse()
		self._download_pool	= SafeQueue()
		self._prase_pool	= SafeQueue()
		self.start_time		= time() # for 
		self.download_times	= 0 # for test

		self._downloader_pool_checker = Thread( target=self.download_pool_checker )
		self._prase_pool_cheker = Thread( target=self.prase_pool_cheker)
		

	def add_seed( self, url ):
		self._seed.append(url)
		html_task = Html(url)
		self._download_pool.append( html_task )
		
	def start(self):
		self._istart = True
		self._downloader.start()
		self._parse.start()
		self._downloader_pool_checker.start()
		self._prase_pool_cheker.start()


	def stop(self):
		self._istart = False
		self._downloader.stop()
		self._parse.stop()
		self._downloader_pool_checker.join()
		self._prase_pool_cheker.join()

	def pause(self):
		pass

	def finish_download(self, html):
		self.download_times+=1
		print("finish download:{0} {1}".format(self.download_times, time()-self.start_time))

	def finish_parse(self, html):
		#self.download_times+=1
		print("finish parse")
		
	
	
	def download_pool_checker(self):
		while ( self._istart == True):
			new_download_task = self._download_pool.pop_left()
			if ( new_download_task == None):
				sleep(0.1)
			else:
				self._downloader.queue_download_task( new_download_task , self.finish_download)

	def prase_pool_cheker(self):
		while ( self._istart == True):
			new_parse_task = self._download_pool.pop_left()
			if ( new_parse_task == None):
				sleep(0.1)
			else:
				self._parse.queue_parse_task( new_parse_task._url , self.finish_parse)

		
		#print(html._data)


		