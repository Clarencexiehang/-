from config import db_local
from models.ClassDefine import TimeBucket
import time

startTimeOfPro = time.time()
cursor=db_local.cursor()

def time_condition():
    timeList=[]
    #获取到每一个人的id
    cursor.execute("select uid from user;")
    rs = cursor.fetchall()
    users = []
    for i in rs:
        users.append(i[0])

    for user1 in range(997, 998):
        user=users[user1]
        print(user1)
        sql1="select day,start_time,use_time,T,U from behaviour where uid = '%s';"%(user)
        cursor.execute(sql1)
        res = cursor.fetchall()
        for i in range(0, len(res)):
            if res[i][4] is None or res[i][4] == 'NULL':
                continue
            day=res[i][0]
            start_time=res[i][1]
            use_time=res[i][2]
            t=res[i][3]
            u=res[i][4]

            #计算属于哪一个时间段
            tempstr = start_time.split(' ')
            ts=tempstr[1]
            hour=int(ts[0]+ts[1])
            minute=int(ts[3]+ts[4])
            second=int(ts[6]+ts[7])
            now=hour*3600+minute*60+second+int(t)
            if now>0 and now<=3600*2:
                period = '00-02'
            elif  now>3600*2 and now<=3600*4:
                period = '02-04'
            elif  now>3600*4 and now<=3600*6:
                period = '04-06'
            elif  now>3600*6 and now<=3600*8:
                period = '06-08'
            elif  now>3600*8 and now<=3600*10:
                period = '08-10'
            elif  now>3600*10 and now<=3600*12:
                period = '10-12'
            elif  now>3600*12 and now<=3600*14:
                period = '12-14'
            elif  now>3600*14 and now<=3600*16:
                period = '14-16'
            elif  now>3600*16 and now<=3600*18:
                period = '16-18'
            elif  now>3600*18 and now<=3600*20:
                period = '18-20'
            elif  now>3600*20 and now<=3600*22:
                period = '20-22'
            elif  now>3600*22 and now<=3600*24:
                period = '22-24'

            #处理url，提取网站，并存取
            website = u.split('/')  # 分割url
            for site in website:
                if 'com' in site or 'cn' in site or 'net' in site:
                    flag = 0
                    # 如果已经存取了该网站，改变visit_time和lastTime
                    for j in timeList:
                        if (j.uid==user and j.day==day and j.period==period and j.site == site):
                            j.lastTime=t
                            # 访问时间等于上次统计的时间加上 下一个网站访问t与现在t的差值
                            if i!= len(res)-1 and res[i+1][0] == day:
                                j.visit_time = j.visit_time+res[i+1][3]-t

                            flag = 1
                            break
                    # 如果没有添加过该网站，则添加进去
                    if flag == 0:
                        if i != len(res) - 1 and res[i + 1][0] == day:
                            visitTtime = res[i+1][3]-t
                        else:
                            visitTtime = 0
                        newSite = TimeBucket(user,day,period,site,visitTtime,t)
                        timeList.append(newSite)

    return timeList


tempList=time_condition()

for i in tempList:
    try:
        sql="insert into timecondition values ('%s','%s','%s','%s','%s');"%(i.uid,i.period,i.site,i.visit_time,i.day)
        cursor.execute(sql)
        db_local.commit()
    except:
        print(sql)
        print('err')

endTimeOfPro = time.time()
print('耗时: ', endTimeOfPro - startTimeOfPro)
db_local.close()