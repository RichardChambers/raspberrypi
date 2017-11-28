//
//  flowwiring.c - Lesson #5 for Osoyoo Raspberry Pi Starter Kit.
//    http://osoyoo.com/2017/06/25/raspberry-pi-flowing-led/

#include <stdio.h>

#include <wiringPi.h>

// if using the Osoyoo Lesson #5 breadboard circuit then this
// needs to be defined.
#define LESSON

#include <stdio.h>

#include <wiringPi.h>

// Following two functions are used to turn an LED on or off.
// These functions assume that the LED is connected to a power
// source, the 3.3v pin, and the other end is connected to a
// GPIO pin on the Raspberry Pi GPIO board.
// To light the LED current must flow by driving the specified
// GPIO pin low. To unlight the LED current must stop flowing
// by driving the specified GPIO pin high.

#if defined(LESSON)
// if following the breadboard circuit as outlined in Osoyoo Lesson #5
// then we turn on the LED by driving the GPIO pin LOW which allows
// current to flow from the common 3.3v power rail of the breadboard.
void turn_on (int pin)
{
	digitalWrite (pin, LOW);
}

void turn_off (int pin)
{
	digitalWrite (pin, HIGH);
}
#else
// if using the second approach of using the GPIO pin as a power
// source then we need to drive the pin HIGH to provide power to
// turn on the LED and drive the pin LOW to turn the power off.
void turn_on (int pin)
{
	digitalWrite (pin, HIGH);
}

void turn_off (int pin)
{
	digitalWrite (pin, LOW);
}
#endif


// A pin list is an array of pin numbers for the LEDs that are being
// used in this lesson. The pin numbers are positive values from 
// zero to the number of pins. A negative value, usually -1, is used
// to indicate the end of the list.
void setup_pins (int *pin_list)
{
	for (; *pin_list >= 0; pin_list++) {
		pinMode (*pin_list, OUTPUT);
		turn_off (*pin_list);
	}
}

// Iterate over the list of pins using the corresponding delay for the
// amount of time the LED is to be lit.
void iterate_list (int *pin_list, int *delay_list)
{
	int savedDelay = 1000;

	for (; *pin_list >= 0; pin_list++) {
		if (delay_list && *delay_list > 0) {
			savedDelay = *delay_list;
			delay_list++;
		}
		turn_on (*pin_list);
		printf (" %d turn on ... ", *pin_list); fflush(stdout);
		delay (savedDelay);
		turn_off (*pin_list);
		printf ("  off \n");
	}
}

int main (int argc, char *argv[])
{
	int pin_list[] = {0, 1, -1};

	if (wiringPiSetup() == -1) {
		printf ("Setup wiringPi failed! Check Setup.\n");
		return -1;
	}

	setup_pins (pin_list);

	if (argc > 1) return 0;

	// iterate over the list a few times.
	{
		int i;

		for (i = 0; i < 10; i++) {
			iterate_list (pin_list, 0);
		}
	}

	// cleanup the environment. set each pin to low
	// and set the mode to INPUT. These steps make sure
	// the equipment is safe to manipulate and prevents
	// possible short and equipment damage from energized pin.
	{
		int i;
		for (i = 0; pin_list[i] >= 0; i++) {
			digitalWrite (pin_list[i], LOW);
			pinMode(pin_list[i], INPUT);
		}
	}

	return 0;
}
