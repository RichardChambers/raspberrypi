/*
 *   Test program for Raspberry Pi from URL
 *     http://osoyoo.com/2017/06/22/intall-wiringpi/
 *
 *   This test program performs a test of a simple LED circuit
 *   that is connected from GPIO #17 through an LED and a 200 ohm
 *   resistor to ground. This test program turns an LED on and off.
 *
 *   Compile with the following command line:
 *     cc testwiringpi.c -lwiringPi
 *
 *   This command line compiles this test program and links it with the
 *   wiringPi.lib library for manipulating the GPIO pins of a Raspberry Pi.
*/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[])
{
        // LEDPIN is wiring Pi Pin #0 or physical pin #11 or GPIO #17
        int LEDPIN = 0;
	int iCount = 10;

	if (wiringPiSetup() == -1) {
		printf ("Setup wiringPi Failed!\n");
		return -1;
	}

	// allow a command line argument to change the target pin from
	// the default of GPIO17. The numbering system is the wiringPiSetup()
	// numbering and not the GPIO numbering.
	if (argc > 1) {
		LEDPIN = atoi (argv[1]);
		printf ("GPIO pin changed to %d\n", LEDPIN);
	}

	pinMode (LEDPIN, OUTPUT); // set the pin function
	
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

	// clean up the GPIO resources we have been using.
	// make sure that things are back to a good state before exit.
	digitalWrite (LEDPIN, LOW);  // make sure the LED is off
	pinMode (LEDPIN, INPUT);     // set the pin function 
	delay (500);
	return 0;
}
