/*
 *   Test program for Raspberry Pi from URL
 *     http://osoyoo.com/2017/06/26/pi3-breathing-led/
 *
 *   This test program performs a test of a simple LED circuit
 *   that is connected to GPIO #18 to exercise the PWM by changing
 *   the brightness of an LED.
 *
 *   WARNING: running this program must be done with sudo in order for
 *            the wiringPi library to allow access to the PWM functionality
 *            of GPIO #18.
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
        // LEDPIN is wiringPi Pin #1 or GPIO #18
	// we choose this pin since it supports PWM as
	// PWM is not supported by any other GPIO pins.
        const int LEDPIN = 1;
	const int BRIGHTSTART = 0;
	const int BRIGHTEND  = 100;
	const int BRIGHTSTEP = 4;

	int iCount = 2;       // do the breathing this many times
	int iBrightness;      // brightness value.

	if (wiringPiSetup() == -1) {
		printf ("Setup wiringPi Failed!\n");
		return -1;
	}

	printf ("Reminder: this program must be run with sudo.\n");
	pinMode (LEDPIN, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	iCount *= 2;
	for (iBrightness = BRIGHTSTART; iCount >= 0; ) {
		pwmWrite (LEDPIN, iBrightness);
		delay (500);
		if (iCount % 2) {
			// if iCount is even then we are going up on brightness
			iBrightness += BRIGHTSTEP;
			if (iBrightness > BRIGHTEND) {
				iBrightness = BRIGHTEND;
				iCount--;
			}
		} else {
			// if iCount is odd then we are going down on brightness
			iBrightness -= BRIGHTSTEP;
			if (iBrightness < BRIGHTSTART) {
				iBrightness = BRIGHTSTART;
				iCount--;
			}
		}
		printf (" iCount %d  iBrightness %d\n", iCount, iBrightness);
	}

	return 0;
}
