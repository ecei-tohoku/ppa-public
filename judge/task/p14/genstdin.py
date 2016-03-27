import os
import sys

CURRENCIES = ('USD', 'GBP', 'EUR', 'CHF')
START_DATE = '2011/1/4'
END_DATE = '2016/1/4'
OFFSET = 20

if __name__ == '__main__':
    fi = sys.stdin
    fi.readline()
    fi.readline()
    fields = fi.readline().strip('\n').split(',')
    F = {c: fields.index(c) for c in CURRENCIES}
    
    D = []
    begin = None
    end = None
    for line in fi:
        fields = line.strip('\n').split(',')
        if fields[0] == START_DATE:
            begin = len(D)
        if fields[0] == END_DATE:
            end = len(D)
        row = dict(date=fields[0])
        for c, f in F.items():
            row[c] = fields[f]
        D.append(row)

    for i, c in enumerate(CURRENCIES):
        fname = 't%02d.stdin' % (i+1)
        with open(fname, 'w') as fo:
            for t in range(begin-OFFSET+1, end):
                fo.write('{}\n'.format(D[t][c]))
