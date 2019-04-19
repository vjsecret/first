#!/usr/bin/python
# -*- coding:utf8 -*-
from grs import Stock

stock = Stock('2618')                         # 擷取長榮航股價
print stock.moving_average(5)                 # 計算五日均價與持續天數
print stock.moving_average_value(5)           # 計算五日均量與持續天數
print stock.moving_average_bias_ratio(5, 10)  # 計算五日、十日乖離值與持續天數


#resp = requests.get(site)
#soup = bs(resp.text)

print ("1")
