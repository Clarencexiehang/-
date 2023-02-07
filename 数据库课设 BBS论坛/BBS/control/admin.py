import datetime

from flask import Flask,request,Blueprint,jsonify
import json
from exts import db


bp = Blueprint("admin",__name__,url_prefix='/admin')

# 请求所有用户的昵称 (存储过程 实现)
@bp.route('/getusers',methods=['GET','POST'])
def getUsers():
    engine = db.get_engine()
    users=[]
    with engine.connect() as conn:
        # 利用存储过程查询所有用户的昵称
        res = conn.execute(f"call getAll_Nickname()")
        item = res.fetchall()
        print(item)
        for i in item:
            users.append(i[0])
    return {'users':users}


# 根据用户昵称注销账号
@bp.route("/logout",methods=['GET','POST'])
def logout():
    engine = db.get_engine()
    data = request.data
    user_info = json.loads(data)
    nickname = user_info.get('nickname')
    type = user_info.get('type')
    if type == 'disc':
        with engine.connect() as conn:
            conn.execute(f"delete from user where nickname = '{nickname}'")
            return {'status':'ok'}
    else:
        return {'status':'DoN'}


# 通过用户名查询其文章 (存储过程 实现)
@bp.route('/getuserartbynickname',methods=['GET','POST'])
def getArtByNIckname():
    data=json.loads(request.data)
    nickname=data.get('nickname')
    userArt=[]
    engine = db.get_engine()
    with engine.connect() as conn:
        res = conn.execute(f"call getArt_By_Nickname('{nickname}')")
        item=res.fetchall()
        for art in item:
            year = str(art[3].year)
            month = str(art[3].month)
            day = str(art[3].day)
            hour = str(art[3].hour)
            minute = str(art[3].minute)
            second = str(art[3].second)

            uArt={
                'article_id':art[0],
                'user_account':art[1],
                'content':art[2],
                'posttime':year+'.'+month+'.'+day+'  '+hour+':'+minute+':'+second,
                'agreenum':art[4],
                'title':art[5]
            }
            userArt.append(uArt)

    if len(userArt)==0:
        return {'hasArt':'no'}
    else:
        return {'hasArt':'yes','useArt':userArt}




# 后台通过文章 id 删除文章
@bp.route('/remartbyid',methods=['GET','POST'])
def removeArtByID():
    data=json.loads(request.data)
    article_id=data.get('article_id')

    engine = db.get_engine()
    with engine.connect() as conn:
        res = conn.execute(f"delete from article where article_id='{article_id}'")
    return {'status':'remok'}



# 后台获取公告请求
@bp.route('/getanncbyid',methods=['GET','POST'])
def getAnncByID():
    data=json.loads(request.data)
    type=data.get('type')
    aid = data.get('aid')
    if type=='get':
        content=None
        engine = db.get_engine()
        with engine.connect() as conn:
            res=conn.execute(f"select content from announcement where Aid='{aid}'")
            item=res.fetchone()
            content=item[0]
        return {'content':content}

    elif type=='modify':
        content=data.get('content')
        try:
            engine = db.get_engine()
            with engine.connect() as conn:
                res = conn.execute(f"update announcement set content='{content}' where Aid='{aid}'")
            return {'status':'ok'}
        except:
            return {'status': 'error'}
    else:
        print('删除 :',aid)
        engine = db.get_engine()
        with engine.connect() as conn:
            res = conn.execute(f"delete from announcement where Aid='{aid}'")
        return {'status': 'ok'}


# 后台请求用户热度信息 (存储过程 实现)
@bp.route('/userdata',methods=['GET','POST'])
def getUserHot():
    data=json.loads(request.data)
    type=data.get('type')
    engine = db.get_engine()
    if type=='usehot': # 用户热度请求(文章数、粉丝数)
        userHot=[]
        with engine.connect() as conn:
            # 获取用户名
            res = conn.execute(f"call getAll_Nickname()")
            nicknameList = res.fetchall()
            for use in nicknameList:
                hotInfo={
                }
                res2 = conn.execute(f"call getArtN_FanN_By_Nickname('{use[0]}')")
                hot=res2.fetchone()
                hotInfo['nickname']=use[0]
                hotInfo['carenum']=hot[0]
                hotInfo['articlenum']=hot[1]
                userHot.append(hotInfo)
        return {'userHot':userHot}

    elif type=='regNumOfMonth': # 月用户注册量请求
        regNumOfMonth = [0] * 13
        with engine.connect() as conn:
            res = conn.execute(f"select registertime from user")
            regNumList=res.fetchall()

            for i in regNumList:
                m=i[0].date().month
                regNumOfMonth[m]=regNumOfMonth[m]+1
        return {'regN':regNumOfMonth}

    else:
        return 'userHot'


# 后台请求活跃用户数据
@bp.route('/hotuser',methods=['GET','POST'])
def getHotUser():
    engine = db.get_engine()
    now = datetime.datetime.now()

    hotUser = {}
    with engine.connect() as conn:
        res0 = conn.execute(f"select acountname from user")
        aclist=res0.fetchall()

        for i in aclist:
            u={
                'account':i[0],
                'hotN':0
            }
            hotUser[i[0]]=u

        res = conn.execute(f"select user_account,posttime from article")
        item=res.fetchall()
        for art in item:
            account=art[0]
            posttime=art[1]
            year=posttime.date().year
            month=posttime.date().month
            day=posttime.date().day

            if (year==now.year)&(month==now.month)&(day==now.day):
                v=hotUser.get(account).get('hotN')
                hotUser[account]['hotN']=v+1

    return {'hotUser':hotUser}


# 后台请求用户活跃收藏数、评论数
@bp.route("/sumofreply",methods=['GET','POST'])
def sumOfReply():
    engine = db.get_engine()
    try:
        with engine.connect() as conn:
            res = conn.execute(f"select acountname from user")
            accountList = res.fetchall()
            print(accountList)
            userAct = []
            for accountName in accountList:
                print(accountName[0])
                use={
                    'accountname':accountName[0],
                    'repNum':0,
                    'colleNum':0
                }
                try:
                    res1 = conn.execute(f"select count(*) from reply where date(replyTime) = date(NOW()) group by accountname having accountname = '{accountName[0]}'")
                    r1=res1.fetchone()
                    use['repNum']=r1[0]
                except:
                    use['repNum'] = 0
                try:
                    res2 = conn.execute(
                        f"select count(*) from collect where date(collectTime) = date(NOW()) group by account having account = '{accountName[0]}'")
                    r2 = res2.fetchone()
                    use['colleNum']=r2[0]
                except:
                    use['colleNum'] = 0

                userAct.append(use)
            return {"userAct":userAct}
    except:
        return {'status':'Nok'}






# 后端发布公告请求
@bp.route("/postnotice",methods=['GET','POST'])
def postnotice():
    engine = db.get_engine()
    data = request.data
    notice_info = json.loads(data)
    notice = notice_info.get('NoticeContent')

    print('发布公告 ',notice)
    with engine.connect() as conn:
        conn.execute(f"insert into announcement(content) values ('{notice}')")
        if conn:
            return {'status':'ok'}
        else:
            return {'status':'DoN'}
