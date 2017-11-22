/*
 *   Test program for Raspberry Pi from URL
 *     http://osoyoo.com/2017/06/27/raspberry-pi-starter-kit-lesson-7
 *
 *   This test program performs a test of a simple LED circuit
 *   that is changed from lit to unlit by the Raspberry Pi when it
 *   sees a button press indication.
 *   The LED is connected to GPIO #18 and 3.3v power through 200 ohm resistor.
 *   The button is connected to GPIO #17 to GND.
 *
 *   Compile with the following command line:
 *     cc buttonpress.c -lwiringPi
 *
 *   This command line compiles this test program and links it with the
 *   wiringPi.lib library for manipulating the GPIO pins of a Raspberry Pi.
*/

#include <wiringPi.h>
#include <stdio.h>


int main ()
{
	const int BUTTONPIN=0;  // button connected to GPIO #17
        const int LEDPIN = 1;   // LED connected to GPIO #18
	const int DEBOUNCE_DELAY = 400;  // delay for button debounce in MS

	if (wiringPiSetup() == -1) {
		printf ("Setup wiringPi Failed!\n");
		return -1;
	}

	pinMode (LEDPIN, OUTPUT);     // LED is output because we will light it
	pinMode (BUTTONPIN, INPUT);   // button is input as we wait for press

	pullUpDnControl (BUTTONPIN, PUD_UP); // pull up for stable voltage level

	do {
		if (digitalRead(BUTTONPIN) == 0) {
			// button pressed, GPIO connected to GND, so zero.
			// so turn LED on
			digitalWrite (LEDPIN, LOW);
			delay (DEBOUNCE_DELAY);
		} else {
			// button released, so 3.3v through pullup resistor
			// so turn LED off
			digitalWrite (LEDPIN, HIGH);
			delay (DEBOUNCE_DELAY);
		}
	} while (1);  // forever

	return 0;
}
