from flask import Flask, request
from flask.ext.restful import Resource, Api

app = Flask(__name__)
api = Api(app)

todos = {}

class TodoSimple(Resource):
    def get(self, todo_ide):
        return {todo_ide: todos[todo_ide]}

    def put(self, todo_ide):
        todos[todo_ide] = request.form['data']
        return {todo_ide: todos[todo_ide]}

api.add_resource(TodoSimple, '/<string:todo_ide>')

if __name__ == '__main__':
    app.run(debug=True)
