import json
from datetime import datetime
from config import db
from exts import db
from flask import Flask,request,jsonify,Blueprint,session


article_bp = Blueprint("article",__name__,url_prefix='/article')


# 根据文章 id 获取文章信息( 进入文章详情页 )
@article_bp.route('/getInfo',methods=['GET','POST'])
def showArticle():
    engine = db.get_engine()
    data = json.loads(request.data)
    articleID = data.get('article_id')
    type = data.get('type')
    if type == 'getArtInfo':
        with engine.connect() as conn:
            try:
                cursor = conn.execute(f"select * from article where article_id = {articleID}")
                item = cursor.fetchone()
                sql1 = "select nickname from user where acountname = '" + item[1] + "';";
                cursor = conn.execute(sql1)
                nickname = cursor.fetchone()
                return {
                    'nickname': nickname[0],
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
                        floor = {
                            'id': item[0],
                            'floorNum': item[1],
                            'nickname': nickname[0],
                            'content': item[3],
                            'replyTime': item[6],
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
                            'replyTime': item[6],
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


@article_bp.route('/addagreenum',methods=['GET','POST'])
def AddAgree():
    engine = db.get_engine()
    data = json.loads(request.data)
    replyID = data.get('reply_id')

    with engine.connect() as conn:
        try:
            conn.execute(f"call add_Rep_AgreeNum({replyID})")
            return 'ok1'
        except:
            return {'content': 'Can not found article content!'}
    return 'ok2'


@article_bp.route('/showagreenum',methods=['GET','POST'])
def ShowAgree():
    engine = db.get_engine()
    data = json.loads(request.data)
    replyID = data.get('reply_id')
    with engine.connect() as conn:
        try:
            rs=conn.execute(f"call show_Rep_AgreeNum({replyID})")
            data=rs.fetchone()
            return str(data[0])
        except:
            return {'content': 'Can not found article content!'}
    return 'ok2'

@article_bp.route('/delrep',methods=['GET','POST'])
def DeleteReply():
    engine = db.get_engine()
    data = json.loads(request.data)
    replyID = data.get('reply_id')
    with engine.connect() as conn:
        try:
            conn.execute(f"delete from reply where id={replyID}")
            return 'delete'
        except:
            conn.rollback_prepared()
            return 'err'

@article_bp.route('/modifyrep',methods=['GET','POST'])
def ModifyReply():
    engine = db.get_engine()
    data = json.loads(request.data)
    replyID = data.get('reply_id')
    content = data.get('content')
    with engine.connect() as conn:
        try:
            conn.execute(f"call modify_reply({replyID},{content});")
            return 'modifyReply'
        except:
            return 'err'

@article_bp.route('/addrep',methods=['GET','POST'])
def AddReply():
    engine = db.get_engine()
    data = json.loads(request.data)
    replyID = data.get('reply_id')
    content = data.get('content')
    with engine.connect() as conn:
        try:
            conn.execute(f"call modify_reply({replyID},{content});")
            return 'modifyReply'
        except:
            return 'err'



