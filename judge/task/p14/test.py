import io
import json
import math
import sys

EPS = 0.02

def read_data(fi):
    D = []
    for line in fi:
        line = line.strip('\r\n')
        fields = line.split(' ')
        assert len(fields) == 4
        D.append((int(fields[0]), float(fields[1]), float(fields[2]), float(fields[3])))
    return D

def compare_data(X, Y):
    assert len(X) == len(Y)
    for i in range(len(X)):
        assert X[i][0] == Y[i][0]
        assert math.fabs(X[i][1] - Y[i][1]) < EPS
        assert math.fabs(X[i][2] - Y[i][2]) < EPS
        assert math.fabs(X[i][3] - Y[i][3]) < EPS

if __name__ == '__main__':
    doc = json.load(sys.stdin)
    X = read_data(io.StringIO(doc['stdout_eval']))
    Y = read_data(io.StringIO(doc['stdout_gold']))
    compare_data(X, Y)
    assert doc['stderr_eval'] == doc['stderr_gold']
