import json
import random
import string
from datetime import datetime
import config
from exts import db,mail
from flask import Flask,request,jsonify,Blueprint,session
from flask_mail import Message

bp = Blueprint("article",__name__,url_prefix='/article')


# 根据文章 id 获取文章信息( 进入文章详情页 )
@bp.route('/getInfo',methods=['GET','POST'])
def showArticle():
    engine = db.get_engine()
    data = json.loads(request.data)
    articleID = data.get('article_id')
    type = data.get('type')

    if type == 'getArtInfo':
        with engine.connect() as conn:
            try:
                cursor = conn.execute(f"select * from article left outer join user on(article.user_account=user.acountname) where article_id={articleID}")
                item = cursor.fetchone()
                return {
                    'nickname': item[8],
                    'content': item[2],
                    'postTime': item[3],
                    'agreeNum': item[4],
                    'title': item[5]
                }
            except:
                return {'content': 'Can not found article content!'}

    elif type == 'getCom':
        with engine.connect() as conn:
            try:
                cursor = conn.execute(f"select * from reply where article_id = {articleID} order by replyTime asc;")
                replyData = cursor.fetchall()

                replyInfo = []  # 记录该文章的所有评论信息

                for item in replyData:
                    if item[4] is None:  # 如果replyID为空，返回回复文章的楼主评论
                        sql = "select nickname from user where acountname = '" + item[2] + "';";
                        nn = conn.execute(sql)
                        nickname = nn.fetchone()

                        year = str(item[6].year)
                        month = str(item[6].month)
                        day = str(item[6].day)
                        hour = str(item[6].hour)
                        minute = str(item[6].minute)
                        second = str(item[6].second)

                        floor = {
                            'id': item[0],
                            'floorNum': item[1],
                            'nickname': nickname[0],
                            'content': item[3],
                            'replyTime': year+'.'+month+'.'+day+'  '+hour+':'+minute+':'+second,
                            'likeNum': item[7],
                            'replyToFloor': [],
                            'replyType': 'reply_to_article'
                        }
                        replyInfo.append(floor)
                    else:
                        sql = "select nickname from user where acountname = '" + item[2] + "';";

                        # 查到回复评论的原评论作者
                        rn = conn.execute(
                            f"select nickname from user where acountname in (select accountname from reply where id = {item[4]});")
                        replyName = rn.fetchone()
                        nn = conn.execute(sql)
                        nickname = nn.fetchone()

                        replyFloor = {
                            'id': item[0],
                            'floorNum': item[1],
                            'nickname': nickname[0],
                            'content': item[3],
                            'replyID': item[4],
                            'replyName': replyName[0],
                            'replyTime': year+'.'+month+'.'+day+'  '+hour+':'+minute+':'+second,
                            'likeNum': item[7],
                            'replyType': 'reply_to_customer'
                        }
                        # 将回复楼主的评论添加进每一楼的字典中
                        for m in replyInfo:
                            # 找到该评论属于哪一楼
                            if replyFloor['floorNum'] == m['floorNum']:
                                if replyFloor['replyID'] == m['id']:
                                    m['replyToFloor'].append(replyFloor)
                                    break
                                else:
                                    for n in m['replyToFloor']:
                                        if replyFloor['replyID'] == n['id']:
                                            m['replyToFloor'].append(replyFloor)
                                            break
                print(replyInfo)
                return {'replyInfo':replyInfo}

            except:
                return {'content': 'Can not found article content!'}
    else:
        return 'ok'


# 发布文章
@bp.route('/postarticle',methods=['GET','POST'])
def postArticle():
    engine = db.get_engine()
    data = json.loads(request.data)
    acountname=data.get('acountname')
    title=data.get('title')
    content=data.get('content')
    print('  账号 :',acountname,'  发布文章 :',content,'  title:',title)
    with engine.connect() as conn:
        try:
            cursor = conn.execute(f"insert into article (user_account,content,title) values ('{acountname}','{content}','{title}')")
            return 'ok'
        except:
            return {'content': 'Can not found article content!'}
    return 'ok'


