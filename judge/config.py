# Temporary directory.
TEMP = ''

# Encoding.
ENCODING = 'utf-8'

# Command-line for compiling source codes.
COMPILE = 'gcc {src} -Wall -o {bin} -lm'

# Command-line for running the code.
RUN = "LD_PRELOAD=/home/okazaki/install/EasySandbox/EasySandbox.so {bin} {argv}"
