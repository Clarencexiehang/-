import json
import random
import string
from datetime import datetime
import config
from exts import db,mail
from flask import Flask,request,jsonify,Blueprint,session
from flask_mail import Message
bp = Blueprint("user",__name__,url_prefix='/user')

# *******************************************************  登录页 *************************************
# 用户登录请求
@bp.route("/log",methods=['GET','POST'])
def log():
    engine = db.get_engine()
    data = request.data
    user_info = json.loads(data)

    acountname = user_info.get('acountname')
    password = user_info.get('password')

    print('账号 ：', acountname,'  密码 ：',password)
    user_id = user_info.get('id')
    with engine.connect() as conn:
        res = conn.execute(f"select * from user where acountname = '{acountname}'")
        item = res.fetchone()
        print('查询结果：',item)
        if res != None:
            if item[5] == password:
                return {'status':'ok','nickname':item[2]}
            else :
                return {'status':'nook'}
        else:
            return {'status':'nook'}


# *******************************************************  注册页 *************************************
# 用户注册请求
@bp.route("/register",methods=['GET','POST'])
def regiter():
    engine = db.get_engine()
    data = request.data
    user_info = json.loads(data)
    acountname = user_info.get('acountName')
    nicktname = user_info.get('nicktName')
    phone = user_info.get('phone')
    email = user_info.get('email')
    birth=user_info.get('birth')
    password = user_info.get('password')
    captcha = user_info.get('captcha')

    if user_info.get('type') == 'getCaptcha':
        letters = string.digits
        captcha = "".join(random.sample(letters,6))
        if email:
            print("77777")
            message = Message(subject='您的BBS邮箱验证码',
                              recipients=[email],
                              body=f"【BBS】您注册BBS论坛的验证码是：{captcha},请勿泄露您的验证码，若非本人操作，请忽略该邮件。"
                              )
            mail.send(message)
            return {'captcha':captcha}
    else:
        with engine.connect() as conn:
            sql=f"insert into user (acountname, nickname, email,birthday,phone, password,registertime)values ('{acountname}','{nicktname}','{phone}','{email}','{birth}','{password}','{datetime.now()}')"
            print(sql)
            try:
                conn.execute(f"insert into user (acountname, nickname, email,birthday,phone, password,registertime,carenum,articlenum,collectnum)values ('{acountname}','{nicktname}','{email}','{birth}','{phone}','{password}','{datetime.now()}',{0},{0},{0});")
                return {'status':'ok'}
            except:
                return {'status':'userExists'}
    return {'status':'ok'}



# *******************************************************  主页 *************************************
# 根据用户昵称获取其他信息
@bp.route('/userAllInfo',methods=['POST','GET'])
def getAllInfo():
    data=json.loads(request.data)
    nickName=data.get('nickname')
    engine = db.get_engine()
    item = None
    with engine.connect() as conn:
        cursor = conn.execute(f"select acountname,nickname,articlenum,carenum from user where nickname='{nickName}' ")
        item = cursor.fetchone()
        userinfo = {
            'acountname': item[0],
            'nickname': item[1],
            'articlenum': item[2],
            'carenum': item[3]
        }
        return {'userinfo': userinfo}


# 获取 通知 数据
@bp.route('/getannounc',methods=['GET'])
def getAnnounc():
    engine = db.get_engine()
    announc=[]
    with engine.connect() as conn:
        res=conn.execute(f"select Aid,content,posttime from announcement")
        data=res.fetchall()

        for item in data:
            year=str(item[2].year)
            month = str(item[2].month)
            day = str(item[2].day)

            hour=str(item[2].hour)
            minute=str(item[2].minute)
            second=str(item[2].second)
            an={
                'Aid':item[0],
                'content':item[1],
                'posttime':year+'.'+month+'.'+day+'  '+hour+':'+minute+':'+second
            }
            announc.append(an)
    return {'ann':announc}


