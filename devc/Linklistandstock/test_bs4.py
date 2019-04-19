#!/usr/bin/python
# -*- coding:utf8 -*-

import requests
#import urllib
import urllib.request
import sys
#from BeautifulSoup import BeautifulSoup
from bs4 import BeautifulSoup as bs
import pandas as pd

#site='https://en.wikipedia.org/wiki/List_of_S%26P_500_companies'
site='http://www.twse.com.tw/zh/page/trading/exchange/TWT84U.html'
#site='https://www.ptt.cc/bbs/Beauty/index.html'
#site='http://192.168.100.1/Overview.html'

#resp = requests.get(site)
#soup = bs(resp.text)

print ("1")
page=urllib.request.urlopen(site)
print ("2")
soup=bs(page.read(),'lxml') #soup=bs(page.read())
print ("3")
print (soup.prettify())
print ("4")
#table = soup.find('table',{'class':'wikitable'})
#table = soup.find('table',{'class':'display'})
table = soup.find('table',{'id':'report-table'})
print ("5")
SD = dict()
for row in table.findAll('tr'):
  col = row.findAll('td')
  if len(col)>0:
    ticker=str(col[0].string.strip())
    sector = str(col[3].string.strip()).lower() #sector = str(col[6].string.strip()).lower()
    SD[ticker] = sector
ticker=pd.Series(SD)

ticker.to_csv('stock.csv')
