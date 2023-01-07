import json
import random
import string
from datetime import datetime
import config
from exts import db,mail
from flask import Flask,request,jsonify,Blueprint,session
from flask_mail import Message

bp = Blueprint("view",__name__,url_prefix='/view')

@bp.route("/index",methods=['GET','POST'])
def indexAriticle():
    engine = db.get_engine()
    with engine.connect() as conn:
        res = conn.execute(f"select * from article")

        # 所有文章信息
        allOfArticle = res.fetchall()
        articleList = []
        for item in allOfArticle:
            # 根据账号查昵称
            resofnick = conn.execute(f"select nickname from user where acountname = '{item[1]}'")
            nickname = resofnick.fetchone()
            article = {
                'nickname':nickname[0],
                'article':{
                    'article_id':item[0],
                    'title':item[5],
                    'content':item[2],
                    'posttime':item[3],
                    'agreenum':item[4]
                }
            }
            articleList.append(article)

    return {'articleList':articleList}