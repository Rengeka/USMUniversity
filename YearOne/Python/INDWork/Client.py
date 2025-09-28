import requests
import json

url = 'http://127.0.0.1:5000/test'
data = {}
response = requests.post(url, data)
print(response.status_code)


"""from tkinter import *
import requests
import json

def CheckLoginData(objects, root):
    url = 'http://127.0.0.1:5000/test'
    data = {'login': 'asd', 'password': 'asda'}
    response = requests.post(url, data)
    print(response.status_code)


    login = objects[1].get()
    password = objects[3].get()
    if login and password:
        SendLoginRequest(objects, root)

def SendLoginRequest(objects, root):
    url = 'http://127.0.0.1:5000/login'
    data = {'login': objects[1].get(), 'password': objects[3].get()}
    response = requests.post(url, data=json.dumps(data))

    if response.status_code == 200:
        print("Успешный вход!")
        OpenChatWindow(root)
    else:
        print("Неудачная попытка входа. Код ошибки:", response.status_code)

def OpenChatWindow(root):
    for obj in root.winfo_children():
        obj.destroy()

    label = Label(root, text="ETASDTASGDHASDHAHD")
    label.pack()

def Start():
    root = Tk()
    root.title("Chat")
    root.geometry("300x250")

    loginLabel = Label(root, text="Enter your name:")
    loginLabel.pack()

    loginEntry = Entry(root)
    loginEntry.pack()

    passwordLabel = Label(root, text="Enter your password:")
    passwordLabel.pack()

    passwordEntry = Entry(root)
    passwordEntry.pack()

    button = Button(root, text="Log in", command=lambda: CheckLoginData([loginLabel, loginEntry, passwordLabel, passwordEntry, button], root))
    button.pack()
    root.mainloop()




Start()"""
