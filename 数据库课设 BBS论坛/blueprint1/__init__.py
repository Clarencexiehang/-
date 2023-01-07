from flask import Flask,Blueprint
from .user import bp as user_bp
from .view import bp as viewbp
from .article import article_bp as article_bp
from .admin import bp as admin_bp

bp1=Blueprint('use',import_name=__name__,static_folder='static1',template_folder='templates')
from . import view
