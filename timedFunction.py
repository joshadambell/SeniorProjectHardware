import threading
import time

def f():
    print "hello"
    # call f() again in 60 seconds
    threading.Timer(10, f).start()

# start calling f now and every 60 sec thereafter
f()