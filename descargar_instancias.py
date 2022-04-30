from bs4 import BeautifulSoup
import urllib.request

parser = 'html.parser'  # or 'lxml' (preferred) or 'html5lib', if installed
resp = urllib.request.urlopen("http://elib.zib.de/pub/mp-testdata/tsp/tsplib/tsp/index.html")
soup = BeautifulSoup(resp, parser, from_encoding=resp.info().get_param('charset'))

for link in soup.find_all('a', href=True):
	dir = link['href']
	if((".tsp" in dir) or (".opt.tour" in dir)):
		if(dir!='.tsp\"'):
			print(dir)
			path = "http://elib.zib.de/pub/mp-testdata/tsp/tsplib/tsp/" + str(dir)
			res = "./data/"+ str(dir)
			print(path)
			print(res)
			urllib.request.urlretrieve(path, res)