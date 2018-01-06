## Raspberry Pi Start Kit - Lesson 13, 14, and 15 Incremental Changes

With this project we are going to start with the 1602 LCD display functionality of
Lesson 13. Then we will add Lesson 14 using the tilt switch along with Lesson 8
using the active buzzer. Then we will improve the product by adding the
material of Lesson 15.

[Raspberry Pi Starter Kit Lesson 8: Raspberry Pi Drive Active Buzzer](http://osoyoo.com/2017/06/28/raspberry-pi-3-buzzer/)

[Raspberry Pi Starter Kit Lesson 13: I2C 1602 LCD](http://osoyoo.com/2017/07/03/raspbery-pi3-drive-i2c-1602-lcd/)

[Raspberry Pi Starter Kit Lesson 14: SW520D Tilt Switch with Raspberry Pi](http://osoyoo.com/2017/06/19/raspberry-tilt-switch/)

[Raspberry Pi Starter Kit Lesson 15: Raspberry Pi, Potentiometer and LCD](http://osoyoo.com/2017/07/04/raspberry-pi-potentiometer/)

### tiltbuzz_1 Starting the project series - Lesson 13 with Lesson 9

The first step is to take the materials developed in project 10 with the 1602 LCD display as a
starting position and add to that solution the materials developed in project 05 with the
active buzzer.

The displayed text will contain a counter that is incremented once every three seconds. Each time the
1602 LCD display text is updated the buzzer will emit a short tone. The length of the tone will vary
depending on the value of the counter mod 5 plus 1 times 400 milliseconds so there will be a total of
5 different tone lengths from 400 ms to 2000 ms (2 seconds) which are emitted in a series which is
repeated.

Sinice the buzzer is annoying and the novelty of using it rapidly waned, I replaced the buzzer with
an LED. The cats appreciated the change as well.

The source code in `tiltbuzz_1.c` expects that the buzzer or LED is attached to BCM Pin #17 and that the
I2C address for the 1602 LCD is 0x27. Use `sudo i2cdetect -y 1` after hooking up 1602 to the
breadboard to see if the I2C address needs to be changed.

### tiltbuzz_2 Next phase - Adding Lesson 14
Adding Lesson 14 involves adding the tilt sensor to the circuit. Using the tilt sensor allows us an
additional mode of user interaction, tilting or rotating the board in one plane so that the tilt
switch indicates that the board has changed its position.

The first line of the 1602 LCD display will show the counter text and the buzzer will emit tones
of varying lengths of time similar to the previous iteration of this project.

Text is displayed on the second line of the 1602 LCD Display to indicate the tilt sensor readings.
In addition we will add an LED which will become lit when the tilt sensor indicates a tilt condition
and then turn off when the tilt is corrected.

The source code in `tiltbuzz_2.c` expects that the buzzer or LED is attached to BCM Pin #17
(wiringPi Pin 0) and that the I2C address for the 1602 LCD is 0x27. Use `sudo i2cdetect -y 1`
after hooking up 1602 to the breadboard to see if the I2C address needs to be changed. In
addition the SW520D tilt switch micro-board is expected to have its data output line connect
to BCM Pin # 27 (wiringPi Pin 2).

#### SW520D Micro-board Tilt Sensor

The tilt sensor included in the kit uses the SW-520D tilt switch soldered to a micro-PCB that contains
the necessary components to provide a digital output to indicate tilt or not tilt.

There are three pins on the micro-board package, VCC (5 volts), GND, and D0 (a digital data line).
The input voltage is 5v so the 5v rail of the Raspberry Pi is used to power the tilt sensor package.
The D0 pin is connected to a digital pin on the Raspberry Pi that is set up for `INPUT`.

The `digitalRead()` function of the wiringPI library is used to determine if the tilt sensor package
is holding the Raspberry Pi pin LOW, indicates not tilted, or HIGH, indicates tilted. When the tilt
switch is vertical the state is Not Tilted so the output is digital LOW. As the tilt switch is
rotated so that the barrel of the tilt switch changes from vertical, 90 degrees or orthogonal to the
ground or horizon, to horizontal at some point the internal balls within the barrel will move
away from the contacts causing the state to change to Tilted so the output becomes digital HIGH.

The tilt sensor needs a fairly large change in position for the little balls in the interior of the
barrel to go from Tilted to a state of Not Tilted.

### Final phase - Adding lesson 15

In the final phase a potentiomter is added to allow a voltage output detected by a pin to be varied.
As the potentiometer is manipulated the voltage level detected is displayed on the 1602 LCD Display.

In addition the tilt switch is used to detect tilting with the LED giving a visual indication of a
tilt.

The first line of the 1602 LCD display is used to display the potentiometer setting along with the
counter text. The buzzer will be emitting the various tone lengths as governed by the counter value.

The second line of the 1602 LCD display is used to display the tilting information along with the
LED visual indicator.

## Breadboard layout for the project

There are a number of parts in this project so efficient space utilization will be important.
The MCP3008 ADC is needed to interface the analog signal components to the Raspberry Pi digital pins.
The analog parts are the potentiometer.

The buzzer is an active buzzer with a built in oscillator and it requires a digital pin to be
either HIGH to turn on the buzzer or LOW to turn off the buzzer.

