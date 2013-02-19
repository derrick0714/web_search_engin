# Simple Crawler
The first project for Web Search Engine
<img src="https://raw.github.com/derrick0714/web_search_engin/master/crawling/docs/crawler_architecture.png" />

Filelist:
	
	readme.txt
	explain.txt
	config.ini								program parameters' configuraton
	crawler.py								main program
		
	core.engine.py							load config file and manage the parser queue and download queue
	core.downloader.py						downloader implementation assgins download tasks to thread pool
	core.parser.py							parser implementation assgins parse tasks to thread pool
	core.searchgoogle.py					Google search API implementation
	
	models.configuration.py					load all configurations from local file and remote mysql
	models.html.py							the data structure maintain the crawled page infomation
	models.safe_dic.py						implementation of dictionary with lock
	models.safe_queue.py					implementation of queue with lock
	models.safe_loop_array.py				implementation of array with lock
	models.status.py						system global variables
	
	include.database_manager.py				interact with remote mysql
	include.database.py						sql executer
	include.log.py							implementation of logger
	include.setting.py						read program parameters from local configuration file
	include.thread_pool.py					implementation of a thread pool		
	
	strategies.bookmarkhandler.py			handle page anchor
	strategies.cgihandler.py				block url address with cgi in it
	strategies.earlyvisithandler.py			block pages visited before
	strategies.filetypehandler.py			decide whether a page is crawable according to its MIME type
	strategies.linksextractor.py			extract links from a downloaded page
	strategies.nestlevelhandler.py			block pages exceed a cetain depth in a site
	strategies.omitindex.py					omit the part of 'index.htm','main.htm',etc with in a url
	strategies.robotexclusionrulesparser.py	a robot exclusion rules parser 
	strategies.robothandler.py				decide whether a page is crawable according to the robot.txt
	strategies.schemehandler.py				scheme whitelist
	strategies.urlextender.py				extend partial url
	
	www.
	
Program parameters:
	
The config.ini file contains runtime parameters:
	Downloader.Threadnum					The number of thread for download
	Downloader.SavePath						The directory stores the downloaded pages
	
	Parser.Threadnum						The number of thread for parse
	Parser.Nestlevel						The maximum depth of a page in a website
	
	seed.keywords							The search key words
	seed.result_num							The result num returned from the Google API
	
	Mysql.host								mysql hostname
	Mysql.user								mysql username
	Mysql.passwd							mysql passwprd
	Mysql.db								mysql database name
	
Desgin:
	
	# Engine 
	----------------------
		Engine is the main controller in the crawler.
		
			It has:
			-a downloader object and a parser object, 
			-two safe queues each for the download and parse tasks, 
			-a status object holding the global status variables for the crawler, 
			-a mysql manager, 
			-objects for every filter strategy,the safe dictionary within the object of earlyvisithandler actually maintains the tree structure of the visited url
			
		
		Once the Engine starts up:		
			-it first apply the filter rules to the seeds from the Google API, and then load the valid ones into the download queue;
			-it starts two threads each keep checking the download queue and parse queue, once a html task is found in the queues, it is then assigned to the downloader or the parser; 
			-The downloader will return html tasks to be parse and push them into the parse queue, and the parser will return the html tasks to be download and push them into the download queue;
			-it starts a thread keep checking the status of the crawler and post runtime info to remote mysql;
		
	
	# Parser
	----------------------
		Parser will assgin the parsing tasks passed from engine to the thread pool object it maintains
			
		Except applying filtering rules when loading seeds from Google API to download queue in the engine, we mainly apply all the filtering rules in parser:
			-robothandler 				check against robot exclusion rules through robot.txt, it maintains a dictionary,
										of which the key is the url's homesite, the value is a object of robotexclutionrulesparser.
			-earlyvisithandler			check against the url visited before, it maintains a dictionary,
										of which the key is the md5 hashcode of the url, the value is the url's corresponding html object.
			-cgihandler					block the url with cgi in it
			-bookmarkhandler			block the link of page anchor
			-filetypehandler			block the url according to the MIME type
			-nestlevelhandler			block url exceed a cetain depth in a site
			-omitindex					omit the part of 'index.htm','main.htm',etc with in a url
			-schemehandler				block the scheme outside the scheme whitelist
			-urlextender				return the complete url
	
	# Downloader
	----------------------
		Downloader will assgin the download tasks passed from engine to the thread pool object it maintains;
		
		The timeout is set as 2 secs, then it returns a exception;
		
		It saves download files to local directory
	
	# Html
	----------------------
		It stores the information of a certain url and its corresponding page data:
			_url 						initial url and the extended url
			_scheme						scheme of the url
			_hostname					hostname of the url
			_md5						md5 hash code of the url
			_id							download sequence
			_depth						distance to the initial seed
			_parent						parent Html object
			_return_code				200, 404, etc
			_data						text within the page
			_data_size					size of data
			_crawled_time				download time