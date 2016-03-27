import argparse
import datetime
import os
import sys
import execute_c

def now():
    return str(datetime.datetime.now())

def test(S, C):
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
                R['status'] = 'timeout'
                S['tests'].append(R)
                continue
            else:
                R['returncode'] = returncode
                R['stdout'] = stdout
                R['stderr'] = stderr
        except EnvironmentError:
            S['status'] = 'error'
            S['note'] = 'Failed to read the stdin: {}'.format(fin)
            return

        # Test the stdout.
        if os.path.exists(fout):
            try:
                with open(fout) as fi:
                    if fi.read() != R['stdout']:
                        R['status'] = 'fail'
            except EnvironmentError:
                S['status'] = 'error'
                S['note'] = 'Failed to read the stdout: {}'.format(fout)
                return

        # Test the stderr.
        if os.path.exists(ferr):
            try:
                with open(ferr) as fi:
                    if fi.read() != R['stderr']:
                        R['status'] = 'fail'
            except EnvironmentError:
                S['status'] = 'error'
                S['note'] = 'Failed to read the stderr: {}'.format(ferr)
                return

        # Successful if nothing was set to the status.
        if not R['status']:
            R['status'] = 'ok'
        S['tests'].append(R)

    # Summarize the test results.
    S['passed'] = sum(1 for r in S['tests'] if r['status'] == 'ok')
    S['status'] = 'ok' if S['passed'] == len(C) else 'fail'

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Test a source code with test cases.'
        )
    parser.add_argument(
        '-i', '--objectid', type=str,
        help='specify the ObjectId for the submission'
        )
    parser.add_argument(
        'argvs', metavar='N', type=str, nargs='+',
        help='a command-line argument for running the code'
        )
    args = parser.parse_args()

    if args.objectid:
        import database
        db = database.Database()
        S = db.get_submission(args.objectid)
        test(S, args.argvs)
        db.replace_submission(args.objectid, S)
    else:
        S = {'source': sys.stdin.read()}
        test(S, args.argvs)
        print(S)
