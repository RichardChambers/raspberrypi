/*
 *   This test program performs a test of a simple LED circuit
 *   that is connected to GPIO #18 to exercise the PWM by changing
 *   the brightness of an LED.
 *
 *   WARNING: running this program must be done with sudo in order for
 *            the wiringPi library to allow access to the PWM functionality
 *            of GPIO #18.
 *
 *   Compile with the following command line:
 *     cc pwmtest.c -lwiringPi
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

	if (wiringPiSetup() == -1) {
		printf ("Setup wiringPi Failed!\n");
		return -1;
	}

	printf ("Reminder: this program must be run with sudo. Delay 5 seconds.\n");
	delay (5000);
	printf ("   starting now.\n");
	pinMode (LEDPIN, PWM_OUTPUT);
	// set the PWM mode to Mark Space
	pwmSetMode(PWM_MODE_MS);
	// set the clock divisor to reduce the 19.2 Mhz clock
	// to something slower, 5 Khz.
	// Range of pwmSetClock() is 2 to 4095.
	pwmSetClock (3840);  // 19.2 Mhz divided by 3840 is 5 Khz.

	// set the PWM range which is the value for the range counter
	// which is decremented at the modified clock frequency.
	// in this case we are decrementing the range counter 5,000
	// times per second since the clock at 19.2 Mhz is being 
	// divided by 3840 to give us 5 Khz.
	pwmSetRange (2500);  // range is 2500 counts to give us half second.

	delay (1);   // delay a moment to let hardware settings settle.

	{
		int i;
		int list[] = {50, 500, 1024, 2500, -1};

		for (i = 0; list[i] > 0; i++) {
			// range for the value written is 0 to 1024.
			pwmWrite (LEDPIN, list[i]);  // set the Duty Cycle for this range.
			// delay 10 seconds to watch the LED flash due to the PWM hardware.
			printf (" PWM Duty Cycle %d\n", list[i]);
			delay (10000);
		} 
	}

	// cleanup the environment. set each pin to low
	// and set the mode to INPUT. These steps make sure
	// the equipment is safe to manipulate and prevents
	// possible short and equipment damage from energized pin.
	pinMode(LEDPIN, INPUT);
	digitalWrite (LEDPIN, LOW);

	return 0;
}
