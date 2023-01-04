from config import db_local
from ClassDefine import TimeBucket,DecisionNode
import time

startTimeOfPro = time.time()
cursor=db_local.cursor()

def StoreData():

    cursor.execute("select uid from user;")
    for user in cursor.fetchall():
        uid=user[0]
        print(uid)
        # 判断时间段
        info = {
            '1': [],
            '2': [],
            '3': [],
            '4': [],
            '5': [],
            '6': [],
            '7': [],
            '8': [],
            '9': [],
            '10': [],
            '11': [],
            '12': []
        }
        db_local.ping(reconnect=True)
        sql3 = "select * from timecondition where uid='%s';" % (uid)
        cursor.execute(sql3)
        rs = cursor.fetchall()

        for m in range(0, len(rs)):
            period = rs[m][1]
            web = rs[m][2]
            visit_time = rs[m][3]
            day = rs[m][4]

            # 先检查该时间段内是否已经存储了此网站
            flag = 0
            if period == '00-02':
                period = 1
            elif period == '02-04':
                period = 2
            elif period == '04-06':
                period = 3
            elif period == '06-08':
                period = 4
            elif period == '08-10':
                period = 5
            elif period == '10-12':
                period = 6
            elif period == '12-14':
                period = 7
            elif period == '14-16':
                period = 8
            elif period == '16-18':
                period = 9
            elif period == '18-20':
                period = 10
            elif period == '20-22':
                period = 11
            elif period == '22-24':
                period = 12
            else:
                period = 0
            period=repr(period)
            for k in info[period]:
                if k.site == web:
                    flag = 1
                    break
            if flag == 1:
                continue
            for j in range(m + 1, len(rs)):
                if rs[j][4] == day:
                    continue
                if rs[j][2] == web and rs[j][1] == period:
                    visit_time = visit_time + rs[j][3]

            newSite = TimeBucket(web, visit_time)
            info[period].append(newSite)


        #开始处理
        sql1="select website,num from divideweb where class='男_本科以下_企业_三千以下'; "
        cursor.execute(sql1)
        res=cursor.fetchall()
        for i in range(0, len(res)):
            web=res[i][0]
            num=res[i][1]
            isVisited='0'
            maxPeriod='0'

            #查询该用户是否使用过该网站
            sql2="select distinct U from behaviour where uid='%s' and U is not null and U !='NULL';"%(uid)
            cursor.execute(sql2)
            for j in cursor.fetchall():
                if web in j[0]:
                    isVisited='1'
                    break

            #查看使用最多的时间段
            if isVisited=='1':
                for keyvalue in info.keys():
                    info[keyvalue].sort(key=lambda x: x.visit_time, reverse=True)
                    for l in info[keyvalue]:
                        if (web in l.site):
                            maxPeriod = keyvalue
                            break
            #加入数据库中
            sql4 = "insert into dnode values ('%s','%s','%s','%s','%s')" % (web, num, isVisited, maxPeriod, uid)
            cursor.execute(sql4)
            db_local.commit()


StoreData()
endTimeOfPro = time.time()
print('耗时: ', endTimeOfPro - startTimeOfPro)
db_local.close()