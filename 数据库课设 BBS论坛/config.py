import pymysql

DB_URI = 'mysql+pymysql://dev:123@121.5.235.148:3306/BBS'
SQLALCHEMY_DATABASE_URI = DB_URI
SQLALCHEMY_BINDS = {
    'admin': 'mysql+pymysql://admin:123456@121.5.235.148:3306/BBS'
}
SQLALCHEMY_TRACK_MODIFICATION = True

SECRET_KEY = "asdasdasd"


#邮箱配置
MAIL_SERVER = 'smtp.qq.com'
MAIL_USE_SSL = True
MAIL_PORT = 465
MAIL_USERNAME = '1094010958@qq.com'
MAIL_PASSWORD = 'qgvwdeibhfquffjg'
MAIL_DEFAULT_SENDER = '1094010958@qq.com'


#pymysql配置
db = pymysql.connect(host='121.5.235.148',
                     user='dev',
                     password='123',
                     database='ba')