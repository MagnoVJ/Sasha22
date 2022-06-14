import requests
from bs4 import BeautifulSoup
  
URL = "https://badoo.com/encounters"
r = requests.get(URL)
  
soup = BeautifulSoup(r.content, 'html5lib') # If this line causes an error, run 'pip install html5lib' or install html5lib
print(soup.prettify())