
"""
Created on Feb 2, 2013

@author: derrick

"""
from threading import Thread	    
from include import setting, status
from include.log import Log
from include.database import Databse
from core.downloader import Downloader
from core.parser import Parser
from models.html import Html
from models.safe_queue import SafeQueue
from models.safe_loop_array import SafeLoopArray
from models.safe_dic import SafeDictionary
from time import time, sleep,localtime,strftime
from core.searchgoogle import SearchGoogle
from strategies.robothandler import RobotHandler
from strategies.earlyvisithandler import EarlyVisitHandler
from strategies.cgihandler import CGIHandler
import os

class Engine(object):
	def __init__( self, setting ):
		self._istart		= False
		#self._stauts		= Status()
		self._setting		= setting
		self._downloader	= Downloader( int(self._setting.get_param("Downloader","Threadnum")) )
		self._parser		= Parser(int(self._setting.get_param("Parser","Threadnum")))
		"""Store the html objects to be downloaded by the downloader"""
		self._download_pool	= SafeQueue()
		"""Store the html objects to be parsed by the parser"""
		self._parse_pool	= SafeQueue()
		self.start_time		= time() # for 
		self.download_times	= 0 # for test
		self.parse_times 	= 0
		self._log 			= Log()
		self._keywords		= ""
		self._keywords_links= []
		self._result_num	= 0		
		
		"""---strategies---"""
		self._earlyvisithandler = EarlyVisitHandler()
		self._robothandler  =RobotHandler()
		self._cgihandler	=CGIHandler()				
		"""---strategies---"""

		self._last_log		= SafeLoopArray( Html("#"),10)
		"""init the path for saving data, if the folder don't exist, create it"""
		self._path			= self._setting.get_param("Downloader","SavePath")+"/"+ strftime('%Y-%m-%d', localtime())+"/"+ strftime('%H-%M-%S', localtime())+"/"
		if not os.path.exists(self._path):
			os.makedirs(self._path)

		#self._database		= Databse(self._setting)

		"""The target is the function passed in to run in the thread"""
		"""Those two threads keep checking and assigning jobs to the two thread pools"""
		self._downloader_pool_checker = Thread( target=self.download_pool_checker )
		self._parse_pool_checker = Thread( target=self.parse_pool_checker)
		"""every second, this thread post runtime info to remote mysql"""
		#self._status_update = Thread( target=self.status_update)

		
		

	def load_seeds(self):
		#load seed info from config file	
		self._keywords = self._setting.get_param("seed","keywords") #"NBA HOUSTON"
		self._result_num = int(self._setting.get_param("seed","result_num"))
		contacter = SearchGoogle(self._keywords, self._result_num)
		self._keywords_links = contacter.getURLs()
		#append seeds, which from google search result, into download pool

		i = 0
		for url in self._keywords_links:
			if i < self._result_num:
				html_task = Html(url)
				self._download_pool.append(html_task)
				'''If use the following two line of code, then the program won't run, which means checking for revisit works'''
				'''however, the dic should be safe with a lock'''
				#self._visited_dic[html_task._md5] = html_task._url 
				#print(len(self._visited_dic))
			else:

				break
			i+=1

	def show_welcome(self):
		print("download folder:"+self._path)
		print "key words:"+self._keywords
		print "Load " +str(self._result_num)+" results from google search:"
		
		i = 0
		for url in self._keywords_links:
			if i < self._result_num:
				print ("[{0}]".format(i)+url)
			i+=1
		print""

		raw_input("press any key to start crawling, press second key to stop")


	def start(self):
		self._istart = True
		self.load_seeds()	#load seeds from google search 
		self.show_welcome()
		self._downloader.start()
		self._parser.start()
		self._downloader_pool_checker.start()
		self._parse_pool_checker.start()
		#self._status_update.start()
		
		
	def stop(self):
		self._istart = False
		""""clear download and parse popl"""
		self._download_pool.clear()
		self._parse_pool.clear()

		"""stop downloader and parser threads"""
		self._downloader.stop()
		self._parser.stop()
		""""Those two checker threads will end when the thread who calls them ends"""
		self._downloader_pool_checker.join()
		self._parse_pool_checker.join()
		#self._status_update.join()
		print ("Engine is stopping")

	def pause(self):
		pass

	def finish_download(self, html_task):
		self.download_times+=1

		"""caculate the path for saving files"""
		full_path = self._path+"[No.{0}]_".format(self.download_times)+".html"
		
		html_task._id = self.download_times
		print("[No.{0}] time:{1:0.1f} page:depth_parent {2}_{3} http-status: {4} data-size: {5}byes url:{6}".format(self.download_times,time()-self.start_time,html_task._depth,\
		html_task._parent,html_task._return_code, html_task._data_size, html_task._url))

		#add to log array, post to mysql
		self._last_log.add(html_task)

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
				
			elif (self._cgihandler.FindCGI(new_download_task._url)==True):
				print("Ingore the link contain cgi, this link is within page {0} , so don't download".format(new_download_task._parent), new_download_task._url)
				sleep(0.1)
			elif (self._earlyvisithandler.check_visited(new_download_task) == True):
				
				sleep(0.1)
			elif (self._robothandler.is_allowed(new_download_task) == False):
				print("Blocked by the Robot.txt, this link is within page {0} , so don't download".format(new_download_task._parent), new_download_task._url)			
				sleep(0.1)
			else:
				self._earlyvisithandler._visited_dic.addorupdate(new_download_task._md5, new_download_task._url)
				self._downloader.queue_download_task(new_download_task , self.finish_download)

	def parse_pool_checker(self):
		while (self._istart == True):
			new_parse_task = self._parse_pool.pop_left()
			if (new_parse_task == None):
				#print("sleeping")
				sleep(0.1)				
			else:												
				self._parser.queue_parse_task(new_parse_task, self.finish_parse)


	#~~~just for test~~~ see result at dengxu.me/websearch/test.php
	def status_update(self):

			
		sql = "UPDATE  `configuation` SET  `downloader_thread` =  {0} ,`downloader_folder`= '{1}', `parser_thread`= {2}, `seed_keywords`='{3}', `seed_resultnum`={4} WHERE  `configuation`.`id` =1".\
				format(self._setting.get_param("Downloader","Threadnum"), self._path, self._setting.get_param("Parser","Threadnum"),self._keywords,self._result_num)
		
		self._database.execute(sql)
		
		"""update result url"""
		sql = "DELETE FROM `key_words`"
		self._database.execute(sql)
		for links in self._keywords_links:
			sql = "INSERT INTO `web_search_engine`.`key_words` (`id`, `url`) VALUES (NULL, '{0}')".format(links)
			self._database.execute(sql)

		while (self._istart == True):
			sql = "UPDATE  `status` SET  `crawled_url_count` =  '{0}'  WHERE  `status`.`id` =1".format(self.download_times)
			self._database.execute(sql)


			for i in range(10):
				html_task = self._last_log.get(i)
				if html_task._url != "#":
					sql = "INSERT INTO `web_search_engine`.`log` (`url`, `download_time`, `data_size`, `code`, `parent`, `depth`)\
						VALUES ('{0}', now(), '{2}', '{3}', '{4}', '{5}')".format\
						(html_task._url, html_task._crawled_time, html_task._data_size, html_task._return_code, html_task._parent, html_task._depth)
					
					self._database.execute(sql)

			sleep(1)
	
		
   


