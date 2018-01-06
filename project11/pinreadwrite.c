
#include <wiringPi.h>

#include "pinreadwrite.h"

void pinSetupWrite (int iPin, int iLevel)
{
    pinMode (iPin, OUTPUT);       // set the pin function
    digitalWrite (iPin, iLevel);  // make sure the buzzer is off
}

void pinWriteHiLo (int iPin, int iCount, int iDelayHigh, int iDelayLow)
{
    for ( ; iCount > 0; iCount--) {
        digitalWrite (iPin, HIGH);
        delay (iDelayHigh);
        digitalWrite (iPin, LOW);
        delay (iDelayLow);
    }
    digitalWrite (iPin, LOW);
}

void pinWriteLoHi (int iPin, int iCount, int iDelayLow, int iDelayHigh)
{
    for ( ; iCount > 0; iCount--) {
        digitalWrite (iPin, LOW);
        delay (iDelayHigh);
        digitalWrite (iPin, HIGH);
        delay (iDelayLow);
    }
    digitalWrite (iPin, HIGH);
}


int pinRead (int iPin)
{
    return digitalRead (iPin);
}

void pinSetupRead (int iPin)
{
    pinMode (iPin, INPUT);    // set the pin function
}

void pinCleanup (int iPin)
{
    pinMode (iPin, INPUT);     // set the pin function
    digitalWrite (iPin, LOW);  // make sure the buzzer is off
}
