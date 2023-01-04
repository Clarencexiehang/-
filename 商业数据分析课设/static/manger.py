import os
from flask import Blueprint, request, Response, jsonify
import pymysql
from ..utils import DBPool,tools
manger = Blueprint('manger',__name__,url_prefix='/manger')
import datetime

#登录相关
@manger.route('/login',methods=['post'])
def login():
    conn = DBPool.getPOOL().connection()
    UserName = request.json['UserName']
    password = request.json['password']
    cursor = conn.cursor(cursor=pymysql.cursors.DictCursor)
    sql = f'''
    select * from manager where role_name = '{UserName}';
    '''
    # print(sql)
    cursor.execute(sql)
    result = cursor.fetchone()
    result['create_date'] = result['create_date'].strftime('%Y-%m-%d %H:%M:%S')
    if result['password'] == password:
        return {'data': {
            'state':'OK',
            'user': result
        }
                }
    else:
        return {'data': 'error'}

@manger.route('/logout')
def logout():
    return 'logout'

#管理员相关
@manger.route('/createManger',methods=['post'])
def createManger():
    conn = DBPool.getPOOL().connection()
    cursor = conn.cursor(cursor=pymysql.cursors.DictCursor)
    role_name = request.json['role_name']
    password = tools.md5Password(request.json['password'])
    phone = request.json['phone']
    create_date = datetime.datetime.now()
    comment = request.json['comment']
    state = request.json['state']
    sql = f'''
    insert manager(role_name, password, phone, create_date,state,comment) 
    values ({role_name},{password},{phone},{create_date},{state},{comment});
    '''
    try:
        cursor.execute(sql)
        return {'state':'OK'}
    except:
        return {'state':'error'}

@manger.route('/selectManger')
def selectManger():
    conn = DBPool.getPOOL().connection()
    cursor = conn.cursor(cursor=pymysql.cursors.DictCursor)
    sql = '''
        select  * from manager;
    '''
    try:
        cursor.execute(sql)
        result = cursor.fetchall()
        for r in result:
            r['create_date'] = r['create_date'].strftime('%Y-%m-%d %H:%M:%S')
        return {'state': 'OK','data':result}
    except Exception as e:
        return {'state':'error','msg':e}

#网站相关
@manger.route('/getWebsitHit')
def getWebsitHit():
    conn = DBPool.getPOOL().connection()
    cursor = conn.cursor(cursor=pymysql.cursors.DictCursor)
    forwordstime = datetime.date.today() - datetime.timedelta(days=6)
    sql = f'''
        select  * from website where time > {forwordstime};
    '''
    try:
        cursor.execute(sql)
        result = cursor.fetchall()
        for r in result:
            r['time'] = r['time'].strftime('%Y-%m-%d')
        respons = []
        for i in range(7):
            time1 = datetime.date.today() - datetime.timedelta(days=i)
            time1 = time1.strftime('%Y-%m-%d')
            obj = {
                'time':time1,
                'hits':0
            }
            for day in result:
                if day['time'] == time1:
                    obj['hits'] = day['hits']
            respons.append(obj)
        conn.close()
        return {'state': 'OK','data':respons}
    except Exception as e:
        return {'state':'error','msg':e}

#文章相关
#添加文章
@manger.route('/addNews',methods=['post'])
def addNews():
    conn = DBPool.getPOOL().connection()
    cursor = conn.cursor(cursor=pymysql.cursors.DictCursor)
    category_id = request.json['category_id']
    title = request.json['title']
    content = request.json['content']
    create_date = datetime.datetime.now()#.strftime('%Y%m%d%H%M%S')
    excerpt = request.json['excerpt']
    article_status = request.json['article_status']
    avatar = request.json['avatar']
    manager_id = request.json['manager_id']
    writer = request.json['writer']
    sql = f'''
    insert news( title, excerpt, article_status, manager_id, avatar, publish_date, last_modify_date, hits, content,writer)
    values ('{title}','{excerpt}',{article_status},{manager_id},'{avatar}','{create_date}','{create_date}',0,'{content}','{writer}');
    '''
    try:
        cursor.execute(sql)
        my_last_id = int(cursor.lastrowid)
        for item in category_id:
            sql1 = f'''
                insert nc(news_id, cate_id) values({my_last_id},{item})
            '''
            try:
                cursor.execute(sql1)
            except Exception as e:
                return {'state': 'error', 'msg': str(e)}
        conn.commit()
        conn.close()
        return {'state': 'OK'}
    except Exception as e:
         return {'state': 'error','msg':str(e)}

#删除文章
@manger.route('/deleteNews',methods=['delete'])
def deleteNews():
    news_id = request.args.get('news_id')
    conn = DBPool.getPOOL().connection()
    cursor = conn.cursor(cursor=pymysql.cursors.DictCursor)
    sql = f'''
        delete from news where news_id = {news_id};
    '''
    try:
        cursor.execute(sql)
        conn.commit()
        conn.close()
        return {'state': 'OK'}
    except Exception as e:
         return {'state': 'error','msg':str(e)}
