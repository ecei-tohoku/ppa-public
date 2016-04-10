import argparse
import sys
from database import *

parser = argparse.ArgumentParser(
    description='Import user accounts from a TSV file (from STDIN).'
        )
parser.add_argument(
    'config', type=str, default='config.yaml',
    help='specify the configuration file (in YAML) for running the server'
    )
parser.add_argument(
    '--clean', '-c', action='store_true',
    help='remove all user accounts beforehand'
    )
args = parser.parse_args()

config = yaml.load(open(args.config))
db = Database(uri=config['judge']['dburi'], dbname=config['judge']['dbname'])

if args.clean:
    db.remove_users()

for line in sys.stdin:
    fields = line.strip('\n').split('\t')
    assert len(fields) == 4
    if not db.get_user(fields[0]):
        print('Add: {}'.format(fields[0]))
        db.add_user(fields[0], fields[1], fields[2], fields[3])
    else:
        print('WARNING: skipping the existing user: {}'.format(fields[0]))

db.create_user_index()
