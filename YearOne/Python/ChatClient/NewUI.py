from kivy.uix.screenmanager import Screen
from kivymd.app import MDApp
from kivy.uix.boxlayout import BoxLayout
from kivymd.uix.textfield import MDTextField
from kivymd.uix.button import MDFlatButton, MDRaisedButton
from kivymd.uix.label import MDLabel
from kivy.uix.popup import Popup
from kivy.uix.screenmanager import ScreenManager
from kivy.uix.gridlayout import GridLayout
from kivy.uix.scrollview import ScrollView
from kivymd.uix.list import OneLineListItem


import NewClient as client
from kivy.clock import Clock

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
            client.LoginRequest(self.username.text, self.password.text)
            self.chatSelectionPage.username = self.username.text
        else:
            self.error_label.text = "Incorrect username or password"

    def check_login_response_wrapper(self, response):
        Clock.schedule_once(lambda dt: self.check_login_response(response))

    def check_login_response(self, response):
        print("CHECKED")
        if response:
            if response["status"] == "fulfilled":
                self.error_label.text = "Login successful"
                app = MDApp.get_running_app()
                screen_manager = app.root
                self.chatSelectionPage.user = self.username.text
                self.chatSelectionPage.reloadChats(response['chats'])
                self.chatSelectionPage.reloadMessages(response['chats'][0]['messages'])
                self.chatSelectionPage.chatsData = response['chats']
                #self.chatSelectionPage.currentChat = response['chats'][0]['ID']

                screen_manager.current = "chat_selection"
                self.opacity = 0
            elif response["status"] == "rejected":
                self.error_label.text = "Access denied"
            else:
                self.error_label.text = "Unpredictable error"
        else:
            self.error_label.text = "No connection to the server"

class ChatSelectionPage(Screen):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.chats = []
        self.messages = []
        self.chatsData = []
        self.currentChat = 0

        self.username = None


        self.layout = BoxLayout(orientation='vertical')
        self.chatLayout = BoxLayout(orientation='horizontal', size_hint_y=0.8)
        self.buttonsLayout = BoxLayout(orientation='horizontal', size_hint_y=0.2)

        self.messagesLay = ScrollView()
        self.message_area_grid = GridLayout(cols=1, spacing=10, size_hint_y=None)
        self.message_area_grid.bind(minimum_height=self.message_area_grid.setter('height'))
        self.messagesLay.add_widget(self.message_area_grid)

        self.scroll_view = ScrollView(size_hint_x=0.3)
        self.chatsLay = GridLayout(cols=1, size_hint=(1, None), spacing=10)
        self.chatsLay.bind(minimum_height=self.chatsLay.setter('height'))


        #self.scroll_view.add_widget(self.chatsLay)

        self.CreateAddChatPopup()
        self.message_input = MDTextField(hint_text="Type your message here", on_text_validate=self.send_message)
        self.addButton = MDRaisedButton(text="Add Chat", halign="left", on_press=lambda x: self.ShowAddChatPopup())
        self.chatGrid = GridLayout(cols=1, size_hint=(1, None), spacing=10)
        self.chatGrid.add_widget(self.addButton)
        self.chatGrid.add_widget(self.chatsLay)



        #self.chatsLay.add_widget(self.addButton)
        self.scroll_view.add_widget(self.chatGrid)
        self.chatLayout.add_widget(self.scroll_view)
        self.chatLayout.add_widget(self.messagesLay)
        self.layout.add_widget(self.chatLayout)
        self.layout.add_widget(self.buttonsLayout)

        self.message_area_grid.add_widget(MDLabel(halign="center"))
        self.buttonsLayout.add_widget(MDLabel(halign="center"))
        self.buttonsLayout.add_widget(self.message_input)

        self.add_widget(self.layout)

    def CreateAddChatPopup(self):
        content = BoxLayout(orientation='vertical')
        text_field = MDTextField(hint_text="Enter chat name")
        add_button = MDRaisedButton(text="Add", on_press=lambda x: self.addChat(text_field.text))
        content.add_widget(text_field)
        content.add_widget(add_button)
        self.popup = Popup(title="Add Chat", content=content, size_hint=(None, None), size=(300, 250))

    def ShowAddChatPopup(self):
        self.popup.open()

    def CloseAddChatPopup(self):
        self.popup.dismiss()

    def addChat(self, login):
        client.StartChat(self.username, login)
        pass

    def send_message(self, instance):
        client.SendMessage(self.currentChat, instance.text, self.username)
        instance.text = ""

    """def GetChats(data):
        Clock.schedule_once(lambda dt: ChatSelectionPage.reloadChats(data))"""

    def reloadChats(self, chats):

        """for chat in self.chats:
            self.chatsLay.remove_widget(chat)"""

        self.chatsLay.clear_widgets()

        self.chats = []

        print(chats)



        for chat in chats:
            item = OneLineListItem(text=chat['name'])
            self.chatsLay.add_widget(item)
            self.chats.append(chat)
            item.bind(on_release=lambda instance, chatID=chat['ID']: self.on_item_pressed(chatID))
            print("sada")


    def on_item_pressed(self, chatID):
        print("ID : ", chatID)
        for chat in self.chatsData:
            if chat['ID'] == chatID:
                self.reloadMessages(chat['messages'])
                self.currentChat = chatID
                break

    def reload_messages(self, ID, messages):
        Clock.schedule_once(lambda dt: self.reloadChatMessages(ID, messages))

    def reloadChatMessages(self, chatID, chatMessages):
        for chat in self.chatsData:
            if chat['ID'] == chatID:
                chat = chatMessages
                if self.currentChat == chatID:
                    self.reloadMessages(chatMessages)
                break

    def reloadMessages(self, messages):

        for message in self.messages:
            self.message_area_grid.remove_widget(message)
        self.messages = []

        for message in messages:
            message_label = MDLabel(
                text=f"{message["user"]}: {message["text"]}",
                halign="left" if message["user"] != self.user else "right",
                size_hint_y=None,
                height="40dp",
                padding=("10dp", "5dp")
            )
            self.message_area_grid.add_widget(message_label)
            self.messages.append(message_label)

class MyApp(MDApp):
    def build(self):
        chat_selection_page = ChatSelectionPage(name="chat_selection")
        login_page = LoginPage(chat_selection_page)

        client.SetLoginPage(login_page)
        client.SetChatSelectionPage(chat_selection_page)

        screen_manager = ScreenManager()
        screen_manager.add_widget(login_page)
        screen_manager.add_widget(chat_selection_page)

        return screen_manager


if __name__ == "__main__":
    app = MyApp()

    app.run()