# 热榜数据请求
@bp.route('/hotdata',methods=['GET','POST'])
def retop20():
    engine = db.get_engine()
    # 数据库查找
    with engine.connect() as conn:
        sql = f"select title,content,agreenum,posttime,article_id from article order by agreenum desc "
        res = conn.execute(sql)
        # 存放文章
        article = []
        res1 = res.fetchall()
        for i in range(0, len(res1)):
            if i<=20: # 取前 20 条
                if res1[i][4] is None or res1[i][4] == 'NULL':
                    continue
                year = str(res1[i][3].year)
                month = str(res1[i][3].month)
                day = str(res1[i][3].day)
                hour = str(res1[i][3].hour)
                minute = str(res1[i][3].minute)
                second = str(res1[i][3].second)

                art = {
                    'title': res1[i][0],
                    'content': res1[i][1],
                    'agreenum': res1[i][2],
                    'posttime': year + '.' + month + '.' + day + '  ' + hour + ':' + minute + ':' + second,
                    'article_id': res1[i][4]
                }
                # 添加每一篇文章
                article.append(art)
    return {'hotdata': article}


# 搜索功能
@bp.route("/search",methods=['GET','POST'])
def Search():
    engine = db.get_engine()
    data = json.loads(request.data)
    inf = data.get("inf")

    with engine.connect() as conn:
        res = conn.execute(f"select * from article where title like '%%{inf}%%'")

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



# 用户消息请求
@bp.route('/userchat', methods=['GET', 'POST'])
def userchat():
    engine = db.get_engine()
    print('-------------- 用户消息请求 ')
    data = json.loads(request.data)
    reciever = data.get("reciever")
    sender = data.get("sender")

    print(' 发送方 ：',sender,'  接收方 ：',reciever)

    # 数据库查找
    with engine.connect() as conn:
        # 根据昵称找账号
        r1=conn.execute(f"select acountname from user where nickname='{sender}'")
        ssender=r1.fetchone()[0]

        r2 = conn.execute(f"select acountname from user where nickname='{reciever}'")
        rreciever = r2.fetchone()[0]

        sql = f"select content,sendTime,sender from message where (reciever,sender) = ('{rreciever}','{ssender}') or (reciever,sender) = ('{ssender}','{rreciever}')"
        res = conn.execute(sql)
        # 存放文章
        message = []
        res1 = res.fetchall()
        for i in range(0, len(res1)):
            if res1[i][0] is None or res1[i][0] == 'NULL':
                continue
            year1 = res1[i][1].year
            month1 = res1[i][1].month
            day1 = res1[i][1].day
            hour1 = res1[i][1].hour
            minute1 = res1[i][1].minute
            second1 = res1[i][1].second
            keynum = year1 * 31536000 + month1 * 2592000 + day1 * 86400 + hour1 * 3600 + minute1 * 60 + second1

            year = str(res1[i][1].year)
            month = str(res1[i][1].month)
            day = str(res1[i][1].day)
            hour = str(res1[i][1].hour)
            minute = str(res1[i][1].minute)
            second = str(res1[i][1].second)
            mes1 = {
                'type':'r',
                'content': res1[i][0],
                'posttime': year + '.' + month + '.' + day + '  ' + hour + ':' + minute + ':' + second,
                'keynum': keynum
            }

            if res1[i][2]==ssender:
                mes1['type']='s'

            message.append(mes1)
        message.sort(key=lambda x: x['keynum'], reverse=False)

    # 将文章返回给前端
    print('---------- 用户私信信息 ——-----------')
    print(message)
    return {'userchat': message}



