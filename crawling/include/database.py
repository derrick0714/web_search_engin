import MySQLdb
from include.log import Log
from include.setting import Setting

class Databse(object):
	def __init__(self, setting):
		self._host 		= setting.get_param("Mysql","host")
		self._user  	= setting.get_param("Mysql","user")
		self._passwd  	= setting.get_param("Mysql","passwd")
		self._db 		= setting.get_param("Mysql","db")


  	def execute(self, sql):
  		try: 
			conn = MySQLdb.connect(host=self._host,	# your host, usually localhost
                 user=self._user , # your username
                  passwd=self._passwd , # your password
                  db=self._db) # name of the data base
			conn.autocommit(True)
			cur = conn.cursor()
			#sql="select * from `status`" 
			#print sql
  			cur.execute(sql)
			for row in cur.fetchall() :
   				 print row[1]
  		except (Exception) as e: 
  			Log().debug(e)
  			return False
  		finally:    
			if conn:    
				conn.close()
  		return True

