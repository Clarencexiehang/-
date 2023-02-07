from exts import db
from datetime import datetime

class UserModel(db.Model):
    id = db.Column(db.Integer,primary_key=True,autoncrement=True)
    accountName = db.Column(db.String(100),nullable=False,unique=True)
    nickName = db.Column(db.String(100),nullable=False,unique=True)
    phone = db.Column(db.String(100), nullable=True, unique=False)
    email = db.Column(db.String(100), nullable=False, unique=True)
    password = db.Column(db.String(100), nullable=False)
    join_time = db.Column(db.DateTime, default=datetime.now)