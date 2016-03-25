from celery import Celery
import os

app = Celery('cmdtasks', broker='redis://localhost')

@app.task
def system(cmd):
    os.system(cmd)
