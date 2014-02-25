import urllib2
import json
import random
import threading
import time
import RPi.GPIO as GPIO

DEVICE_ID = 1
URL = 'http://10.0.1.5:3000/mattress_data'
GPIO.setmode(GPIO.BCM)
GPIO.setup(7, GPIO.IN)
peoplecount = 0

while(1):
        presence = GPIO.input(7)
        if(presence):
            threading.Timer(10, sendData).start()
            peoplecount += 1
            time.sleep(1.5)
        time.sleep(1)


def sendData():
	
	print "send"

	values = dict(mattress_datum=(dict(device_id=DEVICE_ID, 
    					 		   type='how many', 
    					           data=peoplecount, 
    					           units='count', 
    						       date=time.strftime("%Y-%m-%d %H:%M:%S"))))

	try:
		req = urllib2.Request(URL)
		req.add_header('Content-Type', 'application/json')

		rsp = urllib2.urlopen(req, json.dumps(values))
		content = rsp.read()
		print rsp.getcode()
	except:
		print "Error in sending data"
