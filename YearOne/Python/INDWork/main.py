import requests
from flask import Flask, request, Response
import json
from flask_cors import CORS

app = Flask(__name__)

@app.route('/test', methods=['GET'])
def test():

    print("dasdasdadasdasd")
    return Response(status=200)

@app.route('/login', methods=['POST'])
def LogInVerification():
    data = request.data.decode('utf-8')
    json_data = json.loads(data)

    users = LoadUsers('../ChatServer/Users.json')
    print(type(users))

    login = json_data['login']
    password = json_data['password']

    print(login, password)

    if(login == "Rengeka" and password == "12345"):
        return Response(status=200)
    else:
        return Response(status=403)

def SignInVerification():
    print(SignInVerification)

def SendMessage():
    print(SendMessage)

def AddToFriends():
    print(AddToFriends)

def LoadUsers(filename):
    with open(filename, 'r') as file:
        data = json.load(file)
    return data['users']

def SaveUsers(users, filename):
    data = {'users': users}
    with open(filename, 'w') as file:
        json.dump(data, file, indent=4)

CORS(app)
app.run()
