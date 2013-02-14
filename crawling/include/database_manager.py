"""
Created on Feb 13, 2013

@author: derrick

"""

class DatabseManager(object):
	def __init__(self, setting):
		self._setting	= setting
		self._database	= Databse(setting)
		


	def write_configuration(self, download_thread, download_path, parser_thread, key_words, result_num,Nestlevel):
		sql = "UPDATE  `configuation` SET  `downloader_thread` =  {0} ,`downloader_folder`= '{1}',\
		 `parser_thread`= {2}, `seed_keywords`='{3}', `seed_resultnum`={4} WHERE  `configuation`.`id` =1".\
				format(download_thread, download_path, parser_thread, key_words, result_num)

		self._database.execute(sql)		