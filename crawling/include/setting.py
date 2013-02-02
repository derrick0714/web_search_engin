'''
Created on Feb 2, 2013

@author: Adam
'''
import configparser

class setting(object):
              
    def get_strategies(self):
        conf = configparser.ConfigParser()
        conf.read("c:\\config.ini")
        return conf.items("strategies")
    
    def get_log(self):
        conf = configparser.ConfigParser()
        conf.read("c:\\config.ini")
        return conf.items("log")
    
    def get_thread(self):
        conf = configparser.ConfigParser()
        conf.read("c:\\config.ini")
        return conf.items("thread")
    
    def get_queue(self):
        conf = configparser.ConfigParser()
        conf.read("c:\\config.ini")
        return conf.items("queue")
    
if __name__ == "__main__": 
    config = setting() 
    print (config.get_log())
    
        