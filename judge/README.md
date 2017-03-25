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

```
$ openssl genrsa 2048 > server.key
$ openssl req -new -key server.key > server.csr
$ openssl x509 -days 3650 -req -signkey server.key < server.csr > server.crt
```

See http://d.hatena.ne.jp/ozuma/20130511/1368284304

## Starting the server

Starting a job queue for making judges.

```
$ celery -A cmdtasks worker --loglevel=info --concurrency 4
```

Starting the Web server.
```
$ python server.py
```
