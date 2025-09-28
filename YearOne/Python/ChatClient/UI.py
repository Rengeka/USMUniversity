from kivy.uix.screenmanager import Screen
from kivymd.app import MDApp
from kivymd.uix.button import MDRectangleFlatButton
from kivy.core.window import Window
from kivy.lang import Builder
from kivy.uix.label import Label
from kivy.uix.boxlayout import BoxLayout
from kivymd.uix.textfield import MDTextField
from kivymd.uix.button import MDFlatButton
from kivymd.uix.label import MDLabel
from kivy.uix.textinput import TextInput
from kivy.uix.scrollview import ScrollView
from kivymd.uix.list import OneLineListItem
from kivy.uix.popup import Popup
from kivymd.uix.button import MDFlatButton, MDRaisedButton
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.uix.floatlayout import FloatLayout

from kivy.uix.screenmanager import Screen
from kivymd.app import MDApp
from kivy.uix.boxlayout import BoxLayout
from kivymd.uix.textfield import MDTextField
from kivymd.uix.button import MDFlatButton, MDRaisedButton
from kivymd.uix.label import MDLabel
from kivy.uix.popup import Popup
from kivy.uix.screenmanager import ScreenManager
from kivy.uix.widget import Widget
from kivy.uix.gridlayout import GridLayout

import Client as Requests
import socketio


class LoginPage(Screen):
    def __init__(self, chatSelectionPage, **kwargs):
        super().__init__(**kwargs)
        self.chatSelectionPage = chatSelectionPage

        layout = BoxLayout(orientation='vertical', padding=40, spacing=20)
        self.username = MDTextField(hint_text="Username", required=True)
        self.password = MDTextField(hint_text="Password", required=True, password=True)
        self.login_button = MDFlatButton(text="Login", on_press=self.check_login)
        self.error_label = MDLabel(theme_text_color="Secondary", halign="center")
        layout.add_widget(self.username)
        layout.add_widget(self.password)
        layout.add_widget(self.login_button)
        layout.add_widget(self.error_label)
        self.add_widget(layout)

    def check_login(self, *args):
        if self.username.text and self.password.text:
            # Предположим, что у вас есть метод Requests.LoginRequest для отправки запроса на сервер
            response = Requests.LoginRequest(self.username.text, self.password.text)
            if response.status_code:
                if response.status_code == 200:
                    self.error_label.text = "Login successful"
                    app = MDApp.get_running_app()
                    screen_manager = app.root
                    self.chatSelectionPage.user = self.username.text
                    self.chatSelectionPage.reload_chats_and_buttons()
                    screen_manager.current = "chat_selection"
                elif response.status_code == 403:
                    self.error_label.text = "Access denied"
                else:
                    self.error_label.text = "Unpredictable error"
            else:
                self.error_label.text = "No connection to the server"
        else:
            self.error_label.text = "Incorrect username or password"


class ChatSelectionPage(Screen):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.user = ""

        self.layout = BoxLayout(orientation='horizontal')

        self.buttonLayout = BoxLayout(orientation='horizontal')
        self.chat_list_layout = BoxLayout(orientation='vertical')
        self.message_area_layout = ScrollView()
        self.message_area_grid = GridLayout(cols=1, spacing=10, size_hint_y=None)
        self.message_area_grid.bind(minimum_height=self.message_area_grid.setter('height'))
        self.message_area_layout.add_widget(self.message_area_grid)
        self.chatsLabel = MDLabel(text="Your chats!", halign="center")
        self.chat_list_layout.add_widget(self.chatsLabel)

        self.chats = []
        self.messages = []

        self.addButton = MDRaisedButton(text="Add Chat", on_press=lambda x: self.ShowAddChatPopup())
        self.message_input = MDTextField(hint_text="Type your message here")

        self.show_chats()
        self.show_buttons()
        self.layout.add_widget(self.chat_list_layout)
        self.layout.add_widget(self.message_area_layout)
        self.add_widget(self.layout)

    def reload_chats_and_buttons(self):
        chatData = Requests.GetChatData(self.user)
        self.delete_all_chats()
        self.delete_buttons()
        for chat in chatData:
            chatItem = OneLineListItem(text=chat[1])
            self.chats.append(chatItem)

        self.reloadMessages(1)

        self.show_chats()
        self.show_buttons()

    def reloadMessages(self, chat_id):
        chat = Requests.GetMessages(int(chat_id))
        print(chat)
        for message in chat['messages']:
            self.addMessage(message['text'], message['user'])

    def delete_all_chats(self):
        for chat in self.chats:
            self.chat_list_layout.remove_widget(chat)
        self.chats = []

    def delete_buttons(self):
        self.layout.remove_widget(self.addButton)
        self.layout.remove_widget(self.message_input)

    def show_chats(self):
        for chat in self.chats:
            self.chat_list_layout.add_widget(chat)

    def show_buttons(self):
        self.layout.add_widget(self.message_input)
        self.layout.add_widget(self.addButton)

    def enter_chat(self, *args):
        pass

    def CreateAddChatPopup(self):
        content = BoxLayout(orientation='vertical')
        text_field = MDTextField(hint_text="Enter chat name")
        add_button = MDRaisedButton(text="Add", on_press=lambda x: self.addChat(text_field.text))
        content.add_widget(text_field)
        content.add_widget(add_button)
        self.popup = Popup(title="Add Chat", content=content, size_hint=(None, None), size=(300, 250))

    def ShowAddChatPopup(self):
        self.CreateAddChatPopup()
        self.popup.open()

    def CloseAddChatPopup(self):
        self.popup.dismiss()

    def addChat(self, chatName):
        Requests.CreateChat(self.user, chatName)
        self.reload_chats_and_buttons()
        self.CloseAddChatPopup()

    def AddMessage(self, message, author):
        message_label = MDLabel(
            text=f"{author}: {message}",
            halign="left" if author != self.user else "right",
            size_hint_y=None,
            height="40dp",
            padding=("10dp", "5dp")
        )
        self.message_area_grid.add_widget(message_label)

    def SendMessage(self, message, chatID):
        Requests.SendMessage(self.user , message, chatID)

        self.reload_chats_and_buttons()



class MyApp(MDApp):
    def build(self):
        chat_selection_page = ChatSelectionPage(name="chat_selection")
        login_page = LoginPage(chat_selection_page, name="login")
        screen_manager = ScreenManager()
        screen_manager.add_widget(login_page)
        screen_manager.add_widget(chat_selection_page)
        return screen_manager



if __name__ == "__main__":
    MyApp().run()
