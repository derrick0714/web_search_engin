'''
Created on Feb 2, 2013

@author: Adam
'''
import configparser

class setting(object):
              
    def get_section(self, section):
        conf = configparser.ConfigParser()
        conf.read("c:\\config.ini")
        return conf.items(section)
    
    def get_param(self, section, param):
        conf = configparser.ConfigParser()
        conf.read("c:\\config.ini")
        return conf.get(section,param)
    
    def set_param(self, section, param, new_value):
        conf = configparser.ConfigParser()
        conf.read("c:\\config.ini")
        conf.set(section, param, new_value)
        conf.write(open("c:\\config.ini", "w"))
        
    def add_param(self, section, new_param, new_value):
        conf = configparser.ConfigParser()
        conf.read("c:\\config.ini")
        conf.set(section, new_param, new_value)
        conf.write(open("c:\\config.ini", "w"))   

    
if __name__ == "__main__": 
    config = setting() 
    print (config.get_section("log"))
    config.set_param("log", "L1", "TEST")   
    print (config.get_section("log"))
    config.add_param("log","L4", "new") 
    print (config.get_section("log"))    
    print(config.get_param("strategies","S1"))
    
    
        