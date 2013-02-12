'''
Created on Feb 6, 2013

@author: Adam57
'''
from models.html import Html 
from include.thread_pool import ThreadPool
from include.log import Log
from strategies.linksextractor import LinksExtractor
from models.safe_queue import SafeQueue
import urllib, formatter
#import re


class Parser(object):
   
    def __init__(self, num_thread):
        self._num_threads = num_thread
        self._parse_workers = ThreadPool(num_thread)

    def queue_parse_task(self, html_task, callback):
        """assign the tasks(function, parameter, and callback) to the workers(thread pool)"""
        self._parse_workers.queue_task(self.parse_page, html_task, callback)

    def start(self):
        self._parse_workers.start()

    def stop(self):
        self._parse_workers.stop()
    
    def parse_page(self, html_task, callback):
        
        links = []
        format = formatter.NullFormatter()
        htmlparser = LinksExtractor(format)
        try:     
            htmlparser.feed(html_task._data)
            htmlparser.close()
            links = htmlparser.get_links()
        except (Exception) as e:
            #print(html_task._data)
            Log().debug(e)
        finally:
            del html_task

        for link in links:
            #print (link)
            html_task = Html(link)

            """load all strategies to determine if this link can be download"""
            if self.parse_link( html_task ) == True:
                callback(html_task)

        
    def parse_link(self, html_task ):

        """
        simple filter of no _scheme & _hostname for test
        """
        if (html_task._scheme =="") | (html_task._hostname == ""):
            #print("no _scheme & _hostname ")
            return False

        """
        simple filter of type of scheme for test
        """
        if html_task._scheme !="http":
            #print(" html_task._scheme={0}".format(html_task._scheme))
            return False

        return True

        
