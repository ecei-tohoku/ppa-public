import sys
import yaml
from database import *

config = yaml.load(open(sys.argv[1]))
db = Database(uri=config['judge']['dburi'], dbname=config['judge']['dbname'], dbuser=config['judge']['dbuser'], dbpass=config['judge']['dbpass'])
tasks = yaml.load(sys.stdin)

for task in tasks:
    assert 'id' in task
    assert 'title' in task
    assert 'url' in task
    assert 'judge' in task
    tester = task.get('tester', '')
    excludes = task.get('excludes', [])
    print('{} {}'.format(task['id'], task['title']))
    db.set_task(task['id'], task['title'], task['url'], task['judge'], tester, excludes)
