Lesson 9: Drive a Relay to Control LED
    http://osoyoo.com/2017/06/28/raspberry-pi-relay-led/
    
This lesson is particularly interesting to me after seeing what an automatic coffee pot looks
like when torn down. I had an older automatic cone filter coffee maker with a caraf that
after I replaced it with a new one, I took apart.

Inside I found a small, dedicated micro-controller which operated a standard line voltage relay
so that the micro-controller could switch the line voltage to a heating unit in order to
heat the water for the coffee making. The micro-controller had a clock and allowed a person
to program a start time for the micro-controller to start heating water or a person could
just press a switch and do it manually.

In this lesson we will be using a relay to turn an LED on and off.

An interesting variation would be to introduce a push button switch tied to a GPIO pin of the
Raspberry Pi so that when the push button is pressed, the LED will be turned on and when pressed
again, the LED will be turned off.
