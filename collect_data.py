import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(7, GPIO.IN)

counter = 0

while(1):
    presence = GPIO.input(7)
    if(presence):
	print counter
        counter += 1
        time.sleep(1.5)
    time.sleep(1)
