## Installation

### Python

+ Python 3.3 or later
+ MongoDB 3.0 or later
+ Redis

pip install

```
$ pip install Flask
$ pip install flask-login
$ pip install pymongo
$ pip install pyyaml
$ pip install celery
$ pip install redis
```

### EasySandbox

https://github.com/daveho/EasySandbox

EasySandbox is a library for sandboxing untrusted executables on Linux, introducing the following limitations when running executables:

+ They cannot make any system calls except exit(), sigreturn(), read() and write() to already-open file descriptors ([seccomp](https://en.wikipedia.org/wiki/Seccomp)). In other words, they cannot use fopen() nor open() but only STDIN, STDOUT, STDERR for data exchange.
+ They can allocate memory up to a fixed amount (default: 8MB).

We do not have to change the source code, but can force the limitations to executables.

Fetch, compile, and test the source code.

```
$ cd ~/install/
$ git clone https://github.com/daveho/EasySandbox.git
$ cd EasySandbox/
$ make
$ make runtests
```

The judge server requires the shared library `EasySandbox.so` for sandboxing.

### Generating server keys for SSL.

Put key files (`server.crt`, `server.key`) into `conf/ssl/`. For security reasons, please DO NOT forget to remove group/other access permissions from these files.

```
    chmod 600 conf/ssl/server.crt conf/ssl/server.key
```

#### Acquiring server certificate using TAINS/UPKI

TAINS provides an online service to obtain a server certificate from NII (UPKI電子証明書発行サービス). See https://www2.tains.tohoku.ac.jp/others/certificate for further details.

#### For debug purposes

```
$ openssl genrsa 2048 > server.key
$ openssl req -new -key server.key > server.csr
$ openssl x509 -days 3650 -req -signkey server.key < server.csr > server.crt
```

See http://d.hatena.ne.jp/ozuma/20130511/1368284304 for further details. Use this method only for *debug purposes*.

## Starting the server

### Create a configuration file

Duplicate `conf/config-template.yaml` and edit it accordingly. Suppose we save this file to `conf/config.yaml`. For security reasons, you must remove a group/other access, e.g.:

    chmod 600 conf/config.yaml

### Run

Starting a job queue for making judges (up to 4 processes to evaluate).

```
$ celery -A cmdtasks worker --loglevel=info --concurrency 4
```

Starting the Web server.

```
$ python server.py conf/config.yaml
```
