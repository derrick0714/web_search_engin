"""
Created on Feb 12, 2013

@author: derrick

"""
import MySQLdb
from include.log import Log
from inlcude.configuration import Configuration

class Databse(object):
	def __init__(self, config ):
		self._config 		= config._host



  	def execute(self, sql):
  		try: 
			conn = MySQLdb.connect(host=self._config._host,	# your host, usually localhost
                 user=self._config._user , # your username
                  passwd=self._config._passwd , # your password
                  db=self._config._db) # name of the data base
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

