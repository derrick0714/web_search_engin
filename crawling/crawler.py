from core import engine
from core.downloader import Downloader
from include.setting import setting

def main():
	a = Downloader(setting())
	print(a.download_one("http://dengxu.me").read().decode('utf-8'))

if __name__ == "__main__":
    main()
