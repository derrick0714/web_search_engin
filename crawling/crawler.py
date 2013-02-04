from core.engine import Engine
from core.downloader import Downloader
from include.setting import Setting
from time import sleep


def main():
	#load setting
	setting = Setting()
	setting.load("config.ini")
	
	#create crawler engin
	crawler_engine = Engine(setting)

	
	#start engine 
	crawler_engine.start( )

	#load seed info from config file
	for i in range(100):
		crawler_engine.add_seed(setting.get_param('seed','first') )



	sleep(1)
	
	input('press any key to exit')
	#stop engin 
	crawler_engine.stop()
	
if __name__ == "__main__":
    main()
