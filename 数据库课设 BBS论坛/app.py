import json
import config
from exts import db, mail
from flask import Flask, request, jsonify, session, g, make_response
from blueprint1 import user_bp,viewbp,article_bp,admin_bp

app = Flask(__name__)
from flask_cors import CORS

CORS(app, resources=r'/*')
app.config.from_object(config)
db.init_app(app)
mail.init_app(app)

# 注册单文件蓝图
app.register_blueprint(user_bp)
app.register_blueprint(viewbp)
app.register_blueprint(article_bp)
app.register_blueprint(admin_bp)


@app.route("/")
def register():
    session['user_id']='123'
    return "666"


if __name__ == '__main__':
    app.run()
