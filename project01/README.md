This is the source code for lesson #3 from the Osoyoo website.

Raspberry Pi Starter Kit Lesson 3: Prepare GPIO Tool-WiringPi Utility at URL:
  http://osoyoo.com/2017/06/22/intall-wiringpi/
  
This lesson involves a simple LED circuit with a resistor to limit the current in order to protect the LED from damage by too much current.

The circuit is powered by GPIO #17 being set to HIGH to turn the LED on and set the pin LOW to turn it off.

The purpose of this lesson is to do a short introduction to building a circuit and to:
* test that the breadboard connections are good
* test that the wiringPi library is available and working

See this brief explanation about LED polarity. Since a Light Emitting Diode is a diode, it allows electricity to flow only one way so
if you have the LED in the circuit incorrectly, the LED will not light even if GPIO #17 is HIGH.
  https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
  
