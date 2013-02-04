"""
Created on Feb 4, 2013

@author: derrick

"""
import hashlib

class Html(object):
	def __init__(self, url):
		self._url 			= url
		#self._url_hash 		= hashlib.sha256(url.encode('utf-8'))
		self._url_domian	= "" 
		self._data			= ""

		##other 
