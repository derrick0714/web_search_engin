from core.engine import Engine
from core.downloader import Downloader
from include.setting import setting

def main():
	a = Downloader(setting())
	#print(a.download_one("http://dengxu.me").read().decode('utf-8'))
	print (a.download_one("http://dengxu.me"))
	
if __name__ == "__main__":
    main()
