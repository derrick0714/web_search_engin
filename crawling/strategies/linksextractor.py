'''
Created on Feb 7, 2013

@author: Adam57
'''
import html.parser
import formatter
import urllib.request
import urllib

class LinksExtractor(html.parser.HTMLParser):
    
    def __init__(self,formatter):
        html.parser.HTMLParser.__init__(self, formatter)
        """for storing the hyperlinks"""
        self.links = []
        """override handler of <A..>...</A> tags"""
    def start_a(self,attrs):
        if len(attrs) > 0 :
            for attr in attrs :
                if attr[0]=="HREF" :
                    self.links.append(attr[1])
    def get_links(self):
        return self.links
                    
if __name__ == "__main__":
    
        format = formatter.NullFormatter()
        htmlparser = LinksExtractor(format)
        req = urllib.request.Request("http://cis.poly.edu/suel/")
        data = urllib.request.urlopen(req)
        htmlparser.feed(data.read().decode("utf-8"))
        htmlparser.close()
        links = htmlparser.get_links()
        print(links)
        
        
    

        