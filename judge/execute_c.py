"""Compile and execute a C source code.

Copyright (c) 2016  Naoaki Okazaki

"""

import logging as lg
import os
import subprocess
import tempfile
import threading

# Encoding.
ENCODING = 'utf-8'

# Command-line for compiling source codes.
COMPILE = 'gcc {src} -std=c99 -Wall -o {bin} -lm'

# Command-line for running the code.
RUN = "LD_PRELOAD=/home/okazaki/install/EasySandbox/EasySandbox.so exec {bin} {argv}"

def strip_easysandbox(s):
    magic = '<<entering SECCOMP mode>>\n'
    if s.startswith(magic):
        return s[len(magic):]

class Command(object):
    """Execute a shell command with timeout."""

    def __init__(self, cmd, fi):
        self.cmd = cmd
        self.fi = fi
        self.process = None
        self.stdoutdata = b''
        self.stderrdata = b''

    def run(self, timeout):
        def target():
            self.process = subprocess.Popen(self.cmd, shell=True, stdin=self.fi, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            (self.stdoutdata, self.stderrdata) = self.process.communicate()

        thread = threading.Thread(target=target)
        thread.start()

        thread.join(timeout)
        if thread.is_alive():
            self.process.terminate()
            thread.join()
            return False
        return True

class ExecuteC:
    """Execute a C source code."""

    def __init__(self, src, prefix='exec', suffix='.c'):
        """ Construct an instance for compiling and running a code.

        Params:
            src: The source code
            prefix: The pefix for the names of the temporary files.
            suffix: The suffix for the source code.

        """
        # Create a temporary file for the source code.
        fd, name = tempfile.mkstemp(prefix=prefix, suffix=suffix)
        fo = os.fdopen(fd, "w")
        fo.write(src)
        fo.close()        

        # Filenames for the source code and binary.
        self.src = name
        self.bin = name + '.bin'

        lg.debug('src: {}'.format(self.src))
        lg.debug('bin: {}'.format(self.bin))

    def __del__(self):
        """ Destructs the instance with removing temporary files.

        """
        if os.path.exists(self.src):
            os.remove(self.src)
            self.src = None
        if os.path.exists(self.bin):
            os.remove(self.bin)
            self.bin= None
    
    def compile(self):
        """ Compile the source code.

        Returns:
            str: The commane-line for compling the source code.
            int: Return value from the compiler.
            str: Error message.

        """
        cmd = COMPILE.format(src=self.src, bin=self.bin)
        p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdoutadta, stderrdata = p.communicate()
        lg.debug('Compile ({}): {}'.format(p.returncode, cmd))
        return cmd, p.returncode, stderrdata.decode('utf-8')

    def run(self, argv='', fi=None, timeout=5.0):
        """ Run the program.

        Params:
            argv: Optional argument for the program
            fi: File object for STDIN
            timeout: Timeout in seconds.

        Returns:
            str: status ('timeout' if the execution timeouted)
            int: the return value from the binary.
            str: the content from STDOUT.
            str: the content from STDERR.

        """
        cmd = RUN.format(bin=self.bin, argv=argv)
        lg.debug('Run {}'.format(cmd))
        c = Command(cmd, fi)
        finished = c.run(timeout)
        lg.debug('Run ({}): {}'.format(c.process.returncode, cmd))
        if finished:
            return (
                '',
                c.process.returncode,
                strip_easysandbox(c.stdoutdata.decode(ENCODING, 'ignore')),
                strip_easysandbox(c.stderrdata.decode(ENCODING, 'ignore')),
                )
        else:
            lg.debug('Terminated with timeout: {}'.format(cmd))
            return ('timeout', -1, '', '')
            
if __name__ == '__main__':
    logger = lg.getLogger()
    logger.setLevel(lg.DEBUG)

    E = ExecuteC('#include <stdio.h>\nint main() {\n printf("OK");\nreturn 0;\n}\n')
    cmd, retval, message = E.compile()
    lg.info('cmd ({}): {}'.format(retval, cmd))
    lg.info('compile-message: {}'.format(message))

    status, retval, stdout, stderr = E.run()
    lg.info('status: {}'.format(status))
    lg.info('retval: {}'.format(retval))
    lg.info('stdout: {}'.format(stdout))
    lg.info('stderr: {}'.format(stderr))
