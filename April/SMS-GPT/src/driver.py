'''
    File: driver.py
    Author: Mohamed
    Date: 01/04/2023
    @Last updated: 01/04/2023
    @By Mohamed
    For: SMS Chatbot
    Purpose: This is driver program Connecting chatgpt 3.5 with AT 2 Ways SMS API
    License: GNU GPL v2.0 or Later versions
'''
from flask import Flask, request, jsonify
from chatgpt.gpt35 import chatgpt35
import json

app = Flask(__name__)

@app.route("/")
def hello_world():
    return "<p>Hello, World!s</p>"


@app.route("/sms", methods=['POST'])
def process_msm():
    data = request.get_json()
    message = data['message']
    print(message)
    
    return str(chatgpt35(message))

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port='8080')

#response = self.sms.send(str(chatgpt35(tochatgpt)), [str(tophone)] , "90762")