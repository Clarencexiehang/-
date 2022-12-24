

#好像已经废弃？










from selenium import webdriver
from selenium.webdriver.common.by import By
import time
path = 'phantomjs.exe'

brower = webdriver.PhantomJS(path)

url = 'http://www.baidu.com'

brower.get(url)

#获取文本框对象
input = brower.find_element(value='kw')
time.sleep(1)
#在文本框中输入周杰伦
input.send_keys('周杰伦')

#获取百度一下按钮
button = brower.find_element(value='su')

#点击按钮

button.click()
time.sleep(1)

#滑到底部
js_bottom = 'document.documentElement.scrollTop=100000'
brower.execute_script(js_bottom)
time.sleep(1)
# 获取下一页的按钮
next = brower.find_element(by=By.XPATH,value="//a[@class='n']")

next.click()
#回到上一页
time.sleep(1)

brower.back()
#回去
time.sleep(1)

brower.forward()
#退出
time.sleep(1)
brower.quit()