"""Configuration for Codexam.

Copyright (c) 2016  Naoaki Okazaki.

"""

# Temporary directory.
TEMP = ''

# Encoding.
ENCODING = 'utf-8'

# Command-line for compiling source codes.
COMPILE = 'gcc {src} -Wall -o {bin} -lm'

# Command-line for running the code.
RUN = "LD_PRELOAD=/home/okazaki/install/EasySandbox/EasySandbox.so exec {bin} {argv}"

# URI for MongoDB.
DBURI = 'mongodb://localhost:27017/'

# Database name.
DBNAME = 'ppa2016'

# Broker for the job queue (Celery).
BROKER = 'redis://localhost'
