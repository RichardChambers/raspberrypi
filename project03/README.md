Raspberry Pi Starter Kit Lesson 6: Breathing LED
  http://osoyoo.com/2017/06/26/pi3-breathing-led/
  
This project explores using the pwmWrite() function of the wiringPi library to make an LED pulse in brightness.
PWM is an acronym for Pulse Width Modulation and is when an electrical signal is a series of pulses with the
voltage level varying between a low voltage and a high voltage and back to low voltage to generate a series
of pulses. The amount of time a particular voltage level is held before changing to the other voltage level
is the width of the pulse.

This project is using the 3.3v GPIO #18 pin so the high voltage is 3.3v and the low voltage is 0.0v.

WARNING: The wiringPi library requires that a program that is manipulating the
         PWM setting of GPIO#18 must be run with sudo. Not using sudo will result in
         a number of weird behaviors including crash of the operating system.

NOTE: The only pin on the Raspberry Pi 3 which supports hardware PWM is GPIO #18.
      This project will only work if the LED circuit is using GPIO #18.

Here is a 8 minute YouTube video that explains PWM and how it works with an LED:
  How to control LED brightness using PWM https://www.youtube.com/watch?v=jFI7Ahf0lZ8
  
Here is an introductory video about PWM using electronic parts:
  What is PWM? Pulse Width Modulation tutorial! https://www.youtube.com/watch?v=YmPziPfaByw

