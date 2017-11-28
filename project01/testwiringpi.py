#!/usr/bin/python
# The above comment allows the shell to see what application
# this script requires to execute. This allows us to mark the
# file as executable.

# import the necessary libraries and other components we need
# to do what we are going to do.
import RPi.GPIO as GPIO
import time

# set GPIO #0 as LED pin, Python RPi.GPIO uses BCM
# or Broadcom board pin numbering which is different
# from the wiringPi library numbering convention.
LEDPIN = 17


# ------     methods we are using in our application

# setup function to set up the operating environment.
# we will select GCM numbering for the setmode()
# then we indicate the GPIO pin we are using along with
# its initial level of LOW so the LED starts off unlit.
def setup():
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(LEDPIN,GPIO.OUT,initial=GPIO.LOW)


# the main routine will just loop forever turning the LED
# on and then off until the user interrupts with a control-C.
def main():
    while True:
        GPIO.output(LEDPIN,GPIO.HIGH)
        print('LED On ...')
        time.sleep(0.5)

        GPIO.output(LEDPIN,GPIO.LOW)
        print(' LED off\n')
        time.sleep(0.5)
        pass
    pass

# handle the keyboard interrupt by cleaning up the GPIO environment
# in order to exit our program.
def destroy():
    GPIO.output(LEDPIN,GPIO.LOW)
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
