'''
Created on Feb 6, 2013

@author: Adam57
'''
from models.html import Html 
from include.thread_pool import ThreadPool
from include.log import Log
from include.setting import Setting
import urllib.request
import urllib.parse

class Parser(object):
   
    def __init__(self, num_thread):
        print("parser init")
        self._num_threads = num_thread
        self._parse_workers = ThreadPool(num_thread)
        self._log = Log()
        
    def queue_parse_task(self, html_task, callback):
        self._log.info("calling queue_parse_task")
        """assign the tasks(function, parameter, and callback) to the workers(thread pool)"""
        self._parse_workers.queue_task(self.parse_page, html_task, callback)

    def start(self):
        self._parse_workers.start()

    def stop(self):
        self._parse_workers.stop()
    
    def parse_page(self, html_task, callback):
        
        self._log.info(html_task._data)
        self._log.info("parsing pages")
        print("parsing pages")        
        callback(html_task)
        
        
