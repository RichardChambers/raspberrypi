
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
 
#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "spilib.h"

static int spiFD;

int spiAnalogRead(int spiChannel, int channelConfig, int analogChannel)
{
    if(analogChannel < 1 || analogChannel > 8)
        return -1;

    analogChannel--;

    // from URL:
    //   http://hertaville.com/interfacing-an-spi-adc-mcp3008-chip-to-the-raspberry-pi-using-c.html

    // Raspberry Pi asserts the chip select signal connected to the MCP3008
    // (CS0 in our case) by setting it to 0V. This is typically taken care
    // of internally by the spidev driver whenever the proper ioctl() function is called.

    // Raspberry Pi sends a byte containing a value of '1' to the MCP3008. This is a
    // start bit. At the same time the MCP3008 sends back a 'don't care' byte to the Raspberry Pi.

    // Raspberry Pi then sends a second byte whose most significant nibble
    // (SGL/DIFF,D2,D1 & D0 bits) indicate the channel that we want to convert and
    // whether we want single-ended or differential conversion (See Figure 5).
    // For example if this nibble is "1000", the conversion will be single-ended
    // and take place on channel 0 (CH0 pin). The least significant nibble is sent
    // as 'don't care'. At the same time, the MCP3008 sends back the two most
    // significant bits of the digital value (result) of the conversion (bits 8 and 9).

    // Raspberry Pi sends another  'don't care' byte to the MCP3008. At the same time
    // the MCP3008 send back a byte containing bits 7 through 0 0f the digital value
    // (result) of the conversion.

    // The Raspberry Pi then merges bits 8 & 9 from the second received byte with
    // bits 7  through 0 from the third received byte to create the 10-bit digital
    // value resulting from the conversion.

    unsigned char buffer[3] = {1}; // start bit
    buffer[1] = (channelConfig+analogChannel) << 4;

    wiringPiSPIDataRW(spiChannel, buffer, 3);

    return ( (buffer[1] & 3 ) << 8 ) + buffer[2]; // get last 10 bits
}

int spiClose (void)
{

    close (spiFD) ;
}

//    int spiChannel = 0;     // default is to use SPI channel 0 on the Raspberry Pi
//    int channelConfig = CHAN_CONFIG_SINGLE;
int spiOpen (int spiChannel, int channelConfig)
{

    spiFD = wiringPiSPISetup (spiChannel, 10000);
    if (spiFD < 0) {
        return -1;
    }

    return 0;
}

