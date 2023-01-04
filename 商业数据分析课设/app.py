from flask import Flask
from models import ShowData
from flask_cors import CORS
app = Flask(__name__)
app.register_blueprint(ShowData.show_bp)
# r'/*' 是通配符，让本服务器所有的 URL 都允许跨域请求
CORS(app, resources=r'/*')

@app.route('/')
def hello_world():  # put application's code here
    return 'Hello World!'


if __name__ == '__main__':
    app.debug=(True)
    app.run()
