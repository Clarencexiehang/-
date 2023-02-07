import json
import random
import string
from datetime import datetime
import config
from exts import db,mail
from flask import Flask,request,jsonify,Blueprint,session
from flask_mail import Message

bp = Blueprint("view",__name__,url_prefix='/view')

# *******************************************************  主页 *************************************
# *********************  首页 *********

# 首页 :  查询所有文章，及对应作者昵称
#       查询方式 ：连接查询
@bp.route("/index",methods=['GET','POST'])
def indexAriticle():
    engine = db.get_engine()
    data = json.loads(request.data)
    acountname = data.get("acountname")  # 收藏者

    with engine.connect() as conn:
        res = conn.execute(f"select * from article left outer join user on(article.user_account=user.acountname)")

        # 所有文章信息 及用户昵称
        allOfArticle = res.fetchall()
        articleList = []
        for item in allOfArticle:
            article = {
                'nickname':item[8],
                'article':{
                    'article_id':item[0],
                    'title':item[5],
                    'content':item[2],
                    'posttime':item[3],
                    'agreenum':item[4],
                    'collnum':0,
                    'hasbeCollected':None
                }
            }
            # 查询该文章是否被收藏过
            rr=conn.execute(f"select * from collect where account='{acountname}' and article_id={item[0]}")
            rn=rr.fetchall()

            if len(rn)==0:
                article['article']['hasbeCollected']=False
            else:
                article['article']['hasbeCollected'] = True

            # 查询文章被收藏数
            try:
                rt = conn.execute(
                    f"select collect.article_id,count(*) from  collect group by article_id having article_id={item[0]}")
                rg = rt.fetchone()
                article['article']['collnum'] = rg[1]
            except:
                article['article']['collnum'] = 0

            articleList.append(article)
    return {'articleList':articleList}