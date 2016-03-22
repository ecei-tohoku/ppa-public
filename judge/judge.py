import argparse
import sys

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Test a source code with test cases.'
        )
    parser.add_argument(
        '--user', '-u',
        help='specify a user identifier'
        )
    parser.add_argument(
        '--task', '-t',
        help='specify a task identifier',
        )
    parser.add_argument(
        'commands', metavar='N', type=str, nargs='+',
        help='a command-line for running the code'
        )

    args = parser.parse_args()
    print args.accumulate(args.integers)
