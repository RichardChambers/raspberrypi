
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#include "lcd1602.h"
#include "pinreadwrite.h"

int main (int argc, char *argv[])
{
        // BUZZPIN is wiringPi Pin #1 or physical pin #12 or GPIO #18
        int BUZZPIN = 0;
	int SW520DPIN = 2;

	if (wiringPiSetup() == -1) {
		printf ("Setup wiringPi Failed!\n");
		return -1;
	}

	lcd1602Open (0x27);

	pinSetupWrite (BUZZPIN, LOW);
	pinSetupRead (SW520DPIN);

	lcd1602Write (0, 0, "Welcome to tiltbuzz_1");
	delay (2000);

	lcd1602Clear ();

	int  iCount = 20;
	for ( ; iCount > 0; iCount--) {
		int  iDelay = ((iCount % 5) + 1) * 400;
		char buffLines[2][24];

		// LOW means Vertical, HIGH means tilted.
		int iTilt = pinRead (SW520DPIN);

		sprintf (buffLines[0], "tiltbuzz_2 %2.2d", iCount);
		sprintf (buffLines[1], "SW520D  %d", iTilt);
		lcd1602Write (0, 0, buffLines[0]);
		lcd1602Write (0, 1, buffLines[1]);

		// if Vertical then ok, no indicator. if tilt then indicate.
		pinWrite (BUZZPIN, ((iTilt) ? 0 : 1));
		delay (2000);
	}

	// clean up the GPIO resources we have been using.
	// make sure that things are back to a good state before exit.
	pinCleanup (BUZZPIN);
	pinCleanup (SW520DPIN);
	lcd1602Close();

	delay (500);
	return 0;
}
