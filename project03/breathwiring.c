/*
 *   Test program for Raspberry Pi from URL
 *     http://osoyoo.com/2017/06/26/pi3-breathing-led/
 *
 *   This test program performs a test of a simple LED wiring
 *   that is connected to GPIO #17 to turn an LED on and off.
 *
 *   Compile with the following command line:
 *     cc breathwiring.c -lwiringPi
 *
 *   This command line compiles this test program and links it with the
 *   wiringPi.lib library for manipulating the GPIO pins of a Raspberry Pi.
*/

#include <wiringPi.h>
#include <stdio.h>


int main ()
{
        // LEDPIN is wiring Pi Pin #1 or GPIO #18
	// we choose this pin since it supports PWM as
	// PWM is not supported by any other GPIO pins.
        const int LEDPIN = 1;
	int iCount = 10;       // do the breathing this many times
	int iBrightness;       // brightness value from 0 to 100.

	if (wiringPiSetup() == -1) {
		printf ("Setup wiringPi Failed!\n");
		return -1;
	}

	pinMode (LEDPIN, PWM_OUTPUT);
	for (iCount *= 2, iBrightness = 0; iCount >= 0; ) {
		pwmWrite (LEDPIN, iBrightness);
		delay (200);
		if (iCount % 2) {
			// if iCount is even then we are going up on brightness
			iBrightness += 4;
			if (iBrightness > 100) {
				iBrightness = 100;
				iCount--;
			}
		} else {
			// if iCount is odd then we are going down on brightness
			iBrightness -= 4;
			if (iBrightness < 0) {
				iBrightness = 0;
				iCount--;
			}
		}
	}

	return 0;
}