#修改文章
@manger.route('/setNews',methods=['post'])
def setNews():
    conn = DBPool.getPOOL().connection()
    cursor = conn.cursor(cursor=pymysql.cursors.DictCursor)
    category_id = request.json['category_id']
    news_id = request.json['news_id']
    title = request.json['title']
    content = request.json['content']
    create_date = datetime.datetime.now()#.strftime('%Y%m%d%H%M%S')
    excerpt = request.json['excerpt']
    article_status = request.json['article_status']
    avatar = request.json['avatar']
    manager_id = request.json['manager_id']
    writer = request.json['writer']
    sql = f'''
    update news
    set title = '{title}',excerpt = '{excerpt}',article_status = {article_status},
    manager_id = {manager_id},avatar = '{avatar}',last_modify_date = '{create_date}',
    content = '{content}',writer = '{writer}'
    where news_id = {news_id};
    '''
    print(sql)
    sql1 = f'''
        delete from nc where news_id = {news_id}
    '''
    try:
        cursor.execute(sql1)
        cursor.execute(sql)
        for item in category_id:
            sql1 = f'''
                insert nc(news_id, cate_id) values({news_id},{item})
            '''
            try:
                cursor.execute(sql1)
            except Exception as e:
                return {'state': 'error', 'msg': str(e)}
        conn.commit()
        conn.close()
        return {'state': 'OK'}
    except Exception as e:
         return {'state': 'error','msg':str(e)}

#上传图片的函数
@manger.route('/upload',methods=['post'])
def upload():
    imageObj = request.files.to_dict()
    time = datetime.datetime.now().strftime('%Y%m%d%H%M%S')
    path = f'saveImage/{time}.jpg'
    imageObj['file'].save(path)
    # image1 = cv2.imdecode(np.asarray(bytearray(student_name['img1'].read()), dtype='uint8'), cv2.IMREAD_COLOR)
    # cv2.imshow('img1', image1)
    data = {
        'path':path
    }
    return {'state': 'OK','data':data}

#返回图片
@manger.route('/getImage')
def get_image():
    print(request.args.get('path'))
    # mime = mdict[((uri.split('/')[1]).split('.')[1])]
    imagepa = request.args.get('path')
    if not os.path.exists(imagepa):
        # Res 是我自己定义的返回类，raw方法将数据组成字典返回
        return jsonify('image does not exists')
    with open(imagepa, 'rb') as f:
        image = f.read()
    return Response(image, mimetype='jpg')

#分类相关
#插入分类
@manger.route('/addCate',methods=['post'])
def addCate():
    conn = DBPool.getPOOL().connection()
    cursor = conn.cursor(cursor=pymysql.cursors.DictCursor)
    cate_name = request.json['cate_name']
    cate_description = request.json['cate_description']
    sql = f'''
    insert cate(cate_name,cate_description) values('{cate_name}','{cate_description}');
    '''
    try:
        cursor.execute(sql)
        conn.commit()
        return {'state': 'OK'}
    except Exception as e:
        return {'state':'error','msg':e}
#修改文章分类
@manger.route('/setCate',methods=['post'])
def setCate():
    conn = DBPool.getPOOL().connection()
    cursor = conn.cursor(cursor=pymysql.cursors.DictCursor)
    cate_id = request.json['cate_id']
    cate_name = request.json['cate_name']
    cate_description = request.json['cate_description']
    sql = f'''
    update cate
    set cate_name = '{cate_name}',cate_description = '{cate_description}'
    where cate_id = {cate_id};
    '''
    try:
        cursor.execute(sql)
        conn.commit()
        conn.close()
        return {'state': 'OK'}
    except Exception as e:
        return {'state':'error','msg':e}

#删除文章分类
@manger.route('/deleteCate',methods=['delete'])
def deleteCate():
    conn = DBPool.getPOOL().connection()
    cursor = conn.cursor(cursor=pymysql.cursors.DictCursor)
    cate_id = request.args.get('cate_id')
    sql = f'''
        delete from cate where cate_id = {cate_id}
    '''
    try:
        cursor.execute(sql)
        conn.commit()
        conn.close()
        return {'state': 'OK'}
    except Exception as e:
        return {'state':'error','msg':e}

#获取文章分类
@manger.route('/getCate')
def getCate():
    conn = DBPool.getPOOL().connection()
    cursor = conn.cursor(cursor=pymysql.cursors.DictCursor)
    sql = '''
        select  * from cate;
    '''
    try:
        cursor.execute(sql)
        result = cursor.fetchall()
        for r in result:
            sql1 = f'''
                select count(*) as count from nc where cate_id={r['cate_id']};
            '''
            cursor.execute(sql1)
            result1 = cursor.fetchone()
            # print(result1)
            r['article_count'] = result1['count']
            r['create_time'] = r['create_time'].strftime('%Y-%m-%d %H:%M:%S')
        # print(result)
        return {'state': 'OK','data':result}
    except Exception as e:
        return {'state':'error','msg':e}