# 请求用户消息数据
@bp.route('/reciverdata',methods=['GET','POST'])
def mymessage():
    engine = db.get_engine()
    data = json.loads(request.data)
    reciever = data.get("reciever")

    with engine.connect() as conn:
        sql = f"select content,sendTime,sender,id from message where (reciever) = ('{reciever}') order by sendTime"
        res = conn.execute(sql)
        # 存放文章
        message = []
        res1 = res.fetchall()
        for i in range(len(res1) - 1, -1, -1):
            if res1[i][0] is None or res1[i][0] == 'NULL':
                continue
            year = str(res1[i][1].year)
            month = str(res1[i][1].month)
            day = str(res1[i][1].day)
            hour = str(res1[i][1].hour)
            minute = str(res1[i][1].minute)
            second = str(res1[i][1].second)

            nick=conn.execute(f"select nickname from user where acountname='{res1[i][2]}'")
            nickname=nick.fetchone()

            mes1 = {
                'id':res1[i][3],
                'content': res1[i][0],
                'posttime': year + '.' + month + '.' + day + '  ' + hour + ':' + minute + ':' + second,
                'sender': nickname[0],
                'sender_ac':res1[i][2]
            }
            flag = 0
            print(message)

            for x in range(0, len(message)):
                if message[x]['sender'] == mes1['sender']:
                    flag = 1
                    break

            if flag == 0:
                print(flag)
                message.append(mes1)
    print('----------- message -----------------')
    print(message)
    return {'mymessage': message}




# 清空用户聊天记录
@bp.route('/clrmsg',methods=['GET','POST'])
def clearMsg():
    engine = db.get_engine()
    data = json.loads(request.data)
    reciever = data.get("reciever")
    sender = data.get("sender")

    print('------------- 清空聊天记录 ： ',sender,' -> ',reciever)
    with engine.connect() as conn:
        try:
            # res = conn.execute(f"call clrMsg_by_ac('{sender}','{reciever}')")
            res = conn.execute(f"delete from message where sender = '{sender}' and reciever = '{reciever}'")
            print('------------- 清空成功 ---------------')
        except:
            print('------------- 清空异常 ---------------')
    return 'ok'




# 用户消息发送请求
@bp.route('/sendmessage',methods=['GET','POST'])
def sendMessage():
    engine = db.get_engine()
    print('-------------- 用户消息请求 ')
    data = json.loads(request.data)
    reciever = data.get("reciever")
    sender = data.get("sender")
    content = data.get("content")

    print(sender,' 向 ',reciever,'发送消息 : ',content)
    # 数据库查找
    with engine.connect() as conn:
        # 根据昵称找账号
        r1 = conn.execute(f"select acountname from user where nickname='{sender}'")
        ssender = r1.fetchone()
        r2 = conn.execute(f"select acountname from user where nickname='{reciever}'")
        rreciever = r2.fetchone()

        sql = f"select id,content,sendTime from message "
        res = conn.execute(sql)
        res1 = res.fetchall()
        id_now = len(res1) + 1
        reciever_now = rreciever[0]
        print(reciever_now)
        sender_now = ssender[0]
        try:
            sql1 = f"insert into message(reciever,content,sender,sendTime) values ('{reciever_now}','{content}','{sender_now}','{datetime.now()}')"
            conn.execute(sql1)
            return 'send message completed!'
        except:
            print(sql1)
            return {'content': 'Can not send message!'}
    print('---------- 用户信息 ——-----------')
    return ok







# 根据用户昵称获取关注的的用户文章
@bp.route('/usercareart',methods=['POST','GET'])
def getcareart():
    data = json.loads(request.data)
    nickName = data.get('nickname')
    engine = db.get_engine()
    item = None
    with engine.connect() as conn:
        carecount = conn.execute(f"select acountname from user where nickname='{nickName}' ")
        it = carecount.fetchone()
        becarecount = conn.execute(f"select becare from careandbecare where care='{it[0]}' ")
        becarearticle = []
        for item in becarecount.fetchall():
            user_account = item[0]
            artic = f"select title,content,agreenum,posttime,article_id,user_account from article where user_account='{ user_account }'"
            res = conn.execute(artic)
            for item1 in res.fetchall():
                year = str(item1[3].year)
                month = str(item1[3].month)
                day = str(item1[3].day)
                hour = str(item1[3].hour)
                minute = str(item1[3].minute)
                second = str(item1[3].second)

                art = {
                    'nickname':item1[5],
                    'title': item1[0],
                    'content': item1[1],
                    'agreenum': item1[2],
                    'posttime': year + '.' + month + '.' + day + '  ' + hour + ':' + minute + ':' + second,
                    'article_id': item1[4],
                    'show':False
                }
                becarearticle.append(art)

        print(becarearticle)
        return {'usercareart': becarearticle}


