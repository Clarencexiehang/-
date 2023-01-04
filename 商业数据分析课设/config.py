import pymysql

# 数据库连接
db = pymysql.connect(host='121.5.235.148',
                     user='dev',
                     password='',
                     database='ba')

db_local=pymysql.connect(host='localhost',
                     user='root',
                     password='123456',
                     database='ba')
