/*
 *   Test program for Raspberry Pi from URL
 *     http://osoyoo.com/2017/07/12/raspberry-pi-starter-kit-lesson-12-raspberry-pi-drive-sg90-servo/
 *
 *   This test program performs a test of a simple SG90 servo circuit
 *   that is connected to GPIO #18 to exercise the PWM by changing
 *   the position of the horn attached to the servo shaft.
 *
 *   WARNING: running this program must be done with sudo in order for
 *            the wiringPi library to allow access to the PWM functionality
 *            of GPIO #18.
 *
 *   Compile with the following command line:
 *     cc sg90servo.c -lwiringPi
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
	const int POSITIONSTART = 10;    // 1ms pulse width for -90 degrees
	const int POSITIONEND  = 20;     // 2ms pulse width for +90 degrees
	const int POSITIONSTEP = 2;      // 0.2ms steps

	int iPosition;      // servo shaft angular position value.

	if (wiringPiSetup() == -1) {
		printf ("Setup wiringPi Failed!\n");
		return -1;
	}

	printf ("Reminder: this program must be run with sudo. Delay 5 seconds.\n");
	delay (5000);

	pinMode (LEDPIN, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);

	pwmSetClock (1920);
	pwmSetRange (200);

	for (iPosition = POSITIONSTART; iPosition <= POSITIONEND; iPosition += POSITIONSTEP) {
		printf ("  move to iPosition %d\n", iPosition);
		pwmWrite (LEDPIN, iPosition);
		delay (4500);
	}

	// cleanup the environment. set each pin to low
	// and set the mode to INPUT. These steps make sure
	// the equipment is safe to manipulate and prevents
	// possible short and equipment damage from energized pin.
	pinMode(LEDPIN, INPUT);
	digitalWrite (LEDPIN, LOW);

	return 0;
}