# 根据账号查询收藏的文章
@bp.route('/getcollecart',methods=['POST'])
def getCollecArt():
    data=json.loads(request.data)
    acountname = data.get('acountname')
    engine = db.get_engine()
    collectArt=[]

    print('   查询 ',acountname,'  的收藏 ')
    with engine.connect() as conn:
        res = conn.execute(f"select article_id from collect where account = '{acountname}'")
        data=res.fetchall()
        print('data : ', data)
        # 根据每一个文章 id 找文章详细信息
        for item1 in data:
            print('item1 : ',item1)
            r1=conn.execute(f"select * from article where article_id = {item1[0]}")
            item=r1.fetchone()

            print(' item : ',item)
            article={
                'author_acountname':item[1],
                'article_id': item[0],
                'title': item[5],
                'content': item[2],
                'posttime': item[3],
                'agreenum': item[4]
            }

            r2 = conn.execute(f"select nickname from user where acountname = '{item[1]}'")
            item2 = r2.fetchone()
            article['nickname']=item2[0]

            collectArt.append(article)

    return {'cArtList':collectArt}


# 根据昵称修改信息
@bp.route("/modify",methods=['GET','POST'])
def modify():
    engine = db.get_engine()
    userinfo = json.loads(request.data)
    # 信息请求
    if userinfo.get('type') == 'get':
        nickname = userinfo.get('nickname')
        print(nickname)
        with engine.connect() as conn:
            item = conn.execute(f"select acountname,nickname,phone,email,password,birthday from user where nickname = '{nickname}'")
            user = item.fetchone()
            print(user)
            newuser = {'acountname':user[0], 'nickname':user[1], 'phone':user[2], 'email':user[3], 'password':user[4],'birthday':user[5]}
            return {'newuser':newuser}

    # 后台销户请求
    elif userinfo.get('type') == 'disc':
        return {'status': 'ok'}

    else:
        olduser = userinfo.get('useInfo')
        print(olduser)
        with engine.connect() as conn:
            try:
                item = conn.execute(f"update user set nickname = '{olduser.get('nickname')}',phone = '{olduser.get('phone')}',email = '{olduser.get('email')}',birthday='{olduser.get('birthday')}' ,password = '{olduser.get('password')}' where acountname = '{olduser.get('acountname')}'")
                return {'status': 'ok'}
            except:
                return {'status':'userExists'}


@bp.route("/personpage",methods=['GET','POST'])
def person():
    pass


# 根据昵称统计用户 文章数、关注数、粉丝数、收藏数、历史记录数
#    存储过程
@bp.route('/getfournum',methods=['GET','POST'])
def getNum():
    data=json.loads(request.data)
    nickname=data.get('nickname')
    engine = db.get_engine()
    num=[]
    with engine.connect() as conn:
        r1=conn.execute(f"call getArtNum_By_Nickname('{ nickname }')")
        d1=r1.fetchone()
        v1=d1[0]

        r2 = conn.execute(f"call getmyCareNum_By_Nickname('{nickname}');")
        d2 = r2.fetchone()
        v2 = d2[0]

        r3 = conn.execute(f"call getbeCareNum_By_Nickname('{nickname}')")
        d3 = r3.fetchone()
        v3 = d3[0]

        r4 = conn.execute(f"call getcollecNum_By_Nickname('{nickname}')")
        d4 = r4.fetchone()
        v4 = d4[0]

        r5 = conn.execute(f"call getHistNum_By_Nickname('{nickname}')")
        d5 = r5.fetchone()
        v5 = d5[0]

        num.append(v1)
        num.append(v2)
        num.append(v3)
        num.append(v4)
        num.append(v5)

    print(num)
    return {'num':num}

# 根据 id 查文章的标题、内容
@bp.route('/getart',methods=['GET','POST'])
def getByID():
    engine = db.get_engine()
    data = json.loads(request.data)
    article_id=data.get('article_id')

    art={
        'title':'',
        'content':''
    }
    with engine.connect() as conn:
        res = conn.execute(f"select title,content from article where article_id={article_id}")
        rn=res.fetchone()
        art['title']=rn[0]
        art['content']=rn[1]
    return {'art':art}



