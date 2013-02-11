'''
Created on Feb 11, 2013

@author: Adam57
'''
import hashlib
'''
md5 = hashlib.md5() 
md5.update("why") 
print md5.hexdigest() 
print 'block_size:', md5.block_size
print 'digest_size:', md5.digest_size
md5.update("why")
print md5.hexdigest() 
print 'block_size:', md5.block_size
print 'digest_size:', md5.digest_size
'''
'''
a = hashlib.md5('same string').hexdigest()
print a
b = hashlib.md5('same string').hexdigest()
print b
c = hashlib.md5('diff string').hexdigest()
print c
d = hashlib.md5('diff  string').hexdigest()
print d
d = hashlib.md5('diff  string').hexdigest()
print d
'''
md5 = hashlib.md5()
md5.update("a"+"b")
print md5.hexdigest()

md51 = hashlib.md5()
md51.update("a")
print md51.hexdigest()
md51.update("b")
print md51.hexdigest()
