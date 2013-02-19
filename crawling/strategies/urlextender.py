'''
Created on Feb 14, 2013

@author: Adam57
'''
class URLExtender(object):
    def ExtendURL(self, child, parent):

      count =0 
       # parent._url = parent._url
      if child._url[0] == '/':
        count += 1
      if parent._url[len(parent._url)-1] == '/':
        count += 1

      if(count == 2):	
        child._url = child._url[1:]
      if( count == 0):
        parent._url =  parent._url + '/'
       		#print child._url 
      #print "extentd url: "+ parent._url + " *** "+child._url
      child.update_url(parent._url + child._url)
       # child._url
        