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

## Notes about the 1602 LCD display of the kit

The bare bones 1602 LCD display has the 8 data pins which are used to send both text
data characters as well as hexadecimal commands to the 1602 LCD component. The hex
commands specify how the 1602 LCD is to display the text characters.

There are three control signal pins that are also used: R/W to signal read data
or write data, EN to latch data, and RS to select whether data being sent is a
command or a text character.

Since the 1602 LCD display module of the Osoyoo Raspberry Pi Starter Kit is a modified
module composed of a 1602 LCD display and a PCF8574 IC and we are using the I2C functionality
rather than the raw 1602 LCD pins, the software interface is a bit different than a
standard, unadorned 1602 LCD display module.

The difference is that the I2C interface must also allow us to set the control signal pins
as well as to send data/command bits. This is done by dividing the 8 bit serial character
sent vis I2C to the PCF8574 IC into two nibbles. The high nibble indicates the control pin
settings and the lower nibble indicates four bits of the 8 bit character being sent.

This means that to send an 8 bit text character or an 8 bit command character requires two
I2C writes, the first write to send the high order bits (bits 7 through 4) followed by a
second write to send the low order bits (bits 3 through 0).

See [16X2 LCD programming for beginners. Made easy](https://embeddedlifehelp.blogspot.com/2012/03/16x2-lcd-programming-for-beginners-made.html).

See [lcd commands and understanding of LCD module](http://www.firmcodes.com/microcontrollers/8051-3/interfacing-lcd-with-8051/lcd-commands-and-understanding-of-lcd/).

See [LCD - Liquid Crystal Display tutorial](http://www.microcontrollerboard.com/lcd.html) which describes 
in greater detail what seems to be the actual 1602 LCD display module in the Osoyoo kit.

See [Serial LCD quickstart](https://www.sparkfun.com/tutorials/246) which also seems to be similar to what is in the Osoyoo kit.