# 根据账号查找文章
@bp.route('/myarticle',methods=['GET','POST'])
def getArticle():
    # 获取账号名
    engine = db.get_engine()
    data=json.loads(request.data)
    acountname=data.get('acountname')
    # 数据库查找
    with engine.connect() as conn:
        sql= f"select title,content,agreenum,posttime,article_id from article where user_account='{ acountname }'"
        res = conn.execute(sql)
    # 存放文章
        article=[]
        for item in res.fetchall():
            year = str(item[3].year)
            month = str(item[3].month)
            day = str(item[3].day)
            hour = str(item[3].hour)
            minute = str(item[3].minute)
            second = str(item[3].second)

            art={
                'title':item[0],
                'content':item[1],
                'agreenum':item[2],
                'posttime':year+'.'+month+'.'+day+'  '+hour+':'+minute+':'+second,
                'article_id':item[4]
            }
        # 添加每一篇文章
            article.append(art)
    # 将文章返回给前端
    return {'article':article}


# 根据 id 删除用户文章
@bp.route('/delart',methods=['GET','POST'])
def delart():
    engine = db.get_engine()
    data = json.loads(request.data)
    id = data.get("article_id")
    with engine.connect() as conn:
        conn.execute(f"delete from article where article_id = {id}")
        return {'status':'ok'}
    return {'status':'No'}



# 根据 账号 请求关注的用户名
@bp.route('/mycare',methods=['GET','POST'])
def myCare():
    # 获取账号名
    engine = db.get_engine()
    data = json.loads(request.data)
    acountname = data.get('acountname')
    print(acountname)
    # 数据库查找关注的账号
    with engine.connect() as conn:
        res = conn.execute(f"select care,becare from careandbecare where care='{acountname}'")
        # 存放对应昵称用户
        careUser = []
        itemList = res.fetchall()
        for item in itemList:
            print(item)
            nickname = conn.execute(f"select nickname from user where acountname='{item[1]}'")
            careUser.append(nickname.fetchone()[0])
        print(careUser)
    return {'careUser':careUser}


# 根据 关注者-被关注者 账号添加关注关系
@bp.route("/addcare",methods=['GET','POST'])
def addCare():
    engine = db.get_engine()
    data = json.loads(request.data)
    care = data.get("care")  # 关注者
    becare = data.get("becare")  # 被关注者
    print('添加关注  ',care,'  -->  ',becare)
    with engine.connect() as conn:
        conn.execute(f"insert into careandbecare (care,becare) values ('{care}','{becare}')")
        return {'status': 'ok'}
    return {'status': 'No'}



# 根据 关注者-被关注者 账号取消关注关系
@bp.route("/cancelcare",methods=['GET','POST'])
def cancelcare():
    engine = db.get_engine()
    data = json.loads(request.data)
    nickname = data.get("nickname")  # 被关注者
    accountname1 = data.get("accountname")  # 关注者

    print('取消关注  ',accountname1,'  -->  ',nickname)
    with engine.connect() as conn:
        r1=conn.execute(f"select acountname from user where nickname = '{nickname}'")
        n1=r1.fetchone()
        conn.execute(f"delete from careandbecare where (care,becare) = ('{accountname1}','{n1[0]}')")
        return {'status': 'ok'}
    return {'status': 'No'}


# 根据账号 获取粉丝昵称
@bp.route('/careme',methods=['GET','POST'])
def careMe():
    # 获取账号名
    engine = db.get_engine()
    data = json.loads(request.data)
    acountname = data.get('acountname')
    print(acountname)
    # 数据库查找关注的账号
    with engine.connect() as conn:
        res = conn.execute(f"select care,becare from careandbecare where becare='{acountname}'")
        # 存放对应昵称用户
        careUser = []
        itemList = res.fetchall()
        for item in itemList:
            print(item)
            nickname = conn.execute(f"select nickname from user where acountname='{item[0]}'")
            careUser.append(nickname.fetchone()[0])
        print(careUser)
    return {'careUser':careUser}






