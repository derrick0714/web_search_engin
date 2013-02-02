'''
Created on Feb 2, 2013

@author: Adam
'''
import re 
import urllib.request

textfile = open("c:\\depth_1.txt","wt")

for i in re.findall(b'''href=["'](.[^"']+)["']''', urllib.request.urlopen("http://cis.poly.edu/cs6913/").read(), re.I):
    print (i)
    textfile.write(i.decode("utf-8")+'\n')
    for ee in re.findall(b'''href=["'](.[^"']+)["']''', urllib.request.urlopen("http://cis.poly.edu/cs6913/"+i.decode("utf-8")).read(), re.I):
        print (ee)
        textfile.write(ee.decode("utf-8")+'\n')

textfile.close()