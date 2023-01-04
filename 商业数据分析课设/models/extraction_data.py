from config import db
from classify import types
from ClassDefine import WebSite
import time

startTimeOfPro = time.time()

cursor = db.cursor()


def getURL():
    db.ping(reconnect=True)
    cursor.execute("select uid,U from behaviour where U is not null and U!='NULL';")
    res = cursor.fetchall()
    # 遍历每一条url
    for data in res:
        uid = data[0]
        website = data[1].split('/')  # 分割url
        sql1 = "select divideclass from user where uid= '%s';" %(uid)
        cursor.execute(sql1)
        devideclass = (cursor.fetchone())[0]
        for site in website:
            if 'com' in site or 'cn' in site or 'net' in site:
                flag = 0
                # 如果已经存取了该网站，则不做处理
                for j in types[devideclass]:
                    if (j.site == site):
                        j.visit_num = j.visit_num + 1  # 访问次数+1
                        flag = 1
                        break
                # 如果没有添加过该网站，则添加进去
                if flag == 0:
                    newSite = WebSite(site, 0)
                    newSite.visit_num = newSite.visit_num + 1
                    types[devideclass].append(newSite)
            break

getURL()

for key in types.keys():
    for data in types[key]:
        try:
            sql2 = "insert into divideweb values ('%s','%s','%s');" % (key,data.site,data.visit_num)
            cursor.execute(sql2)
            db.commit()
        except:
            print(sql2)
            print('err')

endTimeOfPro = time.time()
print('耗时: ', endTimeOfPro - startTimeOfPro)
db.close()
