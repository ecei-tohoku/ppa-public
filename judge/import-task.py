import sys
import yaml
from database import *

db = Database()
tasks = yaml.load(sys.stdin)

for task in tasks:
    assert 'id' in task
    assert 'title' in task
    assert 'url' in task
    assert 'judge' in task
    tester = task.get('tester', '')
    print('{} {}'.format(task['id'], task['title']))
    db.set_task(task['id'], task['title'], task['url'], task['judge'], tester)
