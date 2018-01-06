
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#include "lcd1602.h"
#include "pinreadwrite.h"

int main (int argc, char *argv[])
{
        // BUZZPIN is wiringPi Pin #0 or physical pin #11 or GPIO #17
        int BUZZPIN = 0;
	int LCDAddrs = 0x27;   // may be 0x37 instead.

	if (wiringPiSetup() == -1) {
		printf ("Setup wiringPi Failed!\n");
		return -1;
	}

	lcd1602Open (LCDAddrs);

	pinSetupWrite (BUZZPIN, LOW);

	lcd1602Write (0, 0, "Welcome tilter");
	delay (2000);

	lcd1602Clear ();

	int  iCount = 20;
	for ( ; iCount > 0; iCount--) {
		int  iDelay = ((iCount % 5) + 1) * 400;

		lcd1602Writef (0, 0, "tiltbuzz_1 %2.2d", iCount);
		pinWriteHiLo (BUZZPIN, 1, iDelay, iDelay);
	}

	// clean up the GPIO resources we have been using.
	// make sure that things are back to a good state before exit.
	pinCleanup (BUZZPIN);
	lcd1602Close();

	delay (500);
	return 0;
}
