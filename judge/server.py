"""Codexam: the judge server for Programming Practice A.

Copyright (c) 2016  Naoaki Okazaki.

"""

import argparse
import collections
import logging
from logging.handlers import RotatingFileHandler
import ssl

from flask import Flask, abort, jsonify, render_template, redirect, url_for, request, flash
from flask.ext.login import LoginManager, login_user, logout_user, current_user, login_required
from database import Database
import cmdtasks

context = ssl.SSLContext(ssl.PROTOCOL_TLSv1_2)
context.load_cert_chain('server.crt', 'server.key')

app = Flask(__name__)
app.secret_key = '\xd4\xa1\x17\xf9\xa9\xa0\xd2j\t\xb3\xd8\x87N\xfb\x14\xa3\xcc\x7f\x88\xde\x19C0N'
app.config['PREFERRED_URL_SCHEME'] = 'https'
app.config['MAX_CONTENT_LENGTH'] = 64 * 1024

login_manager = LoginManager()
login_manager.init_app(app)
login_manager.login_view = 'login'

def getdb():
    return Database()

def is_admin(user):
    return user.get_group() in ('admin', 'ta')
    


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
    userid = current_user.get_id()

    if request.method == 'GET':
        app.logger.info('Account: @%s', userid)
        return render_template('account.html')

    db = getdb()
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
    app.logger.info('Home: @%s', userid)
    return render_template('home.html',tasks=tasks)

@app.route('/submit/<task_id>', methods=['GET', 'POST'])
@login_required
def submit(task_id):
    userid = current_user.get_id()
    if request.method == 'POST':
        f = request.files['source']
        filename = f.filename
        app.logger.info('Submitted a source code: %s for #%s from @%s', filename, task_id, userid)
        if f and f.filename.endswith(('.c', '.cpp', '.cxx')):
            try:
                source = f.read().decode('utf-8')
            except UnicodeError:
                app.logger.info('Unicode error: %s for #%s from @%s', filename, task_id, userid)
                flash('encoding-error')
                return redirect(url_for('home', _external=True))
    
            db = getdb()
            objectid = db.register_submission(userid, task_id, source)
            task = db.get_task(task_id)
            cmd = 'python judge.py -i {} {}'.format(str(objectid), task['judge'])
            cmdtasks.system.delay(cmd)
            return redirect(url_for('result', taskid=task_id, _external=True))

    return redirect(url_for('home', _external=True))

def render_view(userid, taskid, mode=''):
    db = getdb()
    task = db.get_task(taskid)
    result = db.get_result(userid, taskid)
    print(result)
    app.logger.info('Result %s: @%s #%s', mode, userid, taskid)
    return render_template(
        'result.html',
        userid=userid, task=task, result=result, mode=mode)

@app.route('/result/<taskid>')
@login_required
def result(taskid):
    return render_view(current_user.get_id(), taskid, 'result')

@app.route('/report/<taskid>')
@login_required
def report(taskid):
    return render_view(current_user.get_id(), taskid, 'report')

@app.route('/admin/user/<userid>')
@login_required
def admin_userhome(userid):
    if not is_admin(current_user):
        app.logger.warn('Possible attack to admin view: @%s for #%s', userid, taskid)
        abort(404)
    db = getdb()
    adminuserid = current_user.get_id()
    tasks = db.get_tasks_for_user(userid)
    app.logger.info('Home (admin: @%s): @%s', adminuserid, userid)
    return render_template('home.html', tasks=tasks)

@app.route('/admin/group/<groupid>')
@login_required
def admin_group(groupid):
    if not is_admin(current_user):
        app.logger.warn('Possible attack to admin group: @%s', current_user.get_id())
        abort(404)
    db = getdb()
    tasks = list(db.get_task_list())
    for task in tasks:
        task['num_completed'] = 0
    print(list(tasks))
    users = db.get_user_list(groupid)
    U = collections.OrderedDict((u['id'], u) for u in users)
    T = collections.OrderedDict((t['id'], t) for t in tasks)
    for userid, user in U.items():
        user['progress'] = collections.OrderedDict()
        for task in tasks:
            taskid = task['id']
            result = db.get_result(userid, taskid)
            user['progress'][taskid] = result
            T[taskid]['num_completed'] += int(0)
        user['notice'] = '' # Empty for the time being.    
    app.logger.info('Group list (@%s): %s', current_user.get_id(), groupid)
    return render_template('progress.html', users=U, tasks=tasks)

@app.route('/admin/view/<userid>/<taskid>')
@login_required
def admin_view(userid, taskid):
    if not is_admin(current_user):
        app.logger.warn('Possible attack to admin view: @%s for #%s', userid, taskid)
        abort(404)
    app.logger.info('Result view (@%s): @%s for #%s', current_user.get_id(), userid, taskid)
    return render_view(userid, taskid)

@app.route('/admin/add-user', methods=['GET','POST'])
@login_required
def admin_add_user():
    if current_user.get_group() != 'admin':
        app.logger.warn('Possible attack to add-user: @%s', current_user.get_id())
        abort(404)

    if request.method == 'GET':
        return render_template('adduser.html')

    db = getdb()
    userid = request.form['userid']
    newpass = request.form['newpass']
    group = request.form['group']
    name = request.form['name']
    if db.get_user(userid):
        app.logger.warn('Add-user: existing user specified: @%s', userid)
        return render_template('adduser.html', message='exist')

    db.add_user(userid, newpass, group, name)
    app.logger.info('Add-user: success: @%s', userid)
    return render_template('adduser.html', message='success')

@app.route('/admin/reset-user', methods=['GET','POST'])
@login_required
def admin_reset_user():
    if current_user.get_group() != 'admin':
        app.logger.warn('Possible attack to reset-user: @%s', current_user.get_id())
        abort(404)

    if request.method == 'GET':
        return render_template('resetpw.html')

    db = getdb()
    userid = request.form['userid']
    newpass = request.form['newpass']
    if not db.get_user(userid):
        app.logger.warn('Reset-user: the user does not exist: @%s', userid)
        return render_template('resetpw.html', message='unknown')

    db.reset_password(userid, newpass)
    app.logger.info('Reset-user: success: @%s', userid)
    return render_template('resetpw.html', message='success')

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Start a process of judge server.'
        )
    parser.add_argument(
        '--port', '-p', type=int, default=443,
        help='specify the port number of the server'
        )
    parser.add_argument(
        '--debug', '-d', dest='debug', action='store_true',
        help='activate the debug mode'
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

    # Start the server.
    app.run(
        host='0.0.0.0',
        debug=args.debug,
        port=args.port,
        ssl_context=context
        )
