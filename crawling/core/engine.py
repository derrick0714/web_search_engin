
"""
Created on Feb 2, 2013

@author: derrick

"""
from threading import Thread	    
from include import setting, status
from include.log import Log
from core.downloader import Downloader
from core.parser import Parser
from models.html import Html
from models.safe_queue import SafeQueue
from time import time, sleep,localtime,strftime
 
import os

class Engine(object):
	def __init__( self, setting ):
		self._seed 			= []
		self._istart		= False
		#self._stauts		= Status()
		self._downloader	= Downloader( int(setting.get_param("Downloader","Threadnum")) )
		self._parser		= Parser(int(setting.get_param("Parser","Threadnum")))
		"""Store the html objects to be downloaded by the downloader"""
		self._download_pool	= SafeQueue()
		"""Store the html objects to be parsed by the parser"""
		self._parse_pool	= SafeQueue()
		self.start_time		= time() # for 
		self.download_times	= 0 # for test
		self.parse_times 	= 0
		self._log 			= Log()


		"""init the path for saving data, if the folder don't exist, create it"""
		self._path			= setting.get_param("Downloader","SavePath")+"/"+ strftime('%Y-%m-%d', localtime())+"/"+ strftime('%H-%M-%S', localtime())+"/"
		print(self._path)
		if not os.path.exists(self._path):
   			os.makedirs(self._path)
		

		"""The target is the function passed in to run in the thread"""
		"""Those two threads keep checking and assigning jobs to the two thread pools"""
		self._downloader_pool_checker = Thread( target=self.download_pool_checker )
		self._parse_pool_checker = Thread( target=self.parse_pool_checker)
		
	"""Called by the engine, add the url from the user to the download pool"""
	def add_seed(self, url):
		self._seed.append(url)
		html_task = Html(url)
		self._download_pool.append(html_task)
		
	def start(self):
		self._istart = True
		self._downloader.start()
		self._parser.start()
		self._downloader_pool_checker.start()
		self._parse_pool_checker.start()


	def stop(self):
		self._istart = False
		self._downloader.stop()
		self._parse.stop()
		""""Those two checker threads will end when the thread who calls them ends"""
		self._downloader_pool_checker.join()
		self._parse_pool_checker.join()
		print ("Engine is stopping")

	def pause(self):
		pass

	def finish_download(self, html_task):
		self.download_times+=1

		"""caculate the path for saving files"""
		full_path = self._path+"[No.{0}]_".format(self.download_times)+".html"
		print("[No.{0}] time:{1:0.1f} http-status: {2} data-size: {3}byes url:{4}".format(self.download_times, time()-self.start_time,\
			html_task._return_code, html_task._data_size, html_task._url))

		"""save html data to files"""
		f= open(full_path, 'w')
		f.write(html_task._data)
		f.close()


		"""After downloading, pass the data(still using the html objects) to the parse pool"""
		self._parse_pool.append(html_task)
		


		
	def finish_parse(self, html_task):
		self.parse_times+=1
		"""After parsing, pass the urls to be downloaded to the download pool"""
		self._download_pool.append(html_task)
		
	
	def download_pool_checker(self):
		while (self._istart == True):
			new_download_task = self._download_pool.pop_left()
			"""If there is no task remain in the download pool, put the thread into sleep"""
			"""else pop the new task, and download it"""
			"""for the engine to get the result to put into the parse pool, we need to pass the function finish_download down as a callback"""
			if (new_download_task == None):
				sleep(0.1)
			else:
				self._downloader.queue_download_task(new_download_task , self.finish_download)

	def parse_pool_checker(self):
		while (self._istart == True):
			new_parse_task = self._parse_pool.pop_left()
			if (new_parse_task == None):
				#print("sleeping")
				sleep(0.1)
			else:	
				self._parser.queue_parse_task(new_parse_task, self.finish_parse)

				



		