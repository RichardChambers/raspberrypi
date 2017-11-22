
Raspberry Pi Starter Kit Lesson 7: Raspberry Pi Button Control LED
  http://www.osoyoo.com/2017/06/27/raspberry-pi-starter-kit-lesson-7/

This lesson combines two simple circuits which provide a button as an input
source to the Raspberry Pi and an LED to light or not depending on the
button state.

The button press circuit for the input uses a pull up resistor, 10K ohms, 
connected to the 3.3v power connected to one pole of a button press switch
with the other pole of the switch connected to GND, ground. The resistor
is also connected to GPIO #17 which will sense whether the button is pressed
or not.

The LED circuit is connected to 3.3v power through a 200 ohm resistor and
then connected to GPIO #18.

The idea is that GPIO #17 will be set to input and will be HIGH from the
3.3v power until the button is pressed. When the button is pressed the
input will go to LOW.

For the LED GPIO #18 will be set to HIGH which will block the current
flow from the 3.3v power turning the LED off. When the Raspberry Pi sets
GPIO #18 to LOW, this will allow the 3.3v power to flow turning the LED on.
