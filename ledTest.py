from nanpy import (ArduinoApi, SerialManager)
from time import sleep

ledPin = 13

try:
    connection = SerialManager()
    a = ArduinoApi(connection = connection)
except:
    print("Failed to connect to Arduino")

# Setup the pinModes as if we were in the Arduino IDE
a.pinMode(ledPin, a.OUTPUT)

try:
    while True:
        a.digitalWrite(ledPin, a.HIGH)
        print("LED on")
        sleep(1)

        a.digitalWrite(ledPin, a.LOW)
        print("LED off")
        sleep(1)
except:
    a.digitalWrite(ledPin, a.LOW)
