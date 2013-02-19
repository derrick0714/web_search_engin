CS 6913 Spring 2013
Web Search Engine
HomeWork 1

Xu Deng, Qi Wang

Filelist:
	
	readme.txt
	explain.txt
	config.ini						program parameters' configuraton
	crawler.py						main program
		
	core.engine.py						load config file and manage the parser queue and download queue
	core.downloader.py					downloader implementation assgins download tasks to thread pool
	core.parser.py						parser implementation assgins parse tasks to thread pool
	core.searchgoogle.py					Google search API implementation
	
	models.configuration.py					load all configurations from local file and remote mysql
	models.html.py						the data structure maintain the crawled page infomation
	models.safe_dic.py					implementation of dictionary with lock
	models.safe_queue.py					implementation of queue with lock
	models.safe_loop_array.py				implementation of array with lock
	models.status.py					system global variables
	
	include.database_manager.py				interact with remote mysql
	include.database.py					sql executer
	include.log.py						implementation of logger
	include.setting.py					read program parameters from local configuration file
	include.thread_pool.py					implementation of a thread pool		
	
	strategies.bookmarkhandler.py				handle page anchor
	strategies.cgihandler.py				block url address with cgi in it
	strategies.earlyvisithandler.py				block pages visited before
	strategies.filetypehandler.py				decide whether a page is crawable according to its MIME type
	strategies.linksextractor.py				extract links from a downloaded page
	strategies.nestlevelhandler.py				block pages exceed a cetain depth in a site
	strategies.omitindex.py					omit the part of 'index.htm','main.htm',etc with in a url
	strategies.robotexclusionrulesparser.py			a robot exclusion rules parser 
	strategies.robothandler.py				decide whether a page is crawable according to the robot.txt
	strategies.schemehandler.py				scheme whitelist
	strategies.urlextender.py				extend partial url
	
	www.
	
Program parameters:
	
The config.ini file contains runtime parameters:
	Downloader.Threadnum					The number of thread for download
	Downloader.SavePath					The directory stores the downloaded pages
	
	Parser.Threadnum					The number of thread for parse
	Parser.Nestlevel					The maximum depth of a page in a website
	
	seed.keywords						The search key words
	seed.result_num						The result num returned from the Google API
	
	Mysql.host						mysql hostname
	Mysql.user						mysql username
	Mysql.passwd						mysql passwprd
	Mysql.db						mysql database name