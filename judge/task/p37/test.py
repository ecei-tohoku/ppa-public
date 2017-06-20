import sys
import json

def read(fi):
    D = []
    for line in fi:
        line = line.strip('\n')
        if not line:
            continue
        D.append(sorted(line.split(' ')))
    return D

d = json.load(sys.stdin)
DT = read(d['stdout_eval'].split('\n'))
DR = read(d['stdout_gold'].split('\n'))
sys.exit(0 if DT == DR else 1)
