"""Job queue for shell commands using Celery.

Copyright (c) 2016  Naoaki Okazaki.

This worker simply runs a shell command in a job queue
maintained by Celery. Start the worker process with:

```
$ celery -A cmdtasks worker --concurrency 4 --loglevel=info
```

The worker will use four CPUs at maximum (`--concurrency 4`).

"""

import os
from celery import Celery
from config import BROKER

app = Celery('cmdtasks', broker=BROKER)

@app.task
def system(cmd):
    os.system(cmd)
