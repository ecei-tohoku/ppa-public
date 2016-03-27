import argparse
import os
import sys

COMPILE = 'gcc -Wall {src} -lm -o {binary}'
EXECUTE = './{binary} {argv} < {stdin} 1> {stdout} 2> {stderr}'

def run(argv, binary):
    env = {
        'binary': binary,
        'argv': open(argv).readline().strip('\n'),
        'stdin': argv.replace('.argv', '.stdin'),
        'stdout': argv.replace('.argv', '.stdout'),
        'stderr': argv.replace('.argv', '.stderr'),
        }
    cmd = EXECUTE.format(**env)
    print(cmd)
    return os.system(cmd)

def compile(src):
    binary = src.replace('.c', '.bin')
    cmd = COMPILE.format(src=src, binary=binary)
    print(cmd)
    return binary if os.system(cmd) == 0 else ''

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Generate test cases.')
    parser.add_argument(
        'source', type=str,
        help='the reference source code')
    parser.add_argument(
        'argv',  type=str, nargs='+',
        help='a file describing command-line arguments')

    args = parser.parse_args()
    src = args.source
    binary = compile(src)
    if binary:
        for argv in args.argv:
            run(argv, binary)
