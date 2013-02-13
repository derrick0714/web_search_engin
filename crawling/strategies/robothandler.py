'''
Created on Feb 12, 2013

@author: Adam57
'''
from models.safe_dic import SafeDictionary
from strategies.robotexclusionrulesparser import RobotExclusionRulesParser

class RobotHandler(object):
    
    def __init__(self):
        self._hostname_pool =   SafeDictionary()
        self._user_agent = "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_8_2) AppleWebKit/537.17 (KHTML, like Gecko) Chrome/24.0.1312.57 Safari/537.17"
        
    def check_hostname(self, html_task):
        if  (self._hostname_pool.has_key(html_task._homesiteurl)==True):
            return True
        else: 
            return False
    def is_allowed(self,html_task):
        try:
            rerp = RobotExclusionRulesParser()
            if (self.check_hostname(html_task) == False):
                print ("home_site for Robot", html_task._homesiteurl)
                rerp.fetch(html_task._homesiteurl + "/robots.txt")
                self._hostname_pool.addorupdate(html_task._homesiteurl,rerp) 
            else:
                rerp = self._hostname_pool.valueofkey(html_task._homesiteurl)       
            return rerp.is_allowed(self._user_agent, html_task._url)                    
        except Exception:
            return True