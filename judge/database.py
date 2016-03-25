import datetime
import hashlib
import json
import pymongo
from bson.objectid import ObjectId

def pwhash(x):
    return hashlib.sha256(x).hexdigest()

def now():
    return str(datetime.datetime.now())

class Database:
    def __init__(self, uri='mongodb://localhost:27017/', dbname='ppa2016'):
        self.client = pymongo.MongoClient(uri)
        self.db = self.client[dbname]

    def add_user(self, user, password, group, name):
        self.db.user.insert_one(
            {'user': user, 'password': pwhash(password), 'group': group, 'name': name, 'timestamp': now()}
            )

    def update_password(self, user, oldpw, newpw):
        return self.db.user.update_one(
            {'user': user, 'password': pwhash(oldpw)},
            {'$set': {'password': pwhash(newpw)}}
            ).modified_count == 1

    def authenticate_user(self, user, password):
        return self.db.user.find_one({'user': user, 'password': pwhash(password)})

    def get_user(self, user):
        return self.db.user.find_one({'user': user})

    def get_users(self):
        return self.db.find()

    def set_task(self, tid, title, url, judge):
        self.db.task.replace_one(
            {'id': tid},
            {'id': tid, 'title': title, 'url': url, 'judge': judge},
            upsert=True
            )

    def get_task(self, tid):
        return self.db.task.find_one({'id': tid})

    def get_tasks_for_user(self, user):
        tasks = []
        for row in self.db.task.find():
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
