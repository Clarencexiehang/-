import json
import flask
from models.ClassDefine import WebSite, TimeBucket
from config import db

show_bp = flask.Blueprint("show", __name__, url_prefix='/show')


@show_bp.route('/income_condition', methods=['GET', 'POST'])
def income():
    info = {'data': []}  # 最终返回的数据
    reqType = flask.request.args.get('type')
    reqType = int(reqType)
    cursor = db.cursor()
    reqType = int(reqType)
    tempList = []  # 暂时存取所有的网站信息
    if reqType == 0:
        db.ping(reconnect=True)
        # print(tempList, '====')
        cursor.execute("select * from divideweb where class like '%三千以下' order by num desc;")
        res = cursor.fetchall()
        print(tempList, '====')
        for d in res:
            website = d[1]
            num = int(d[2])
            site = WebSite(website, num)
            tempList.append(site)
        print(tempList, '====')

    elif reqType == 1:
        db.ping(reconnect=True)
        cursor.execute("select * from divideweb where class like '%三千到八千' order by num desc;")
        res = cursor.fetchall()
        for d in res:
            website = d[1]
            num = int(d[2])
            site = WebSite(website, num)
            tempList.append(site)

    elif reqType == 2:
        db.ping(reconnect=True)
        cursor.execute("select * from divideweb where class like '%八千以上' order by num desc;")
        res = cursor.fetchall()
        for d in res:
            website = d[1]
            num = int(d[2])
            site = WebSite(website, num)
            tempList.append(site)

    tempList.sort(key=lambda x: x.visit_num, reverse=True)
    n = 0
    for i in range(0, len(tempList)):
        flag = 0
        for j in info['data']:
            if j['name'] == tempList[i].site:
                flag = 1
                break
        if flag == 0:
            info['data'].append({'value': tempList[i].visit_num, 'name': tempList[i].site})
            n = n + 1
        if n == 10:
            break
    return info


@show_bp.route('/time')
def time():
    uid = flask.request.args.get('uid')
    cursor = db.cursor()
    info = {
        '00-02': [],
        '02-04': [],
        '04-06': [],
        '06-08': [],
        '08-10': [],
        '10-12': [],
        '12-14': [],
        '14-16': [],
        '16-18': [],
        '18-20': [],
        '20-22': [],
        '22-24': []
    }
    db.ping(reconnect=True)
    sql1 = "select * from timecondition where uid='%s';" % (uid)
    cursor.execute(sql1)
    res = cursor.fetchall()

    for i in range(0, len(res)):
        time_block = res[i][1]
        web = res[i][2]
        visit_time = res[i][3]
        day = res[i][4]

        # 先检查该时间段内是否已经存储了此网站
        flag = 0
        for k in info[time_block]:
            if k.site == web:
                flag = 1
                break
        if flag == 1:
            continue
        for j in range(i + 1, len(res)):
            if res[j][4] == day:
                continue
            if res[j][2] == web and res[j][1] == time_block:
                visit_time = visit_time + res[j][3]

        newSite = TimeBucket(web, visit_time)
        info[time_block].append(newSite)

    # 根据不同时间段的网址访问时间排序，选择最多十条显示,存进finalData
    finalData = {
        '00-02': [],
        '02-04': [],
        '04-06': [],
        '06-08': [],
        '08-10': [],
        '10-12': [],
        '12-14': [],
        '14-16': [],
        '16-18': [],
        '18-20': [],
        '20-22': [],
        '22-24': []
    }
    for keyvalue in info.keys():
        info[keyvalue].sort(key=lambda x: x.visit_time, reverse=True)
        num = 0
        for i in info[keyvalue]:
            if (num == 10):
                break
            finalData[keyvalue].append({'web': i.site, 'visit_time': i.visit_time})
            num = num + 1

    response = json.dumps(finalData)
    return response


@show_bp.route('/getusers')
def getusers():
    users = []
    cursor = db.cursor()
    db.ping(reconnect=True)
    cursor.execute("select uid from user;")
    rs = cursor.fetchall()
    for u in rs:
        users.append(u[0])

    return users


@show_bp.route('/activePeriod')
def activePeriod():
    uid = flask.request.args.get('uid')
    cursor = db.cursor()
    db.ping(reconnect=True)
    sql1 = "select time_block,day from timecondition where uid='%s';" % (uid)
    cursor.execute(sql1)
    res = cursor.fetchall()
    info = {
        '00-02': 0,
        '02-04': 0,
        '04-06': 0,
        '06-08': 0,
        '08-10': 0,
        '10-12': 0,
        '12-14': 0,
        '14-16': 0,
        '16-18': 0,
        '18-20': 0,
        '20-22': 0,
        '22-24': 0
    }
    for i in range(0, len(res)):
        for key in info.keys():
            if res[i][0] == key:
                info[key] = info[key] + 1
                break
    return info


@show_bp.route('/pushweb')
def pushweb():
    uid = flask.request.args.get('uid')
    cursor = db.cursor()
    db.ping(reconnect=True)
    sql1 = "select * from dnode where uid='%s';" % (uid)
    cursor.execute(sql1)
    rs = cursor.fetchall()
    pushInfo = {
        '00-02': [],
        '02-04': [],
        '04-06': [],
        '06-08': [],
        '08-10': [],
        '10-12': [],
        '12-14': [],
        '14-16': [],
        '16-18': [],
        '18-20': [],
        '20-22': [],
        '22-24': []
    }
    for i in range(0, len(rs)):
        web = rs[i][0]
        num = rs[i][1]
        isVisited = rs[i][2]
        ifpush = 0
        if num >= 114.5:
            if isVisited == '0':
                if num > 965.5:
                    ifpush = 13
            else:
                max = 0
                for j in range(5, 17):
                    if rs[i][j] != None and int(rs[i][j]) > int(max):
                        max = rs[i][j]
                        ifpush = j

        if ifpush == 13:
            for key in pushInfo.keys():
                pushInfo[key].append(web)
        elif ifpush == 1:
            pushInfo['00-02'].append(web)
        elif ifpush == 2:
            pushInfo['02-04'].append(web)
        elif ifpush == 3:
            pushInfo['04-06'].append(web)
        elif ifpush == 4:
            pushInfo['06-08'].append(web)
        elif ifpush == 5:
            pushInfo['08-10'].append(web)
        elif ifpush == 6:
            pushInfo['10-12'].append(web)
        elif ifpush == 7:
            pushInfo['12-14'].append(web)
        elif ifpush == 8:
            pushInfo['14-16'].append(web)
        elif ifpush == 9:
            pushInfo['16-18'].append(web)
        elif ifpush == 10:
            pushInfo['18-20'].append(web)
        elif ifpush == 11:
            pushInfo['20-22'].append(web)
        elif ifpush == 12:
            pushInfo['22-24'].append(web)
    return pushInfo


db.close()
