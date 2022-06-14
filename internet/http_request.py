import requests

#r = requests.get('https://web.whatsapp.com/')

#print(r.status_code)
#print(r.text)
#receive = requests.get('https://imgs.xkcd.com/comics/making_progress.png')

#with open(r'./images/image.png','wb') as f:
#    f.write(receive.content)

#pload = {'username':'Olivia','password':'123'}
#r = requests.post('https://httpbin.org/post',data = pload)
#print(r.text)

import requests
URL = "https://www.geeksforgeeks.org/data-structures/"
r = requests.get(URL)
print(r.content)