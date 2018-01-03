## Raspberry Pi Starter Kit Lesson 13: I2C 1602 LCD

This lesson is at URL: http://osoyoo.com/2017/07/03/raspbery-pi3-drive-i2c-1602-lcd/

The purpose of this lesson is to use the I2C communication facilities to display text on
a 1602 LCD (16 characters by 2 lines LCD display module). The 1602 LCD display requires
a parallel interface with 8 data bits provided for each character.

However the 1602 LCD module included in the Osoyoo kit has attached to it a PCF8574 IC
chip whose purpose is to accept a stream of bits on an I2C protocol wire and then convert
the serial stream of bits into a parallel set of bits for the 1602 LCD display.

The PCF8574 IC has four pins: (1) 5v power, (2) GND, (3) serial data pin SDA1, and (4)
serial data clock SCL1. The way it is used is a serial set of bits are clocked into the
IC and accumulated into a parallel byte and then pushed from the IC to the 1602 LCD display
through the parallel data pins connected between the PCF8574 and the 1602.

### Raspberry Pi configuration changes

The I2C subsystem of Raspbian on the Raspberry Pi must be turned on.
