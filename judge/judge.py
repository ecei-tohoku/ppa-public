import argparse
import datetime
import json
import os
import sys
import subprocess
import execute_c

def now():
    return datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')

def do_test(stdout_eval, stdout_gold, stderr_eval, stderr_gold, tester=None):
    if tester is not None:
        # Encode the test case.
        J = json.dumps({
            'stdout_eval': stdout_eval,
            'stdout_gold': stdout_gold,
            'stderr_eval': stderr_eval,
            'stderr_gold': stderr_gold
            })

        # Run the test program
        p = subprocess.Popen(tester, shell=True, stdin=subprocess.PIPE)
        p.stdin.write(J.encode('utf-8'))
        p.stdin.close()
        return p.wait() == 0

    else:
        # Exact match.
        if stdout_gold is not None and stdout_eval != stdout_gold:
            return False
        if stderr_gold is not None and stderr_eval != stderr_gold:
            return False
        return True

def test(S, C, tester):
    """

    Input:
        source (str): the source code.

    Outupt:
        compile (dict):
            returncode: the return value from the compiler.
            message: the error message (STDERR) from the compiler.
            timestamp: the timestamp of the compilation.
        status (str): 'ok', 'fail', or 'internal error'
        note (str): the detailed message about the status.
        tests (list):
            cid: the testcase identifier.
            status: 'ok', 'fail', or 'timeout'
            argv: the command-line argument.
            timestamp: the timestamp of the execusion.
            returncode: the return code from the program.
            stdin: the input for STDIN.
            stdout: the output from STDOUT.
            stderr: the output from STDERR.

    """
    # Initialize (or reset) the submission object.
    S['note'] = ''
    S['passed'] = 0
    S['tests'] = []

    # Determine the prefix.
    prefix = 'exec'
    if 'user' in S and 'task' in S:
        prefix += '_{}_{}_'.format(S['user'], S['task'])
    
    # Compile the code.
    E = execute_c.ExecuteC(S['source'], prefix=prefix)
    cmd, returncode, message = E.compile()
    S['compile'] = dict(
        cmd=cmd,
        returncode=returncode,
        message=message,
        timestamp=now()
        )
    if returncode != 0:
        S['status'] = 'fail'
        S['note'] = 'Failed to compile the source code.'
        return

    # Test the source code.
    for fargv in C:
        R = dict(cid=os.path.basename(fargv).replace('.argv', ''), status='')
        fin = fargv.replace('.argv', '.stdin')
        fout = fargv.replace('.argv', '.stdout')
        ferr = fargv.replace('.argv', '.stderr')

        # Read the command argument.
        try:
            with open(fargv) as fi:
                R['argv'] = fi.readline().strip('\n')
        except EnvironmentError:
            S['status'] = 'error'
            S['note'] = 'Failed to read the command-line argument: {}'.format(fargv)
            return

        # Run the code.
        try:
            with open(fin) as fi:
                R['stdin'] = fi.read()
            fi = open(fin) if os.path.exists(fin) else None
            status, returncode, stdout, stderr = E.run(R['argv'], fi)
            R['timestamp'] = now()
            if status == 'timeout':
                # When a timeout occurs, do not continue the tests because
                # it is very likely to have timeouts again with the same code.
                R['status'] = 'timeout'
                S['tests'].append(R)
                break
            else:
                R['returncode'] = returncode
                R['stdout'] = stdout
                R['stderr'] = stderr
        except EnvironmentError:
            S['status'] = 'error'
            S['note'] = 'Failed to read the stdin: {}'.format(fin)
            return

        # Test case.
        stdout_eval = R['stdout']
        stdout_gold = None
        stderr_eval = R['stderr']
        stderr_gold = None

        # Read the gold-standard for STDOUT
        if os.path.exists(fout):
            try:
                with open(fout) as fi:
                    stdout_gold = fi.read()
            except EnvironmentError:
                S['status'] = 'error'
                S['note'] = 'Failed to read the stdout: {}'.format(fout)
                return

        
        # Read the gold-standard for STDERR
        if os.path.exists(ferr):
            try:
                with open(ferr) as fi:
                    stderr_gold = fi.read()
            except EnvironmentError:
                S['status'] = 'error'
                S['note'] = 'Failed to read the stderr: {}'.format(ferr)
                return

        # Test the case.
        if do_test(stdout_eval, stdout_gold, stderr_eval, stderr_gold, tester):
            R['status'] = 'ok'
        else:
            R['status'] = 'fail'

        S['tests'].append(R)

    # Summarize the test results.
    S['passed'] = sum(1 for r in S['tests'] if r['status'] == 'ok')
    S['status'] = 'ok' if S['passed'] == len(C) else 'fail'

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Test a source code with test cases.'
        )
    parser.add_argument(
        '-d', '--dbname', type=str,
        help='specify the ObjectId for the submission'
        )
    parser.add_argument(
        '-i', '--objectid', type=str,
        help='specify the ObjectId for the submission'
        )
    parser.add_argument(
        '-t', '--tester', type=str,
        help='specify a command-line to test an output'
        )
    parser.add_argument(
        'argvs', metavar='N', type=str, nargs='+',
        help='a command-line argument for running the code'
        )
    args = parser.parse_args()

    if args.objectid:
        import database
        #sys.stderr.write('{} {}: {}\n'.format(args.dbname, args.objectid, args.tester))
        db = database.Database(dbname=args.dbname)
        S = db.get_submission(args.objectid)
        test(S, args.argvs, args.tester)
        db.replace_submission(args.objectid, S)
    else:
        S = {'source': sys.stdin.read()}
        test(S, args.argvs, args.tester)
        print(json.dumps(S, indent=2))
