from sklearn.model_selection import train_test_split

from config import db_local
from models.ClassDefine import TimeBucket

cursor=db_local.cursor()

def changeData():
    str=[]
    cursor.execute("select * from dnode where uid='0143692D264FD906F10B8ECAB0F139D1'")
    rs=cursor.fetchall()
    time=[]
    for i in range(0, len(rs)):
        t = []
        num = rs[i][1]
        isv = rs[i][2]
        for j in range(5, 17):
            if rs[i][j] is not None:
                if int(rs[i][j]) > 1800:
                    t.append(2)
                else:
                    t.append(1)
            else:
                t.append(0)
        w = 0
        if num > 100:
            if isv == '0':
                if num > 1000:
                    w = 13
                else:
                    w = 0
            else:
                max = 0
                for j in range(0, len(t)):
                    if t[j] > max:
                        max = t[j]
                        w = j
        # if w!=0:
        #     w=1
        import csv
        str=[w,num,isv]
        for x in t:
            str.append(x)

        with open("./data.csv", "a+",newline='') as csvfile:
            writer = csv.writer(csvfile)
            writer.writerow(str)


#changeData()

def storeData1():
    cursor = db_local.cursor()
    cursor.execute("select uid from user;")
    rs = cursor.fetchall()
    for u in rs:
        uid=u[0]
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
        sql1 = "select * from timecondition where uid='%s';"% (uid)
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

        #改数据
        sql3="select * from dnode where uid='%s'"%(uid)
        cursor.execute(sql3)
        result=cursor.fetchall()
        for h in result:
            web=h[0]
            for keyvalue in info.keys():
                for website in info[keyvalue]:
                    if web == website.site:
                        keyvalue=keyvalue.replace('-','_')
                        sql4="update dnode set %s ='%s' where uid = '%s' and web='%s'"%(keyvalue,website.visit_time,uid,web)
                        #print(sql4)
                        cursor.execute(sql4)
                        db_local.commit()
                        break


def treeShow():
    from sklearn import tree
    import csv,pandas as pd,numpy as np
    import matplotlib.pyplot as plt
    import os
    import graphviz
    # 使用numpy导入CSV数据
    filename = 'pima_data.csv'
    with open('./data.csv', 'rt') as f:
        data = np.loadtxt(f, delimiter=',')


    clf = tree.DecisionTreeClassifier(criterion='gini'
                                      ,max_depth=3
                                      )
    x=data[:,[1,2]]
    y=data[:,[0]]
    xTrain,xTest,yTrain,yTest = train_test_split(x,y,test_size=0.3)
    clf=clf.fit(xTrain,yTrain)
    def tree1(clf):
        import warnings
        warnings.filterwarnings('ignore')
        fig = plt.figure(figsize=(35, 10))
        tree.plot_tree(clf,fontsize=8)
        fig.savefig(os.path.join('./', "tree1.png"))

    tree1(clf)
    print('得分: ',clf.score(x,y))

    doc_data=tree.export_graphviz(clf
                                  ,feature_names=['点击数量','是否访问','访问时段']
                                  ,class_names=['推送','不推送']
                                  ,filled=True
                                  ,rounded=True)
    graph = graphviz.Source(doc_data.replace('helvetica', '"Microsoft YaHei"'), encoding='utf-8')

treeShow()

