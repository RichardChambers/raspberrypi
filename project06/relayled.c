/*
 *   Test program for Raspberry Pi from URL
 *     http://osoyoo.com/2017/06/28/raspberry-pi-relay-led/
 *
 *   This test program performs a test of a simple relay circuit
 *   that is connected from GPIO #17 to the relay's signal pin.
 *
 *   A variation is to add a press button switch connected to GPIO #27
 *   and then use a busy loop to wait for the button to be pressed
 *   indicating that the user is requesting the LED to be turned off.
 *
 *   This test program turns an LED on and off by signaling a relay.
 *
 *   Compile with the following command line:
 *     cc relayled.c -lwiringPi
 *
 *   This command line compiles this test program and links it with the
 *   wiringPi.lib library for manipulating the GPIO pins of a Raspberry Pi.
*/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>



int main (int argc, char *argv[])
{
        // RELAYPIN is wiringPi Pin #0 or physical pin #11 or GPIO #17
        int RELAYPIN = 0;

	if (wiringPiSetup() == -1) {
		printf ("Setup wiringPi Failed!\n");
		return -1;
	}

	pinMode (RELAYPIN, OUTPUT); // set the pin function
	
	digitalWrite (RELAYPIN, LOW);  // make sure the relay is off
	delay (1500);
	digitalWrite (RELAYPIN, HIGH);  // make turn on the relay
	if (argc < 2) {
		int iDelay = 1500;
		printf ("   Delaying %d milliseconds\n", iDelay);
		delay ( iDelay);
	} else {
        	// SWITCHPIN is wiringPi Pin #2 or physical pin #13 or GPIO #27
		int SWITCHPIN = 2;
		int iSwitchOff = 1;   // has switch been pressed.

		pinMode (SWITCHPIN, INPUT); // set the pin function
		printf ("   Waiting for button press on pin %d\n", SWITCHPIN);
		do {
			iSwitchOff = (1 != digitalRead (SWITCHPIN));
			delay (50);
		} while (iSwitchOff);
	}

	// clean up the GPIO resources we have been using.
	// make sure that things are back to a good state before exit.
	digitalWrite (RELAYPIN, LOW);  // make sure the buzzer is off
	pinMode (RELAYPIN, INPUT);     // set the pin function 
	delay (500);
	return 0;
}
