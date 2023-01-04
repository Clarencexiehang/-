# @Time : 2022/12/30 16:21
from config import db

cursor = db.cursor()

gender = ['男', '女']
# ['edu_primary','edu_junior','edu_highSchool','edu_junior_college','edu_college','edu_master']
edu = ['本科以下', '本科及以上']
# ['企业/公司一般职员','学生','党政机关事业单位工作者','企业/公司管理者','专业技术人员','个体户/自由职业者','无业、下岗、失业','产业、服务业工人','党政机关事业单位一般职员','党政机关事业单位领导干部','农村外出务工人员','农民','其他']
job = ['企业', '学生', '党政机关事业单位工作者', '个体户', '无业', '产业工人', '其他']
# ['1501～2000元', '无收入', '2001～3000元', '8001～12000元', '3001～5000元', '5001～8000元', '501～1000元', '12000元以上', '1001～1500元', '500元及以下']
income = ['三千以下', '三千到八千', '八千以上']

types = {}
for a in gender:
    for b in edu:
        for c in job:
            for d in income:
                str = a + "_" + b + "_" + c + "_" + d
                types[str] = []


# 打印每一类有什么人
# newType=types
# for key in types.keys():
#     sql2="select %s from divideusers where %s is not null;"%(key,key)
#     cursor.execute(sql2)
#     res=cursor.fetchall()
#     for i in range(0, len(res)):
#         uid=res[i][0]
#         sql3="update user set divideclass='%s' where uid = '%s';"%(key,uid)
#         try:
#             print(sql3)
#             cursor.execute(sql3)
#             db.commit()
#             newType[key].append(uid)
#         except:
#             print('err')

# for key in types.keys():
#     print(key,":",newType[key])

# sql = "create table divideUsers("
# for key in types.keys():
#     sql = sql+key+' char(50),'
# sql = sql.rstrip(',')
# sql = sql+");"
# print(sql)

# 将用户导入到分好的类中
# cursor.execute("select uid,gender,edu,job,income from user;")
# res=cursor.fetchall()
#
# for i in range(0, len(res)):
#     uid=res[i][0]
#     gender=res[i][1]
#     edu=res[i][2]
#     job=res[i][3]
#     income=res[i][4]
#
#     part = gender
#     if edu=='大学本科' or edu=='硕士及以上':
#         part = part+'_本科及以上'
#     else:
#         part = part + '_本科以下'
#
#     if job=='企业/公司一般职员' or job=='企业/公司管理者' or job=='专业技术人员':
#         part = part + '_企业'
#     elif job =='学生':
#         part = part + '_学生'
#     elif job =='党政机关事业单位工作者' or job=='党政机关事业单位一般职员' or job=='党政机关事业单位领导干部':
#         part = part + '_党政机关事业单位工作者'
#     elif job=='个体户/自由职业者' or job=='农村外出务工人员' or job=='农民':
#         part = part + '_个体户'
#     elif job=='无业、下岗、失业' or job=='退休':
#         part = part+'_无业'
#     elif job=='产业、服务业工人' :
#         part = part + '_产业工人'
#     elif job=='其他':
#         part = part + '_其他'
#
#
#     if income=='无收入'or income=='1501～2000元' or income=='2001～3000元' or income=='501～1000元' or income=='1001～1500元' or income=='500元及以下':
#         part = part + '_三千以下'
#     elif income=='3001～5000元' or income=='5001～8000元':
#         part = part + '_三千到八千'
#     elif income=='12000元以上' or income=='8001～12000元':
#         part = part + '_八千以上'
#
#     try:
#         sql="insert into divideusers(%s) values('%s');"%(part,uid)
#         cursor.execute(sql)
#         db.commit()
#     except:
#         print(sql)
#         print('err')
db.close()
