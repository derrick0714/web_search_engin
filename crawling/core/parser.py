'''
Created on Feb 6, 2013

@author: Adam57
'''
from models.html import Html 
from include.thread_pool import ThreadPool
from include.log import Log
from include.setting import Setting
from strategies.linksextractor import LinksExtractor
from models.safe_queue import SafeQueue
import urllib, formatter
#import re


class Parser(object):
   
    def __init__(self, num_thread):
        self._num_threads = num_thread
        self._parse_workers = ThreadPool(num_thread)
        self._log = Log()      
        self._links = []
        self._format = formatter.NullFormatter()
        self._htmlparser = LinksExtractor(self._format)
        
    def queue_parse_task(self, html_task, callback):
        """assign the tasks(function, parameter, and callback) to the workers(thread pool)"""
        self._parse_workers.queue_task(self.parse_page, html_task, callback)

    def start(self):
        self._parse_workers.start()

    def stop(self):
        self._parse_workers.stop()
    
    def parse_page(self, html_task, callback):
        
        #format = formatter.NullFormatter()       
        self._htmlparser.feed(html_task._data)
        self._htmlparser.close()
        links = self._htmlparser.get_links()
        
        """for i in re.findall(b'''href=["'](.[^"']+)["']''', html_task._data, re.I): 
            print(i.decode("utf-8"))       
#            self._log.info(i)
            
            html_tasks = Html(i.decode("utf-8"))      
            callback(html_tasks)
        """
        for link in links:
            print (link)
            html_tasks = Html(link)
            callback(html_tasks)
        
        
