#!/usr/bin/python
# The above comment allows the shell to see what application
# this script requires to execute. This allows us to mark the
# file as executable.

# this script assumes the following simple circuit with an active buzzer.
#    GPIO #18 pin connected to buzzer cathode or negative leg (short one).
#    buzzer anode or positive leg (long one) connected to 3.3v

# we set GPIO #18 HIGH to prevent power flowing to the buzzer, turning
# it off. we set GPIO #18 LOW to allow power to flow through the buzzer
# turning it on.

# import the necessary libraries and other components we need
# to do what we are going to do.
import RPi.GPIO as GPIO
import time

# set GPIO #1 as buzzer pin, Python RPi.GPIO uses BCM
# or Broadcom board pin numbering which is different
# from the wiringPi library numbering convention.
LEDPIN = 18


# ------     methods we are using in our application

# setup function to set up the operating environment.
# we will select GCM numbering for the setmode()
# then we indicate the GPIO pin we are using along with
# its initial level of HIGH so the buzzer starts off inactive.
def setup():
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(LEDPIN, GPIO.OUT, initial=GPIO.HIGH)

# make the buzzer oscillate for a given period of time
# make sure the buzzer is turned off before we return.
def buzz(iPin, iCount, fDelay):
    while (iCount > 0):
        # turn off the buzzer.
        GPIO.output (iPin, GPIO.HIGH)
        time.sleep(fDelay)
        
        # turn on the buzzer.
        GPIO.output (iPin, GPIO.LOW)
        time.sleep(fDelay)
        iCount -= 1
        pass
    # turn off the buzzer as we leave this function.
    GPIO.output (iPin, GPIO.HIGH)


# the main routine will just loop forever turning the LED
# on and then off until the user interrupts with a control-C.
def main():
    buzz (LEDPIN, 70, 0.01)
    time.sleep (0.50)

    buzz (LEDPIN, 30, 0.1)
    time.sleep (0.50)
    destroy()

# handle the keyboard interrupt by cleaning up the GPIO environment
# in order to exit our program.
def destroy():
    GPIO.output(LEDPIN, GPIO.HIGH)
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
