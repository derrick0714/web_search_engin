from core.engine import Engine
from include.setting import Setting
#from include.commond import Commond
from time import sleep
from core.searchgoogle import SearchGoogle


def main():
	#load setting
	setting = Setting()
	setting.load("config.ini")

	#start commond view

	#create crawler engin
	crawler_engine = Engine(setting)


	#start engine 
	crawler_engine.start( )

	keywords = "NBA HOUSTON"
	contacter = SearchGoogle(keywords)
	links = contacter.getURLs()

	#load seed info from config file

	for i in range(10):
		#crawler_engine.add_seed(links[i])
		print links[i]


	raw_input(" ")

	#stop engin 
	crawler_engine.stop()

if __name__ == "__main__":
	#main(sys.argv[1:])
	main()