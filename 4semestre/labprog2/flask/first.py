from flask import Flask, request
from flask.ext import restful

app = Flask(__name__)
api = restful.Api(app)

mylist = []

class HelloWorld(restful.Resource):
    def get(self):
        return mylist
    
    def put(self):
        var = request.form['variaveis']
        mylist.append(var)
        return mylist

    def delete(self):
        name = request.form['deleting']
        if name in mylist:
            mylist.pop(name)
        #if len(mylist) > 0:
        #    mylist.pop()
        return mylist
    
    def post(self):
        f = request.form['files']
        print(f)

api.add_resource(HelloWorld, '/')
if __name__ == '__main__':
    app.run(debug=True)


#agora pra enviar coisas pro servidor:
#oops, esse programa nunca chegara nessa linha :/
put('http://localhost:5000/', data = {'variaveis' : 'teste1'})
put('http://localhost:5000/', data = {'variaveis' : 'teste2'})
put('http://localhost:5000/', data = {'variaveis' : 'teste3'})
put('http://localhost:5000/', data = {'variaveis' : 'teste4'})
