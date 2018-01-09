
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#include "lcd1602.h"
#include "spilib.h"
#include "pinreadwrite.h"

int main (int argc, char *argv[])
{
        // BUZZPIN is wiringPi Pin #1 or physical pin #12 or GPIO #18
        int BUZZPIN = 1;
	int LEDPIN = 3;
	int SW520DPIN = 3;

	if (wiringPiSetup() == -1) {
		printf ("Setup wiringPi Failed!\n");
		return -1;
	}

	lcd1602Open (0x27);
	spiOpen (0, SPI_CHAN_CONFIG_SINGLE);

	pinSetupWrite (BUZZPIN, LOW);
	pinSetupWrite (LEDPIN, LOW);
	pinSetupRead (SW520DPIN);

	lcd1602Write (0, 0, "Welcome to tiltbuzz_2");
	delay (2000);
	lcd1602Clear();

	int  iCount = 20;
	for ( ; iCount > 0; iCount--) {
		int  iDelay = ((iCount % 5) + 1) * 400;
		char buffLines[2][24];

		int iSpiVal = spiAnalogRead (0, SPI_CHAN_CONFIG_SINGLE, 2);

		sprintf (buffLines[0], "tiltbuzz_2 %2d", iCount);
		lcd1602Write (0, 0, buffLines[0]);
		sprintf (buffLines[1], "Pent val %4d", iSpiVal);
		lcd1602Write (0, 1, buffLines[1]);
		pinWriteHiLo (BUZZPIN, 1, iDelay, iDelay);
	}

	// clean up the GPIO resources we have been using.
	// make sure that things are back to a good state before exit.
	pinCleanup (BUZZPIN);
	lcd1602Close();
	spiClose();

	delay (500);
	return 0;
}
