'''
Created on Feb 10, 2013

@author: Adam57
'''

import urllib2,urllib
import json

class SearchGoogle(object):
    def __init__(self, searchstr = 'NYU'):
        self._keywords = searchstr
        self._links = []
    def getURLs(self):
        for x in range(2):   
            start = x*5           
            url = ('https://ajax.googleapis.com/ajax/services/search/web'
                  '?v=1.0&q=%s&rsz=5&start=%s') % (urllib.quote(self._keywords),start)
            try:
                request = urllib2.Request(url, None)
                response = urllib2.urlopen(request)

                """Process the JSON string."""
                results = json.load(response)
                info = results['responseData']['results']
            except Exception,e:
                print e
            else:
                for minfo in info:
                    self._links.append(minfo['url'])
                    print(minfo['url'])
        return self._links        
                
if __name__ == "__main__": 
    contacter = SearchGoogle("NYU Courant")    
    print(contacter.getURLs())
    