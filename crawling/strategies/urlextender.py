'''
Created on Feb 14, 2013

@author: Adam57
'''
class URLExtender(object):
    def ExtendURL(self, child, parent):

      # if root folder
      if child._url[0] == '/':
        child.update_url(parent._homesiteurl + child._url)

      else :
        if parent._url[len(parent._url)-1] != '/':
          parent._url =  parent._url + '/'
        child.update_url(parent._url + child._url)
       		#print child._url 
      #print "extentd url: "+ parent._url + " *** "+child._url
     # child.update_url(parent._url + child._url)
       # child._url
    
