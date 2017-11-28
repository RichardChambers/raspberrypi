#!/usr/bin/python
# The above comment allows the shell to see what application
# this script requires to execute. This allows us to mark the
# file as executable.

# The circuit for this lesson is composed of one or more LEDs
# each of which is connected to a GPIO pin and to 3.3v power
# rail through a 200 ohm resistor.
#    | VCC | ---- |200 ohm R | ----  | >| LED | ---- | pin |

# import the necessary libraries and other components we need
# to do what we are going to do.
import RPi.GPIO as GPIO
import time

# Python RPi.GPIO uses BCM or Broadcom board pin
# numbering which is different from the wiringPi
# library numbering convention. This is a list of
# the pins we have in our circuit.
LEDPIN_LIST = [ 17, 18]

# ------     methods we are using in our application

# setup function to set up the operating environment.
# we will select GCM numbering for the setmode()
# then we indicate the GPIO pin we are using along with
# its initial level of LOW so the LED starts off unlit.
def setup():
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    for iPin in LEDPIN_LIST:
        GPIO.setup(iPin, GPIO.OUT, initial=GPIO.HIGH)


# the main routine will just loop forever turning the LED
# on and then off until the user interrupts with a control-C.
def main():
    iCount = 10
    while iCount > 0:
        for iPin in LEDPIN_LIST:
            GPIO.output(iPin, GPIO.LOW)
            print('LED On ...')
            time.sleep(0.5)

            GPIO.output(iPin, GPIO.HIGH)
            print(' LED off\n')
            time.sleep(0.5)
            pass
        iCount -= 1
        pass
    pass

# handle the keyboard interrupt by cleaning up the GPIO environment
# in order to exit our program.
def destroy():
    GPIO.output(LEDPIN, GPIO.LOW)
    GPIO.cleanup()

# ------- no more methods


# if this script is being run directly then do the
# environment setup and run our main routine until interrupted.
if __name__ == '__main__':
    setup()
    try:
        main()
    except KeyboardInterrupt:
        destroy()
