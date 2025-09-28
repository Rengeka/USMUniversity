import requests

from flask import Flask, request
from flask_socketio import SocketIO, emit
import json

app = Flask(__name__)
app.config['SECRET_KEY'] = '1234567890'
socketio = SocketIO(app)

activeSessions = []

@socketio.on('GetMessage')
def GetMessage(data):
    print("Message recieved")
    print(data)



    if (data['ID'] != None) and (data['text'] != None) and (data['user'] != None):

        print(data['ID'])

        dtBase = LoadDatabase('Users.json')

        for chat in dtBase['chats']:
            if chat['ID'] == data['ID']:
                message = {
                    'text': data['text'],
                    'user': data['user']
                }
                chat['messages'].append(message)


                with open('Users.json', "w") as json_file:
                    json.dump(dtBase, json_file)


                for user in chat['users']:
                    for session in activeSessions:
                        if user == session['user']:
                            SendMessageUpdate(session['sessionID'], {'ID': chat['ID'], 'messages': chat['messages']})
                            break

                break

def SendMessageUpdate(session, data):
    emit('GetMessages', data, room=session)
    print('Update was sent')

def SendUpdate(session, data):
    emit('GetUpdate', data, route=session)
    print('Update was sent')

@socketio.on('ChatRequest')
def ChatRequest(data):
    dtBase = LoadDatabase('Users.json')
    print(data)

    userExists = bool(0)

    for user in dtBase['users']:
        if data['username'] == user['username']:
            userExists = bool(1)
            break

    isNew = bool(1)

    for chat in dtBase['chats']:
        if (chat['users'][0] == data['user'] and chat['users'][1] == data['username']) or (
                chat['users'][1] == data['user'] and chat['users'][0] == data['username']):
            isNew = bool(0)
            break

    print(userExists, isNew)

    if userExists and isNew:
        ID = 0
        for chat in dtBase['chats']:
            if chat['ID'] >= ID:
                ID = chat['ID'] + 1

        chat = {
            "ID": ID,
            "users": [data['user'], data['username']],
            "messages": []
        }

        dtBase["chats"].append(chat)

        for user in dtBase["users"]:
            if (user['username'] == data['user']):
                user['chats'].append(ID)

        for user in dtBase["users"]:
            if (user['username'] == data['username']):
                user['chats'].append(ID)

        with open('Users.json', "w") as json_file:
            json.dump(dtBase, json_file)

        print(chat['users'])
        for user in dtBase['users']:
            for session in activeSessions:
                if user['username'] == session['user']:
                    chats = []
                    for id in user['chats']:
                        for ch in dtBase['chats']:
                            if ch['ID'] == id:
                                chats.append(ch)
                                break

                    SendChatUpdate(session['sessionID'],{"ID": chat['ID'],
                    "name": chat['users'][0] if chat['users'][0] != data['user'] else chat['users'][1],
                    "messages": chat['messages']})

                    """{'chats': chats}"""

                    break

def SendChatUpdate(session, data):
    emit('GetChats', data, room=session)
    pass

@socketio.on('LoginVerification')
def LoginRequest(data):
    users = LoadUsers('Users.json')
    print("LOGIN VERIFICATION")


    if data:
        isFound = False
        for user in users:
            if user['username'] == data['login'] and user['password'] == data['password']:
                isFound = True

                activeSessions.append({'sessionID': request.sid, 'user': data['login']})

                chats = LoadChats('Users.json')
                chosenChats = []

                for chat in chats:
                    for ch in user['chats']:
                        if ch == chat['ID']:
                            chosenChats.append({"ID" : chat['ID'],
                                                "name" : chat['users'][0] if chat['users'][0] != data['login'] else chat['users'][1],
                                                "messages" : chat['messages']})

                print("fulfilled")

                emit('VerifyLogin',{"status": "fulfilled", "chats": chosenChats}, route=data['sessionID'])
                break
        if isFound :
            print("rejected")
            emit('VerifyLogin', {"status": "rejected"}, route=data['sessionID'])
    else:
        print("no data")
        emit('VerifyLogin', {"status": "rejected"}, route=data['sessionID'])

def LoadUsers(filename):
    with open(filename, 'r') as file:
        data = json.load(file)
    return data['users']

def LoadChats(filename):
    with open(filename, 'r') as file:
        data = json.load(file)
    return data['chats']

def LoadDatabase(filename):
    with open('Users.json', 'r') as file:
        dtBase = json.load(file)
    return dtBase


if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5000, allow_unsafe_werkzeug=True)