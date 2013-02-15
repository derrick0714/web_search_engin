"""
Created on Feb 13, 2013

@author: derrick

"""

from models.status import Status
from models.configuration import Configuration
from include.database import Database
from time import time

class DatabseManager(object):
	def __init__(self, config):
		self._database	= Database(config)
		

	"""
	def write_configuration(self, config):
		sql = "UPDATE\
		`configuation` SET  `downloader_thread` =  {0} ,`downloader_folder`= '{1}',\
		 `parser_thread`= {2}, `seed_keywords`='{3}', `seed_resultnum`={4} WHERE  `configuation`.`id` =1".\
				format(config._down_num, config.download_path, parser_thread, key_words, result_num)

		self._database.execute(sql)	
	"""	

	def write_status(self, status):
		sql = "UPDATE `web_search_engine`.`status` SET `crawled_url_count` = '{0}', `crawled_time` = '{1}', `crawled_size` = '{2}',\
		 `crawled_queue` = '{3}', `parse_count` = '{4}', `parse_queue` = '{5}', `parse_scheme_type` = '{6}', `parse_cgi` = '{7}',\
		  `parse_visited` = '{8}', `parse_robot` = '{9}', `parse_nestlv` = '{10}' WHERE `status`.`id` = 1;"\
			.format( status._download_times, time()-status._sys_start, status._download_size, status._download_queue,\
		 	status._parse_times, status._parse_queue, status._scheme_type, status._cgi, status._early_visit, status._robot, status._nestlv)
		 
		#print sql
		self._database.execute(sql)	
		

	def read_if_start(self):
		sql = "SELECT `is_start` FROM `configuation` WHERE `id` =1"

		result = self._database.execute(sql)	
		
		if(result != None):
			return result[0][0]
		else:
			return None

