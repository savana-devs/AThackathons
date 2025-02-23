from flask import Flask, jsonify
from sms.send import SMS
app = Flask(__name__)

@app.route('/')
def hello():
    SMS().send()
    return jsonify({"message": "message sent"})


@app.route('/last-sms')
def fetch_sms():
    sms = SMS().fetch_last_sms()
    if sms is None:
        return jsonify({"message": "No sms messages in your inbox."})
    return jsonify(sms)

@app.route('/buzz')
def buzz():
    # some logic to buzz or to not buzz
    return "Buzz"
@app.route('/status')
def status():
    return jsonify({"status": "Server is running"})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5001, debug=True)