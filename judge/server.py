import argparse
import logging
from logging.handlers import RotatingFileHandler
import ssl
import subprocess

from flask import Flask, abort, jsonify, render_template, redirect, url_for, request, flash
from flask.ext.login import LoginManager, login_user, logout_user, current_user, login_required
from database import Database
import cmdtasks

#context = ssl.SSLContext(ssl.PROTOCOL_TLSv1_2)
#context.load_cert_chain('server.crt', 'server.key')

app = Flask(__name__)
app.secret_key = '\xd4\xa1\x17\xf9\xa9\xa0\xd2j\t\xb3\xd8\x87N\xfb\x14\xa3\xcc\x7f\x88\xde\x19C0N'
app.config.update(dict(PREFERRED_URL_SCHEME='https'))

login_manager = LoginManager()
login_manager.init_app(app)
login_manager.login_view = 'login'

def getdb():
    return Database()

class User:
    def __init__(self, id, group):
        self.id = id
        self.group = group

    def is_authenticated(self):
        return True

    def is_active(self):
        return True
 
    def is_anonymous(self):
        return False
 
    def get_id(self):
        return self.id

    def get_group(self):
        return self.group

@login_manager.user_loader
def load_user(id):
    db = getdb()
    user = db.get_user(id)
    return User(id, user['group'])

@app.route('/')
def index():
    return render_template('login.html')

@app.route('/login', methods=['GET','POST'])
def login():
    if request.method == 'GET':
        return render_template('login.html')

    db = getdb()
    username = request.form['username']
    password = request.form['password']
    user = db.authenticate_user(username, password)
    if not user:
        app.logger.info('Failed to login: @%s', username)
        return render_template('login.html', error=True)

    app.logger.info('Login successfully: @%s', username)
    registered_user = User(username, user['group'])
    login_user(registered_user)
    return redirect(url_for('home', _external=True))

@app.route("/logout")
@login_required
def logout():
    app.logger.info('Logout: @%s', current_user.get_id())
    logout_user()
    return redirect(url_for('login', _external=True))

@app.route('/account', methods=['GET','POST'])
@login_required
def account():
    if request.method == 'GET':
        app.logger.info('Account: @%s', userid)
        return render_template('account.html')

    db = getdb()
    userid = current_user.get_id()
    curpass = request.form['curpass']
    newpass = request.form['newpass']
    if not db.update_password(userid, curpass, newpass):
        app.logger.info('Failed to change the password: @%s', userid)
        return render_template('account.html', message='incorrect')

    app.logger.info('Changed the password successfully: @%s', userid)
    return render_template('account.html', message='success')

@app.route('/home')
@login_required
def home():
    db = getdb()
    userid = current_user.get_id()
    tasks = db.get_tasks_for_user(userid)
    print(tasks)
    app.logger.info('Home: @%s', userid)
    return render_template('home.html', tasks=tasks)

@app.route('/submit/<task_id>', methods=['GET', 'POST'])
@login_required
def submit(task_id):
    userid = current_user.get_id()
    if request.method == 'POST':
        f = request.files['source']
        filename = f.filename
        app.logger.info('Submitted a source code: %s for #%s from @%s', filename, task_id, userid)
        if f and f.filename.endswith('.c'):
            source = f.read().decode('utf-8')
            db = getdb()
            objectid = db.register_submission(userid, task_id, source)
            task = db.get_task(task_id)
            cmd = 'python judge.py -d ppa2016 -c result -i {} {}'.format(str(objectid), task['judge'])
            cmdtasks.system.delay(cmd)
            #retcode = subprocess.call(cmd, shell=True)
            return redirect(url_for('result', taskid=task_id, _external=True))

    return redirect(url_for('logout', _external=True))

def render_view(userid, taskid, mode=''):
    db = getdb()
    task = db.get_task(taskid)
    result = db.get_result(userid, taskid)
    print(result)
    app.logger.info('Result %s: @%s #%s', mode, userid, taskid)
    return render_template(
        'result.html',
        task=task, result=result, mode=mode)

@app.route('/result/<taskid>')
@login_required
def result(taskid):
    return render_view(current_user.get_id(), taskid, 'result')

@app.route('/report/<taskid>')
@login_required
def report(taskid):
    return render_view(current_user.get_id(), taskid, 'report')

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Start a process of judge server.'
        )
    parser.add_argument(
        '--debug', '-d', dest='debug', action='store_true',
        help='Enable the debugging mode'
        )
    parser.add_argument(
        '--log', '-l', type=str,
        help='Log to a file'
        )
    args = parser.parse_args()

    if args.log:
        handler = RotatingFileHandler(args.log, maxBytes=100000000, backupCount=100)
        formatter = logging.Formatter(
            "[%(asctime)s] {%(pathname)s:%(lineno)d} %(levelname)s - %(message)s")
        handler.setLevel(logging.INFO)
        handler.setFormatter(formatter)
        app.logger.addHandler(handler)
    app.run(host='0.0.0.0', debug=args.debug)#, ssl_context=context)
