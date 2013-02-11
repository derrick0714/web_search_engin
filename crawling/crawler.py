from core.engine import Engine
from include.setting import Setting
#from include.commond import Commond
from time import sleep

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


		raw_input("")
		#stop engin 
		crawler_engine.stop()

	except (Exception) as e:  
		Log().debug(e)
		crawler_engine.stop()
if __name__ == "__main__":
	#main(sys.argv[1:])
	main()