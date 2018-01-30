
#include <stdio.h>
#include <wiringPi.h>

int main (void)
{
	const int BuzzerPin = 1;     // buzzer is attached Pin #1 or BCM #18
	const int PirSensorPin = 0;  // PIR sensor is attached Pin #0 or BCM #17
	int alarmState;              // current alarm state to reduce output lines.

	if (wiringPiSetup() == -1) {
		printf ("setup of wiringPi lib failed.\n");
		return 1;
	}

	pinMode (BuzzerPin, OUTPUT);
	pinMode (PirSensorPin, INPUT);

	alarmState = 0;
	printf (" --  No alarm\n");
	while (1) {
		if (digitalRead (PirSensorPin) == 0) {
			digitalWrite (BuzzerPin, HIGH);
			alarmState == 1 && printf (" --  No alarm\n");
			alarmState = 0;
		} else {
			digitalWrite (BuzzerPin, LOW);
			alarmState == 0 && printf ("***  Alarm!\n");
			alarmState = 1;
		}
		delay(1000);
	}

	return 0;
}