# 根据文章 id 修改内容
@bp.route('/modifyArticle',methods=['GET','POST'])
def modifyArticle():
    engine = db.get_engine()
    data = json.loads(request.data)
    articleID = data.get('article_id')
    newContent = data.get('newContent')
    with engine.connect() as conn:
        try:
            conn.execute(f"update article set content = {newContent} where article_id = {articleID};")
            conn.execute(f"update article set posttime = {datetime.now()} where article_id = {articleID};")
        except:
            return 'ERROR'
    return 'ok'



# 根据文章 id 将点赞数 +1
@bp.route('/addartagreenum',methods=['GET','POST'])
def addAgreenum():
    engine = db.get_engine()
    data = json.loads(request.data)
    articleID = data.get('article_id')
    print('------------ 文章 ',articleID,' ',type(articleID),'   点赞 +1 ...')
    with engine.connect() as conn:
        try:
            conn.execute(f"update article set agreenum = agreenum+1 where article_id = {articleID}")
        except:
            return 'ERROR'
    return 'ok'


# 根据评论 id 将点赞数 +1
@bp.route('/addcomagreenum',methods=['GET','POST'])
def Agree():
    engine = db.get_engine()
    data = json.loads(request.data)
    replyID = data.get('reply_id')

    with engine.connect() as conn:
        try:
            conn.execute(f"update reply set likeNum = likeNum+1 where id = {replyID}")
            return 'ok1'
        except:
            return {'content': 'Can not found article content!'}
    return 'ok2'



# 添加新的评论(或回复)
@bp.route('/addrep',methods=['GET','POST'])
def AddReply():
    engine = db.get_engine()
    data = json.loads(request.data)
    floorNUM = data.get('floorNum')
    account = data.get('account')
    content = data.get('content')
    replyID = data.get('replyID')
    articleID = data.get('articleID')

    with engine.connect() as conn:
        try:
            if replyID!=None:
                sql1=f"insert into reply (floorNum, accountname, content, replyID, article_id, replyTime) " \
                     f"values ({floorNUM},'{account}','{content}',{replyID},{articleID},'{datetime.now()}');"
                conn.execute(sql1)
                return 'insertReply'
            else:
                sql1 = f"insert into reply (floorNum, accountname, content, article_id, replyTime) " \
                       f"values ({floorNUM},'{account}','{content}',{articleID},'{datetime.now()}');"
                conn.execute(sql1)
                return 'insertReply'
        except:
            print(sql1)
            return 'err'


# 根据 id 删除楼主评论
@bp.route('/delcom',methods=['GET','POST'])
def delCom():
    engine = db.get_engine()
    data = json.loads(request.data)
    com_id = data.get('com_id')
    print('删除楼主评论 : ', com_id)
    with engine.connect() as conn:
        # 先查询该楼主评论的 楼数
        floor=conn.execute(f"select floorNum from reply where id={com_id}")
        floorr=floor.fetchall()
        # 删除该楼主评论下的每个回复
        for f in floorr:
            try:
                conn.execute(f"delete from reply where floorNum={f[0]}")
                print('------ 成功 删除评论回复 : ', f[0])
            except:
                print('------ 删除评论回复 : ', f[0],'  异常 !')
        # 删除楼主评论
        conn.execute(f"delete from reply where id={com_id}")

    return 'ok'


# 根据 id 删除评论回复
@bp.route('/delrep', methods=['GET', 'POST'])
def delRep():
    engine = db.get_engine()
    data = json.loads(request.data)
    rep_id = data.get('rep_id')
    print('删除评论回复 : ', rep_id)
    with engine.connect() as conn:
        try:
            conn.execute(f"delete from reply where id={rep_id}")
            print('------ 成功 删除评论回复 : ', rep_id)
        except:
            print('------ 删除评论回复 : ', rep_id,'  异常 !')
    return 'ok'


# 添加新的关注
@bp.route('/careinfo',methods=['GET','POST'])
def Follow():
    engine = db.get_engine()
    data = json.loads(request.data)
    type=data.get('type')

    if type=='get':
        # 查询用户之间是否被关注
        care = data.get('care')
        becare = data.get('becare')

        with engine.connect() as conn:
            try:
                res=conn.execute(f"select * from careandbecare where care='{care}' and becare='{becare}'")
                careData=res.fetchall()

                if len(careData)!=0:
                    return {'status':'exists'}
                else:
                    return {'status': 'no_exists'}
            except:
                pass
    else:
        return 'err'