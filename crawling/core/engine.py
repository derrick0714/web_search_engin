from include import log


class Engine(object):
	def start(self):
		obj = log.Log()		
		obj.write( "engine start")

	def stop(self):
		obj = log.Log()	
		obj.write( "engine stop")

	def pause(self):
		obj = log.Log()	
		obj.write( "engine Log")