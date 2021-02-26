import time
from grove_rgb_lcd import *
import grovepi
from grovepi import *
boton = 4
sensor = 2
#A0 sensor
pinMode(boton,"INPUT")
temp = grovepi.temp(sensor,'1.1')

setRGB(0,0,255)
while True:
	try:
		button_status = digitalRead(boton)
		if button_status:
			setRGB(0,255,0)
			#temp = 23
			setText("Temp = " + str(temp) + " C")
			time.sleep(.5)
		else:		
			setRGB(255,0,0)
			setText("Presiona el boton")
			time.sleep(.5)
	except KeyboardInterrupt:
		setRGB(126,126,0)
		setText("Adios")
		break
	except (IOError,TypeError) as e:
		print("Error")
