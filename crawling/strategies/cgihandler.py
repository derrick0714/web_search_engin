'''
Created on Feb 13, 2013

@author: Adam57
'''
class CGIHandler(object):

    def FindCGI(self, url):
        if url.find("cgi")==-1:
            return False
        else:
            return True
