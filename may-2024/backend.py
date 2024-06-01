from flask import Flask, jsonify, request
import mysql.connector

dataBase = mysql.connector.connect(
  host ="localhost",
  user ="hacker",
  passwd ="hacker",
  database = "vikobaplus"
)
cursorObject = dataBase.cursor()
app = Flask(__name__)

@app.route('/')
def hello_world():
    return 'Hello World'

@app.route('/user/auth/login')

#login
def login():

    return jsonify({'login' : 'success'})

@app.route('/user/auth/registration')

def registration():

    return jsonify({'status' : 'succeeded'})


# view users
@app.route('/users')
def view_users():

    users = {'user1': 'sabina', 'user2': 'mohamed'}

    return jsonify({'data': users})

#list all groups
@app.route('/groups')
def view_groups():

    groups = {'group1': {'name': 'sabina'}, 'group2': {'name': 'moo'} }

    return jsonify({'data': groups})

@app.route('/group/create', methods=["GET", "POST"])

def create_group():

    return 'group created successfully'

#Join the group
@app.route('/group/join')

def join_group():

    return jsonify({'message': 'successful joined ABC Vicoba group'})


#get user details
@app.route('/user/{id}')

def user_details():

    return jsonify({'data' : 'user data goes here'})


#request loan
@app.route('/loan/request', methods=["POST", "GET"])

def request_loan():
    #chek loan type
    '''
    airtime via AT
    data via AT
    money via AzamPay


    Also check eigibility for applicant
    '''
    return jsonify({'message' : 'load requested successifully'})


if __name__ == '__main__':

    app.run(debug=True)