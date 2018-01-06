
// functions to set a pin to INPUT or to OUTPUT and to set
// the output level, HIGH or LOW.

// set the specified pin as an OUTPUT pin for writing and initialize
// the pin to the specified level, HIGH or LOW, for its initial conditions.
void pinSetupWrite (int iPin, int iLevel);

void pinWrite (int iPin, int iLevel);

// for the number of times specified by the value of iCount, vary
// the signal level of the specified pin.
// These two functions have a loop where the output level of the pin
// is set then a delay then the output level of the pin is set followed
// by another delay.
// 
// Output level is: HIGH, delay, LOW, delay.
// pin is left at LOW when function returns.
void pinWriteHiLo (int iPin, int iCount, int iDelayHigh, int iDelayLow);

// Output level is: LOW, delay, HIGH, delay.
// pin is left at HIGH when function returns.
void pinWriteLoHi (int iPin, int iCount, int iDelayLow, int iDelayHigh);

void pinSetupRead (int iPin);
int pinRead (int iPin);

void pinCleanup (int iPin);
