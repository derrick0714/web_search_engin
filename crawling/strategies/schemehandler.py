'''
Created on Feb 14, 2013

@author: Adam57
'''
class SchemeHandler(object):
    def SchemeChecker(self, html_task):
        
        #print (html_task._url, html_task._scheme, html_task._hostname, html_task._path, html_task._query_string)
        
        '''scheme white list'''
        if not html_task._scheme in ['http', 'https', ""]:
            #print(" html_task._scheme={0}".format(html_task._scheme))
            return False
        '''block #'''    
        if (html_task._hostname == None and html_task._path == ""):
            #print("no _scheme & _hostname ")
            return False
        
        return True