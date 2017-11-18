/*
 *   Test program for Raspberry Pi from URL
 *     http://osoyoo.com/2017/06/22/intall-wiringpi/
 *
 *   This test program performs a test of a simple LED wiring
 *   that is connected to GPIO #17 to turn an LED on and off.
 *
 *   Compile with the following command line:
 *     cc testwiringpi.c -lwiringPi
 *
 *   This command line compiles this test program and links it with the
 *   wiringPi.lib library for manipulating the GPIO pins of a Raspberry Pi.
*/

#include <wiringPi.h>
#include <stdio.h>


int main ()
{
        // LEDPIN is wiring Pi Pin #0 or physical pin #11 or GPIO #17
        const int LEDPIN = 0;
	int iCount = 10;

	if (wiringPiSetup() == -1) {
		printf ("Setup wiringPi Failed!\n");
		return -1;
	}

	pinMode (WPI_MODE_PINS, OUTPUT);
	
	digitalWrite (LEDPIN, LOW);  // make sure the LED is off
	while (iCount > 0) {
		digitalWrite (LEDPIN, HIGH);  // turn the LED on
		printf ("%d LED On ... ", iCount); fflush (stdout);
		delay (1000);
		digitalWrite (LEDPIN, LOW); // turn the LED off
		printf ("LED Off\n");
		delay (500);
		iCount--;
	}

	digitalWrite (LEDPIN, LOW);  // make sure the LED is off
	delay (500);
	return 0;
}
