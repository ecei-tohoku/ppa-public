import sys
from database import *

db = Database()
for line in sys.stdin:
    fields = line.strip('\n').split('\t')
    assert len(fields) == 4
    db.add_user(fields[0], fields[1], fields[2], fields[3])
