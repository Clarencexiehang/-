from config import db
import time
import os

startTimeOfPro = time.time()

# 使用 cursor() 方法创建一个游标对象 cursor
cursor = db.cursor()


def StoreBehaviourData():
    dirPath = "C:\\Users\\Clarence\\Desktop\\商业数据分析\\数据集\\data\\behavior"
    dirs = os.listdir(dirPath)

    for everyDayPath in dirs:
        print(everyDayPath)
        everyDayPath = dirPath + '\\' + everyDayPath
        everyFilePath = os.listdir(everyDayPath)
        for everyFile in everyFilePath:
            everyFile = everyDayPath + '\\' + everyFile
            # 处理用户文件
            # 获取打开的文件名以及用户uid
            fileName, extensionName = os.path.splitext(os.path.basename(everyFile))
            fileNameList = fileName.split("_")
            uid = fileNameList[0]
            day = fileNameList[1]

            bFile = open(everyFile, encoding='utf8')

            content = bFile.readline()
            tempList = content.split("<=>")
            use_time = tempList[1].replace('\n', '')

            content = bFile.readline()
            tempList = content.split("<=>")
            start_time = tempList[1].replace('\n', '')

            content = bFile.readline()

            while content:
                tempList = content.split("[=]")
                lastStr = tempList[-1].replace('\n', '')
                tempList[-1] = lastStr
                # print(tempList)

                fName = {
                    'T': '',
                    'P': '',
                    'I': '',
                    'W': '',
                    'V': '',
                    'N': '',
                    'C': '',
                    'A': '',
                    'B': '',
                    'U': ''
                }

                for i in range(0, len(tempList)):
                    data = tempList[i].split("<=>")
                    if data[0] == 'T':
                        fName['T'] = data[1]
                    elif data[0] == 'P':
                        fName['P'] = data[1]
                    elif data[0] == 'I':
                        fName['I'] = data[1]
                    elif data[0] == 'W':
                        fName['W'] = data[1]
                    elif data[0] == 'V':
                        fName['V'] = data[1]
                    elif data[0] == 'N':
                        fName['N'] = data[1]
                    elif data[0] == 'C':
                        fName['C'] = data[1]
                    elif data[0] == 'A':
                        fName['A'] = data[1]
                    elif data[0] == 'B':
                        fName['B'] = data[1]
                    elif data[0] == 'U':
                        fName['U'] = data[1]
                    else:
                        print('未匹配')
                try:
                    # 使用 execute()  方法执行 SQL 查询
                    sql1 = "insert into behaviour(uid,day,start_time,use_time"
                    sql2 = "values('%s','%s','%s','%s'" % (uid, day, start_time, use_time)
                    for i in fName.keys():
                        if fName[i] != '':
                            sql1 = sql1 + ","
                            sql1 = sql1 + i
                            sql2 = sql2 + ",\""
                            sql2 = sql2 + fName[i]
                            sql2 = sql2 + "\""
                    sql1 = sql1 + ') '
                    sql2 = sql2 + ');'
                    sql = sql1 + sql2
                    cursor.execute(sql)
                    db.commit()
                except:
                    print('err')
                    print(everyFile)
                    print(sql)
                    # os.system("pause")
                    # db.rollback()
                content = bFile.readline()


def StoreUsers():
    # 处理用户文件
    userFile = open("C:\\Users\\Clarence\\Desktop\\商业数据分析\\数据集\\data\demographic.csv", encoding='utf8')
    userContent = userFile.readline()
    userContent = userFile.readline()

    while userContent:
        # 对每一行数据处理然后存入数据库
        tempLine = userContent.split("\",\"")
        firstStr = tempLine[0].replace('"', '')
        tempLine[0] = firstStr
        lastStr = tempLine[8].replace('"\n', '')
        tempLine[8] = lastStr

        uid = tempLine[0]
        gender = tempLine[1]
        birthday = tempLine[2]
        edu = tempLine[3]
        job = tempLine[4]
        income = tempLine[5]
        province = tempLine[6]
        city = tempLine[7]
        isCity = tempLine[8]

        try:
            # 使用 execute()  方法执行 SQL 查询
            sql1 = "insert into user values(%s,%s,%s,%s,%s,%s,%s,%s,%s);"
            cursor.execute(sql1, (uid, gender, birthday, edu, job, income, province, city, isCity))
            db.commit()
            print('1')
            # res = cursor.execute("select * from user;")
            # item = cursor.fetchone()
            # print(item)
        except:
            print('err')
            db.rollback()

        userContent = userFile.readline()


db.close()

endTimeOfPro = time.time()
print('耗时: ', endTimeOfPro - startTimeOfPro)
