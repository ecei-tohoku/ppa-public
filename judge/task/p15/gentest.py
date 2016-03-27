import random
import subprocess
import sys

DIGITS = (12, 13, 20, 21)

def random_number(N):
    s = ''
    for i in range(N):
        s += '{}'.format(random.randint(0, 9))
    return s

def run(s):
    p = subprocess.Popen('./a.out', shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, close_fds=True)
    p.stdin.write('{}\n'.format(s).encode('utf-8'))
    p.stdin.close()
    return p.stdout.read().decode('utf-8')

i = 1
for digit in DIGITS:
    with open('t%02d.stdin' % i, 'w') as fo:
        while 1:
            s = random_number(digit)
            if run(s).strip() == 'true':
                fo.write('{}\n'.format(s))
                break
        i += 1
    with open('t%02d.stdin' % i, 'w') as fo:
        while 1:
            s = random_number(digit)
            if run(s).strip() == 'false':
                fo.write('{}\n'.format(s))
                break
        i += 1

