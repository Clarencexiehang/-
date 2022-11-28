import sys
from lxml import etree
import json
import requests

url='http://www.huaue.com/gx24.htm'

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


html = askUrl(url)
html_tree = etree.HTML(html)
data = html_tree.xpath("//table//tr/td/div/table/tr/td/text()")
# for item in data:
#      print(item)
# a// 表示a下面任意层级 a/ 表示a下的第一层级 text()表示该层级下的文本

#获取每个大分类的标题 :  贵州本科高校 贵州专科高校 贵州独立学院 贵州民办高校
className = html_tree.xpath("//table//tr/td/table//tr/td/a/b/text()")

#获取 学校名称 网址 的数据
datalist_schoolName = html_tree.xpath("//table//tr/td/div/table//tr/td/a/text()")
#print(datalist_schoolName)

#发现 贵州电力职业技术学院 的网址为空 进行手动处理
datalist_schoolName.insert(datalist_schoolName.index('贵州电力职业技术学院')+1,"")

school_title = ['学校名称','主管部门','所在地','层次','网址']

#存储全部信息
dataList = []

#获取每个分类的开头字符串 用来标志每个分类的开始 用来分类
titlearr = data[0]  # '学校名称　主管部门　所在地　层次　网址'


tempList = []       #每个大类下的信息，临时存储
for item in data:
    if item == titlearr:          # item=='学校名称　主管部门　所在地　层次　网址' 说明新的分类开始
        if tempList == []:
            continue

        dataList.append(tempList)
        tempList = []
        continue
    if len(item) == 5:      # data 里面还含有序号内容 如 '\r\n01\u3000' 长度为 5 ，应跳过
        continue

    data2obj = {}  #每个学校信息
    info = ""       #存储三个有效信息
    index = 1
    for char in item:
    #对取下的字符串进行数据处理 拿到自己想要的有效数据
        if char != u'\u3000':       # item 中 字符不为 '\u3000' 则为有效字符，加入 data2
            info = info + char
        else:
            if info != "":
                data2obj[school_title[index]] = info
                index = index + 1
                info = ""

    if len(data2obj) != 3: # 去除其他无效字符
        continue
    tempList.append(data2obj)

# 将这个大类下的所有学校基本信息加入到数据 dataList
dataList.append(tempList)


#对拿到的数据进行封装 封装成字典类型 后面用json存储
finaldata = {}
school_index = 0
for i in range(0,len(dataList)):
    everyClass = dataList[i]    #取出 dataList 中的每个分类的数据
    tempClassName = className[i]    #取出每个 分类的名字
    newEveryClass = {}          #用于存储每个分类的对象
    for j in range(0,len(everyClass)):              # 取出每个大类里的每个学校
        title2 = datalist_schoolName[school_index]  #加入学校名称
        school_index = school_index + 1
        everyClass[j][school_title[4]] = datalist_schoolName[school_index]  # 加入学校网址
        school_index = school_index + 1
        newEveryClass[title2] = everyClass[j]

    finaldata[tempClassName] = newEveryClass


#将数据写入一个json文件
with open('data1.json', 'w', encoding='utf-8') as f:
    json.dump(finaldata,f,ensure_ascii=False,indent=4)
