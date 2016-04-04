"""Database interface for Codexam.

Copyright (c) 2016  Naoaki Okazaki

Schema for the collections.

user:
+ id: ID for the user
+ password: password (hashed string)
+ group: group (in {staff, ta, a, b, c, d})
+ name: name of the user (student ID)
+ timestamp: the timestamp when the entry is created

task:
+ id: ID for the task
+ title: title for the task
+ url: URL for the task
+ judge: test cases (*.argv) for the task

submission:
+ user: user ID
+ task: task ID
+ source: the submitted source code
+ timestamp: the timestamp when the source code is submitted
+ status: status in {queue, ok, fail, error}
+ note: message for the status
+ passed: the number of passed tests
+ compile.cmd: the command-line for compiling the source code
+ compile.returncode: the return code from the compiler
+ compile.message: the error message (STDERR) from the compiler
+ compile.timestamp: the timestamp when compiling the code
+ tests[].cid: test case ID
+ tests[].status: status in {ok, fail, timeout, error}
+ tests[].message: message for the status
+ tests[].timestamp: the timestamp when running the test case
+ tests[].argv: the command-line argument for the test case
+ tests[].stdin: the content of STDIN
+ tests[].stdout: the content of STDOUT
+ tests[].stderr: the content of STDERR

"""

import datetime
import hashlib
import json
import pymongo
from bson.objectid import ObjectId
from config import *

def pwhash(x):
    return hashlib.sha256(x).hexdigest()

def now():
    return datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')

class Database:
    def __init__(self, uri=DBURI, dbname=DBNAME):
        self.client = pymongo.MongoClient(uri)
        self.db = self.client[dbname]

    def add_user(self, user, password, group, name):
        self.db.user.insert_one(
            {'id': user, 'password': pwhash(password.encode(ENCODING)), 'group': group, 'name': name, 'timestamp': now()}
            )

    def update_password(self, user, oldpw, newpw):
        return self.db.user.update_one(
            {'id': user, 'password': pwhash(oldpw.encode(ENCODING))},
            {'$set': {'password': pwhash(newpw.encode(ENCODING))}}
            ).matched_count == 1

    def reset_password(self, user, newpw):
        return self.db.user.update_one(
            {'id': user},
            {'$set': {'password': pwhash(newpw.encode(ENCODING))}}
            ).matched_count == 1

    def authenticate_user(self, user, password):
             return self.db.user.find_one({'id': user, 'password': pwhash(password.encode(ENCODING))})

    def get_user(self, user):
        return self.db.user.find_one({'id': user})

    def get_user_list(self, group):
        return self.db.user.find({'group': group})

    def get_users(self):
        return self.db.user.find()

    def remove_users(self):
        return self.db.user.drop()

    def create_user_index(self):
        self.db.user.create_index([('id', pymongo.DESCENDING)])

    def set_task(self, tid, title, url, judge, tester):
        self.db.task.replace_one(
            {'id': tid},
            {'id': tid, 'title': title, 'url': url, 'judge': judge, 'tester': tester},
            upsert=True
            )

    def get_task(self, tid):
        return self.db.task.find_one({'id': tid})

    def get_task_list(self):
        return self.db.task.find().sort('id', 1)

    def get_tasks_for_user(self, user):
        tasks = []
        for row in self.get_task_list():
            row['submission'] = self.get_result(user, row['id'])
            tasks.append(row)
        return tasks

    def register_submission(self, userid, taskid, source):
        d = self.db.submission.insert_one({
            'user': userid,
            'task': taskid,
            'source': source,
            'timestamp': now(),
            'status': 'queue'
            })
        return d.inserted_id if d.acknowledged else None

    def replace_submission(self, objectid, d):
        self.db.submission.replace_one({'_id': ObjectId(objectid)}, d)

    def get_submission(self, objectid):
        return self.db.submission.find_one({'_id': ObjectId(objectid)})

    def get_result(self, userid, taskid):
        rows = self.db.submission.find(
            {'user': userid, 'task': taskid}).sort('timestamp', -1).limit(1)
        return rows[0] if rows.count() >= 1 else None

    def index_submission(self):
        self.db.submission.create_index('user')
        self.db.submission.create_index('task')
        self.db.submission.create_index([('timestamp', -1)])
