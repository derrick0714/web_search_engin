from core.engine import Engine
from include.setting import Setting
#from include.commond import Commond
from time import sleep


def main():
	#load setting
	setting = Setting()
	setting.load("config.ini")

	#start commond view
	"""
	try:
		opts, args = getopt.getopt(argv,"hi:o:",["ifile=","ofile="])
	except getopt.GetoptError:
		print 'test.py -i <inputfile> -o <outputfile>'
		sys.exit(2)
	for opt, arg in opts:
		if opt == '-h':
			print 'test.py -i <inputfile> -o <outputfile>'
			sys.exit()
      	elif opt in ("-i", "--ifile"):
			inputfile = arg
		elif opt in ("-o", "--ofile"):
			outputfile = arg
	print 'Input file is "', inputfile
	print 'Output file is "', outputfile
"""
	#create crawler engin
	crawler_engine = Engine(setting)

	
	#start engine 
	crawler_engine.start( )

	#load seed info from config file
	for i in range(10):
		crawler_engine.add_seed(setting.get_param('seed','first') )


	input('')
	
	
	#stop engin 
	crawler_engine.stop()
	
if __name__ == "__main__":
	#main(sys.argv[1:])
	main()
ain()
