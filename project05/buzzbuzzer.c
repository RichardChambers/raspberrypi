/*
 *   Test program for Raspberry Pi from URL
 *     http://osoyoo.com/2017/06/28/raspberry-pi-3-buzzer/
 *
 *   This test program performs a test of a simple active buzzer circuit
 *   that is connected from GPIO #18 through the active buzzer's cathode
 *   or negative leg (the short leg) and from the buzzer's anode or
 *   positive leg (the long leg) to 3.3v.
 *
 *   This test program turns an active buzzer on and off multiple times
 *   with various delays in order to create different tones.
 *
 *   Compile with the following command line:
 *     cc buzzbuzzer.c -lwiringPi
 *
 *   This command line compiles this test program and links it with the
 *   wiringPi.lib library for manipulating the GPIO pins of a Raspberry Pi.
*/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>


// oscillate the pin between low and high to turn off and on the buzzer.
void buzz (int iPin, int iCount, int iDelay)
{
	printf ("   buzz: pin %d for %d time with delay of %d ms\n",
		iPin, iCount, iDelay);
	for ( ; iCount > 0; iCount--) {
		digitalWrite (iPin, LOW);
		delay (iDelay);
		digitalWrite (iPin, HIGH);
		delay (iDelay);
	}
	digitalWrite (iPin, LOW);
}

int main (int argc, char *argv[])
{
        // BUZZPIN is wiringPi Pin #1 or physical pin #12 or GPIO #18
        int BUZZPIN = 1;

	printf ("Starting to buzz like a bee.\n");

	if (wiringPiSetup() == -1) {
		printf ("Setup wiringPi Failed!\n");
		return -1;
	}

	pinMode (BUZZPIN, OUTPUT); // set the pin function
	
	digitalWrite (BUZZPIN, LOW);  // make sure the buzzer is off

	// now lets make the buzzer buzz with several variations of
	// delay between on and off as well as the number of times the
	// buzzer is cycled.
	buzz (BUZZPIN, 100, 3);
	delay (100);
	buzz (BUZZPIN, 100, 10);
	delay (100);
	buzz (BUZZPIN, 20, 100);
	delay (100);
	buzz (BUZZPIN, 20, 200);

	// clean up the GPIO resources we have been using.
	// make sure that things are back to a good state before exit.
	digitalWrite (BUZZPIN, LOW);  // make sure the buzzer is off
	pinMode (BUZZPIN, INPUT);     // set the pin function 
	delay (500);
	return 0;
}
