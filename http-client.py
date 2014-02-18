import urllib2
import json
import random
import threading
import time

DEVICE_ID = 1
URL = 'http://localhost:3000/mattress_data'


def sendData():
	count = random.randrange(1, 30)
	print "send"
	values = dict(mattress_datum=(dict(device_id=DEVICE_ID, 
    					 		   type='how many', 
    					           data=count, 
    					           units='seconds', 
    						       date='date')))

	req = urllib2.Request(URL)
	req.add_header('Content-Type', 'application/json')

	rsp = urllib2.urlopen(req, json.dumps(values))
	content = rsp.read()
	print rsp.getcode()

	threading.Timer(10, sendData).start()

# start calling f now and every 60 sec thereafter
sendData()