from include import log


class Engine(object):
	def start(self):
		obj = log.Log()		
		obj.write( "engin start")

	def stop(self):
		obj = log.Log()	
		obj.write( "engin stop")

	def pause(self):
		obj = log.Log()	
		obj.write( "engin Log")