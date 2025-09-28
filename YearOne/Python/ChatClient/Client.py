import requests
import json
from tkinter import *

def TestRequest():
    url = 'http://127.0.0.1:5000/test'
    response = requests.get(url)
    print(f"Status code: {response.status_code}")

def CreateChat(user, username):
    url = 'http://127.0.0.1:5000/createChat'
    data = {'user': user, 'username': username}
    response = requests.post(url, json=data)

    if response.status_code != 200:
        print('failed to create chat')

def GetChatData(username):
    url = 'http://127.0.0.1:5000/getChats'
    response = requests.post(url, data=username)

    if response.status_code == 200:
        response_data = response.json()
        print(response_data)
        return response_data
    else:
        print("Ошибка:", response.status_code)

def CheckLoginData(objects): # DELETE THIS
    login = objects[1].get()
    password = objects[3].get()
    if login and password:
        LoginRequest(objects)

def LoginRequest(login, password):
    url = 'http://127.0.0.1:5000/login'
    data = {'username': login, 'password': password}
    response = requests.post(url, json=data)

    if response.status_code == 200:
        print("Успешный вход")
        return response
        #OpenChatWindow(root)
    else:
        print(f"Ошибка: {response.status_code}")
        return response

"""def CheckAddressee(objects, root):
    url = 'http://127.0.0.1:5000/checkAddressee'
    data = objects[0].get()
    headers = {'Content-Type': 'text/plain'}

    response = requests.post(url, data=data, headers=headers)

    if response.status_code == 200:
        print("Существующий адресат")
        #OpenChatWindow(root)
    else:
        print(f"Ошибка: {response.status_code}")"""

def GetMessages(ID):
    url = 'http://127.0.0.1:5000/getChat'
    data = {'ID': ID}

    response = requests.post(url, json=data)

    print(response)

    if response.status_code == 200:
        messages = response.json()  # Предполагается, что сервер возвращает JSON с сообщениями
        # Дальнейшая обработка полученных сообщений
        return messages
    else:
        print(f"Ошибка: {response.status_code}")
        return None

def SendMessage(author, message,ID):
    url = 'http://127.0.0.1:5000/addMessages'
    data = {'author': author, 'message': message,'ID': ID}

    response = requests.post(url, json=data)
    if response.status_code == 200:
        response = requests.post(url, json=data)
        return response
    else:
        print(f"Ошибка: {response.status_code}")
        return None