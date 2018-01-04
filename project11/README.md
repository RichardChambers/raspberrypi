## Raspberry Pi Start Kit - Lesson 13, 14, and 15 Incremental Changes

With this project we are going to start with the 1602 LCD display functionality of
Lesson 13. Then we will add Lesson 14 using the tilt switch along with Lesson 8
using the active buzzer. Then we will improve the product by adding the
material of Lesson 15.

[Raspberry Pi Starter Kit Lesson 8: Raspberry Pi Drive Active Buzzer](http://osoyoo.com/2017/06/28/raspberry-pi-3-buzzer/)

[Raspberry Pi Starter Kit Lesson 13: I2C 1602 LCD](http://osoyoo.com/2017/07/03/raspbery-pi3-drive-i2c-1602-lcd/)

[Raspberry Pi Starter Kit Lesson 14: SW520D Tilt Switch with Raspberry Pi](http://osoyoo.com/2017/06/19/raspberry-tilt-switch/)

[Raspberry Pi Starter Kit Lesson 15: Raspberry Pi, Potentiometer and LCD](http://osoyoo.com/2017/07/04/raspberry-pi-potentiometer/)

### Starting the project series - Lesson 13 with Lesson 9

The first step is to take the materials developed in project 10 with the 1602 LCD display as a
starting position and add to that solution the materials developed in project 05 with the
active buzzer.

The displayed text will contain a counter that is incremented. Each time the 1602 LCD display text
is changed the buzzer will emit a short tone. The tone will vary depending on the value of the counter
mod 5 so there will be a total of 5 different tones which are emitted in a series which is then
repeated.

### Next phase - Adding Lesson 14
Adding Lesson 14 involves adding the tilt sensor to the circuit. Using the tilt sense allows us an
additional mode of user interaction, tilting or rotating the board in one plane so that the tilt
switch indicates that the board has changed its position.

Text is displayed on the 1602 LCD Display to indicate the tilt sensor readings. In addition the buzzer
is sounded as tilts are detected.

### Final phase - Adding lesson 15

In the final phase a potentiomter is added to allow a voltage output detected by a pin to be varied.
As the potentiometer is manipulated the voltage detected is displayed on the 1602 LCD Display. The
buzzer is used to provide aural feedback by changing the tone emitted based on the voltage level
of the potentiometer.
