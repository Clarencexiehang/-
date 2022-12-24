import requests
import ddddocr
from lxml import etree
from fake_useragent import UserAgent

# 模拟谷歌浏览器
ua = UserAgent()
headers = {
    'User-Agent': ua.chrome  # 只要谷歌浏览器的
}

# 登录页 url
loginUrl = 'https://so.gushiwen.cn/user/login.aspx?from=http://so.gushiwen.cn/user/collect.aspx'

# 传入 url 爬取
def askUrl(BaseUrl):
    headers = {
        'User-Agent': ua.chrome  # 只要谷歌浏览器的
    }
    try:
        res = requests.get(BaseUrl,headers=headers)
        res.encoding = 'utf8'
        return res.text # 返回网页 html 文本
    except Exception as e:
        if hasattr(e,'code'):
            print('错误码  :',e.code)
        if hasattr(e,'reason'):
            print('错误原因  :',e.reason)

# 获取网页 html 文本
html = askUrl(loginUrl)

html_tree = etree.HTML(html)

# 获取登录需要的参数 __VIEWSTATE , __VIEWSTATEGENERATOR
__VIEWSTATE = html_tree.xpath("//input[@id='__VIEWSTATE']/@value")[0]
__VIEWSTATEGENERATOR = html_tree.xpath("//input[@id='__VIEWSTATEGENERATOR']/@value")[0]

# 获取验证码图片 url
imgUrl = 'https://so.gushiwen.cn' + html_tree.xpath("//img[@id='imgCode']/@src")[0]

# 用 session 请求，防止验证码刷新
session = requests.session()
imageContent = session.get(imgUrl).content

print(__VIEWSTATE)
print(__VIEWSTATEGENERATOR)

# 将验证码图片写入文件
with open('img.png', 'wb') as f:
    f.write(imageContent)


# 传入图片数据，解析验证码
ocr=ddddocr.DdddOcr()
code=ocr.classification(imageContent)

print(code)

# 设置登录参数
data = {
    '__VIEWSTATE':__VIEWSTATE,
    '__VIEWSTATEGENERATOR':__VIEWSTATEGENERATOR,
    'from': 'https://so.gushiwen.cn/shiwens/',
    'email':'2608414230@qq.com',
    'pwd':'112233',
    'code':code,
    'denglu':'登录'
}

# 用 session 传入参数登录
res_post = session.post(loginUrl,data=data,headers=headers)
res = res_post.text

tree = etree.HTML(res)

# xpath 获取古诗标题
title = tree.xpath("//div[@class='cont']/a/text()")
# xpath 获取古诗链接
url = tree.xpath("//div[@class='cont']/a/@href")
# xpath 获取古诗作者
writer = tree.xpath("//div[@class='cont']/a/span/text()")

# 输出古诗信息
print('----------- 我的收藏：')
for i in range(0,len(title)):
    print(title[i],writer[i], 'https://so.gushiwen.cn' + url[i])
