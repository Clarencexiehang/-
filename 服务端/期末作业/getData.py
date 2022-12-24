import sys
from lxml import etree
import json
import datetime
import time
import requests

url='http://mi.talkingdata.com/terminals.html?terminalType=2'

def askUrl(BaseUrl):
    head = {
        "User-Agent": 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.74 Safari/537.36'
    }
    try:
        res = requests.get(BaseUrl,headers=head)
        res.encoding = 'gbk'
        return res.text
    except Exception as e:
        if hasattr(e,'code'):
            print(e.code)
        if hasattr(e,'reason'):
            print(e.reason)

def getPhoneInfo():
    data = []
    for i in range(1,7):
        startYear = 2016
        startMonth = 1
        startDay = '01'
        typeDataList = []
        for j in range(33):
            startMonth = startMonth + 1
            if startMonth > 12:
                startMonth = 1
                startYear = startYear + 1
            if startMonth <10:
                strMonth = '0' + str(startMonth)
            date = str(startYear) + '-' + strMonth + '-' + startDay
            if i == 1:
                platform = '3'
            else:
                platform = '2'
            url = 'https://mi.talkingdata.com/terminal.json?dateType=m&date=' + date + '&platform='+platform+'&terminalType='+str(i)
            head = {
                "User-Agent": 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.74 Safari/537.36'
            }
            print(url)
            itemList = json.loads(requests.get(url,headers=head).text)
            # time.sleep(0.5)
            for item in itemList:
                dataList1 = []
                dataList1.append(float(item['r']))
                dataList1.append(1)
                dataList1.append(2)
                dataList1.append(item['k'])
                dataList1.append(date)
                typeDataList.append(dataList1)
            # print(itemList)
        data.append(typeDataList)
        typeDataList = []
    with open('phoneInfoData.json', 'w', encoding='utf-8') as f:
        json.dump(data, f, ensure_ascii=False, indent=4)

getPhoneInfo()

# with open('phoneInfoData.json', 'r', encoding='utf-8') as f:
#     data = json.load(f)
#     print(data)
    # json.dump(data, f, ensure_ascii=False, indent=4)