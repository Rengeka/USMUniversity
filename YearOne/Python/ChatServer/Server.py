import requests
from flask import Flask, request, Response, jsonify
import json
from flask_cors import CORS

app = Flask(__name__)


@app.route('/test', methods=['GET'])
def test():
    return Response(status=200)

@app.route('/checkUpdate', methods=['GET'])
def CheckUpdate():
    data = request.json

    users = LoadUsers('Users.json')

    chats = LoadChats('Users.json')

    response = {'userResponse':0, 'chatResponse':0, 'currentUserUpdate' : -1, 'currentChatUpdate' : -1}
    for user in users:
        print(user['update'])
        if user['username'] == data['username'] and user['update'] != data['userUpdate']:
            response['currentUserUpdate'] = user['update']
            response['userResponse'] = 1
            break

    for chat in chats:
        print(chat['update'])
        if chat['ID'] == data['chatID'] and chat['update'] != data['chatUpdate']:
            response['currentChatUpdate'] = chat['update']
            response['chatResponse'] = 1
            break

    return jsonify(response)


"""@app.route('/getMessages', methods=['POST'])
def GetMessages():
    data = request.data.decode('utf-8')
    chats = LoadChats('Users.json')"""




@app.route('/addMessages', methods=['POST'])
def AddMessages():
    data = request.json

    with open('Users.json', 'r') as file:
        dtBase = json.load(file)

    newMessage = {
        "user": data['user'],
        "text": data['message']
    }

    update = 0;

    for chat in dtBase['chats']: #chats:
        if (chat['ID'] == data['ID']):
            chat['messages'].append(newMessage)
            chat['update'] += 1 #chats['update']
            break


    with open('Users.json', "w") as json_file:
        json.dump(dtBase, json_file)

    return Response(status=200)


@app.route('/createChat', methods=['POST'])
def CreateChat():
    data = request.json

    with open('Users.json', 'r') as file:
        dtBase = json.load(file)

    print(data['username'])
    userExists = bool(0)

    for user in dtBase['users']:
        if data['username'] == user['username']:
            userExists = bool(1)
            break

    isNew = bool(1)

    if not userExists or not isNew:
        return Response(status=403)

    #Check if such a chat exists
    for chat in dtBase['chats']:
        if (chat['users'][0] == data['user'] and chat['users'][1] == data['username']) or (chat['users'][1] == data['user'] and chat['users'][0] == data['username']):
            #return Response(status=403)
            isNew = bool(0)
            break

    print(isNew)
    print(userExists)

    ID = 0
    for chat in dtBase['chats']:
        if chat['ID'] >= ID:
            ID = chat['ID'] + 1

    new_chat = {
        "ID": ID,
        "users": [data['user'], data['username']],
        "messages": []
    }

    dtBase["chats"].append(new_chat)

    for user in dtBase["users"]:
        if (user['username'] == data['user']):
            user['chats'].append(ID)
            user['update'] += 1

    for user in dtBase["users"]:
        if (user['username'] == data['username']):
            user['chats'].append(ID)
            user['update'] += 1

    with open('Users.json', "w") as json_file:
        json.dump(dtBase, json_file)

    return Response(status=200)

def LoadUsers(filename):
    with open(filename, 'r') as file:
        data = json.load(file)
    return data['users']

def LoadChats(filename):
    with open(filename, 'r') as file:
        data = json.load(file)
    return data['chats']

@app.route('/getChat', methods=['POST'])
def GetChat():
    data = request.data.decode('utf-8')
    print(data)
    data = json.loads(data)
    chats = LoadChats('Users.json')
    for chat in chats:
        if (chat['ID'] == data['ID']):
            return jsonify(chat), 200

@app.route('/getChats', methods=['POST'])
def GetChats():
    data = request.data.decode('utf-8')
    users = LoadUsers('Users.json')

    if data:
        for user in users:
            if user['username'] == data:
                chats = LoadChats('Users.json')
                chosenChats = []

                for chat in chats:
                    for ch in user['chats']:
                        if ch == chat['ID']:
                            chosenChats.append([chat['ID'], chat['users'][1] if chat['users'][0] == data else chat['users'][0]])#, chat['messages']])

                return jsonify(chosenChats), 200
            else:
                return Response(status=403)
    else:
        return Response(status=403)



@app.route('/login', methods=['POST'])
def LogInVerification():
    data = request.json
    users = LoadUsers('Users.json')

    if data:
        for user in users:
            if user['username'] == data['username'] and user['password'] == data['password']:
                """chats = LoadChats('Users.json')
                chosenChats = []

                for chat in chats:
                    for ch in user['chats']:
                        if ch == chat['ID']:
                            chosenChats.append(chat)"""

                #print(chosenChats)


                return Response(status=200) #jsonify(chosenChats), 200
            else:
                return Response(status=403)
    else:

        return Response(status=403)


#Delete????
@app.route('/checkAddressee', methods=['POST'])
def CheckAddressee():
    data = request.data.decode('utf-8')
    users = LoadUsers('Users.json')


    if data:
        for user in users:
            if user['username'] == data:
                print("Allowed user")
                break

        return Response(status=200)
    else:
        # Если данные отсутствуют, возвращаем ошибку доступа (код 403)
        return Response(status=403)

CORS(app)
app.run()