# 根据 id 编辑用户文章
@bp.route('/modifyart',methods=['GET','POST'])
def modifyart():
    engine = db.get_engine()
    data = json.loads(request.data)
    id = data.get("article_id")
    title=data.get('title')
    Ncontent = data.get("content")
    with engine.connect() as conn:
        conn.execute(f"update article set content = '{Ncontent}' where article_id = {id}")
        conn.execute(f"update article set title = '{title}' where article_id = {id}")
        return {'status': 'ok'}
    return {'status': 'No'}



# 根据账号、文章 id 添加收藏
@bp.route('/addcollect',methods=['GET','POST'])
def addCollect():
    engine = db.get_engine()
    data = json.loads(request.data)
    article_id = data.get("article_id")  #文章
    acountname = data.get("acountname")   #收藏者

    print(' 用户 ',acountname,'  收藏文章 ',article_id)
    with engine.connect() as conn:
        sql=f"insert into collect(account,article_id,collectTime) values ('{acountname}',{article_id},'{datetime.now()}')"
        try:
            conn.execute(f"insert into collect(account,article_id,collectTime) values ('{acountname}',{article_id},'{datetime.now()}')")
            return {'status': 'ok'}
        except:
            print(sql)
            return {'status': 'no'}



# 根据账号、文章 id 取消收藏
@bp.route('/cancelcollec',methods=['GET','POST'])
def cancelcollec():
    engine = db.get_engine()
    data = json.loads(request.data)
    id = data.get("article_id")  #文章
    accountname = data.get("accountname")   #收藏者
    with engine.connect() as conn:
        conn.execute(f"delete from collect where (account,article_id) = ('{accountname}','{id}')")
        return {'status': 'ok'}
    return {'status': 'No'}



#  根据账号获取历史记录
@bp.route("/gethistory",methods=['GET','POST'])
def getHistory():
    engine = db.get_engine()
    data = json.loads(request.data)
    accountname = data.get("accountname")

    Hlist = []
    try:
        with engine.connect() as conn:
            res = conn.execute(f"select article_id,readtime from history where account = '{accountname}'")
            itemList = res.fetchall()

            for item in itemList:
                year = str(item[1].year)
                month = str(item[1].month)
                day = str(item[1].day)
                hour = str(item[1].hour)
                minute = str(item[1].minute)
                second = str(item[1].second)
                history = {
                    'nickname': '',
                    'article_id': item[0],
                    'title': '',
                    'readtime': year+'.'+month+'.'+day+'  '+hour+':'+minute+':'+second,
                    'agreenum': 0
                }

                article = conn.execute(f"select title,agreenum,user_account from article where article_id = '{item[0]}'")
                a=article.fetchone()

                history['title']=a[0]
                history['agreenum'] = a[1]

                wr=conn.execute(f"select nickname from user where acountname = '{a[2]}'")
                ww=wr.fetchone()

                history['nickname'] = ww[0]

                Hlist.append(history)

            print('-------------------- 历史记录 ——------------')
            print(Hlist)
            return {'history': Hlist}
    except:
        return {'status': 'NoK'}


# 根据账号、文章 id 添加历史记录
@bp.route("/posthistory",methods=['GET','POST'])
def postHistory():
    engine = db.get_engine()
    data = json.loads(request.data)
    acountname = data.get("acountname")
    article_id = data.get("article_id")
    try:
        with engine.connect() as conn:
            conn.execute(f"insert into history(account,article_id) values ('{acountname}','{article_id}')")
            return {'status':'ok'}
    except:
        return {'status':'NoK'}


# 根据账号、文章 id 清除历史记录
@bp.route("/clrhistory",methods=['GET','POST'])
def clrHistory():
    engine = db.get_engine()
    data = json.loads(request.data)
    acountname = data.get("accountname")
    article_id = data.get("article_id")
    try:
        with engine.connect() as conn:
            conn.execute(f"delete from history where account='{acountname}' and article_id='{article_id}'")
            return {'status':'ok'}
    except:
        return {'status':'NoK'}
