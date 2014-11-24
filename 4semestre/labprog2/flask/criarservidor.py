from flask import Flask, request
from flask.ext import restful

app = Flask(__name__)
api = restful.Api(app)

text = 'no!'

@app.route('/')
def get():
    return 'lalalal'

@app.route('/<string:var>')
def getlegal(var):
    text = var
    return text

@app.route('/teste', methods = ['POST'])
def my_post():
    f ='lala'
    print(f)



#api.add_resource(ServerCreator, '/')
if __name__ == '__main__':
    app.run(debug = True)
