from core.engine import Engine
from include.setting import Setting
#from include.commond import Commond
from time import sleep
from core.searchgoogle import SearchGoogle
from include.log import Log

def main():
	#load setting
	setting = Setting()
	setting.load("config.ini")

	try:	
		#create crawler engin
		crawler_engine = Engine(setting)


		#start engine 
		crawler_engine.start( )

		#load seed info from config file
		
		keywords = setting.get_param("seed","keywords") #"NBA HOUSTON"
		contacter = SearchGoogle(keywords)
		links = contacter.getURLs()

		print "key words:"+keywords
		print "Load 10 results from google search:"
		
		for i in range(10):		
			print ("[{0}]".format(i)+links[i])
		print""

		raw_input("press any key to start crawling")

		#append seeds, which from google search result, into engine 
		for i in range(10):
			crawler_engine.add_seed(links[i])

		raw_input("")
		#stop engin 
		crawler_engine.stop()

	except (Exception) as e:  
		Log().debug(e)
		crawler_engine.stop()
if __name__ == "__main__":
	#main(sys.argv[1:])
	main()