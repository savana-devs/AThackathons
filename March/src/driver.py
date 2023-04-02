'''
    File: driver/py
    Author: Mohamed
    Date: 01/04/2023
    @Last updated: 01/04/2023
    @By Mohamed
    For: SMS Chatbot
    Purpose: This is driver programan Connecting chatgpt 3.5 with AT 2 Ways SMS API
    License: GNU GPL v2.0 or Later versions
'''
import africastalking
from chatgpt.gpt35 import chatgpt35
import time

class SMS:
    def __init__(self):

        self.username = "sandbox"
        self.api_key = "YOUR-API-KEY"

        africastalking.initialize(self.username, self.api_key)
        self.sms = africastalking.SMS
    def fetch_sms_sync(self):
        last_msg = "let-this-be-like-this-ever"
        while(True):
            print("Here we go... start")

            

            try:
                last_received_id = 0;

                while True:
                    MessageData = self.sms.fetch_messages(last_received_id)

                    messages = MessageData['SMSMessageData']['Messages']
                    if len(messages) == 0:
                        print ('No sms messages in your inbox.')
                        break
                    '''You don't need to worry we will take the last message from inbox'''
                    #We got u covered
                    for message in messages:
                        tochatgpt = message["text"]
                        tophone = message["from"]

                        last_received_id = int(message['id'])
                    print(tochatgpt)
                    if last_msg == tochatgpt:
                        print("Do not send, and sleeping")

                    elif last_msg != tochatgpt:
                        response = self.sms.send(str(chatgpt35(tochatgpt)), [str(tophone)] , "90762")
                        last_msg = tochatgpt
                        print("Send now, and sleeping")
                        time.sleep(2)

            except Exception as e:
                print ('Encountered an error while fetching: %s' % str(e))

if __name__ == '__main__':
    SMS().fetch_sms_sync()