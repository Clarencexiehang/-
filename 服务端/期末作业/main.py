from lxml import etree
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.firefox.service import Service
import time
path = 'geckodriver(1).exe'
# brower = webdriver.Firefox(service=Service(path))
import json
from flask import Flask,request
app = Flask(__name__)
app.config['JSON_AS_ASCII'] = False

def getPhoneSalesVolumeData():
    with open('phoneInfoData.json','r',encoding = 'utf-8') as f:
        data = json.load(f)
    return data

@app.route("/PhoneSalesVolumeData")
def PhoneSalesVolumeData():
    data = getPhoneSalesVolumeData()
    index = int(request.args.get('type'))
    return {"data":data[index]},'200',{"Access-Control-Allow-Origin":"*"}

@app.route("/test")
def test():
    with open('./life-expectancy-table.json','r',encoding='utf-8') as f:
        m = json.load(f)
        # print(m)
        return json.dumps(m),'200',{"Access-Control-Allow-Origin":"*"}

if __name__ == '__main__':
    app.run(debug=True)