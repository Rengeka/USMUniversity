import socketio
from kivy.clock import Clock

sio = socketio.Client()

def SetLoginPage(value):
    global loginPage
    loginPage = value
def SetChatSelectionPage(value):
    global ChatSelectionPage
    ChatSelectionPage = value

@sio.event
def TEST(data):
    print(data)

"""def connect():
    sio.emit('GetSessionID', {'sessionID': sio.sid})
    print('Connected to server')"""

@sio.event
def GetChats(data):
    Clock.schedule_once(lambda dt: ChatSelectionPage.reloadChats(data))

"""def GetChats(data):
    #ChatSelectionPage.reloadChats(data)

    ChatSelectionPage.GetChats(data)"""

@sio.event
def GetUpdate(data):
    print('Update data:', data)
def StartChat(user, login):
    print("Chat request")
    sio.emit('ChatRequest', {'user': user, 'username': login})
def LoginRequest(login, password):
    print("LOGIN REQUEST")
    sio.emit('LoginVerification',  {'login': login, 'password': password, 'sessionID': sio.sid})
@sio.event
def VerifyLogin(response):
    print(response)
    loginPage.check_login_response_wrapper(response)
def SendMessage(ID, text, user):
    sio.emit('GetMessage',  {'ID': ID, 'text': text, 'user' : user})
    print('Message was sent')
@sio.event()
def GetMessages(data):
    print("I've got a message")
    print(data)
    ChatSelectionPage.reload_messages(data['ID'], data['messages'])


sio.connect('http://127.0.0.1:5000')
#sio.connect('http://localhost:5000')