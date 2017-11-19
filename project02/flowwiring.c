//
//  flowwiring.c - Lesson #5 for Osoyoo Raspberry Pi Starter Kit.
//    http://osoyoo.com/2017/06/25/raspberry-pi-flowing-led/

#include <stdio.h>

#include <wiringPi.h>

// Following two functions are used to turn an LED on or off.
// These functions assume that the LED is connected to a power
// source, the 3.3v pin, and the other end is connected to a
// GPIO pin on the Raspberry Pi GPIO board.
// To light the LED current must flow by driving the specified
// GPIO pin low. To unlight the LED current must stop flowing
// by driving the specified GPIO pin high.

void turn_on (int pin)
{
	digitalWrite (pin, HIGH);
}

void turn_off (int pin)
{
	digitalWrite (pin, LOW);
}


// A pin list is an array of pin numbers for the LEDs that are being
// used in this lesson. The pin numbers are positive values from 
// zero to the number of pins. A negative value, usually -1, is used
// to indicate the end of the list.
void setup_pins (int *pin_list)
{
	pinMode (WPI_MODE_PINS, OUTPUT);
	for (; *pin_list >= 0; pin_list++) {
		turn_off (*pin_list);
	}
}

int main ()
{
	int pin_list[] = {0, -1};

	if (wiringPiSetup() == -1) {
		printf ("Setup wiringPi failed! Check Setup.\n");
		return -1;
	}

	setup_pins (pin_list);

	turn_on (pin_list[0]);
	delay (2000);
	turn_off (pin_list[0]);
	delay(500);


	return 0;
}
