/********************************************************************************************
*Filename      : readmcp300x.c
*Description   : read ADC mcp3008 value with raspberry pi
*Author        : Alan
*Website       : www.osoyoo.com
*Update        : 2017/06/29
********************************************************************************************/

/*
 * Modification history
 * 12-09-17 : R.Chambers    : reformat code and collapse one time use functions into main()
 * 12-09-17 : R.Chambers    : improve comments, change the usage string.
 * 12-11-17 : R.Chambers    : modifications for project08 photoresistor.
*/

#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
 
#define CHAN_CONFIG_SINGLE  8
#define CHAN_CONFIG_DIFF    0
 
 
char *usage = "Usage: mcp3008 all|analogChannel[1-8] [-l] [-ce1] [-d]\n\
       -l   = load SPI driver,  default: do not load\n\
       -b   = GPIO #18 connected to an LED. sudo required.\n\
       -p   = GPIO #18 connected to an LED. sudo required.\n\
       -ce1  = spi analogChannel 1, default:  0\n\
       -d   = differential analogChannel input, default: single ended";
 
 
int myAnalogRead(int spiChannel,int channelConfig,int analogChannel)
{
    if(analogChannel < 0 || analogChannel > 7)
        return -1;

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

void print_info()
{
    printf("\n");
    printf("|*****************************************|\n");
    printf("|    Read MCP3008(3004) ADC value         |\n");
    printf("|    ------------------------------       |\n");
    printf("|       | ADC |           | Pi  |         |\n");
    printf("|       |-----|-----------|-----|         |\n");
    printf("|       | CS  | connect to| CE0 |         |\n");
    printf("|       | Din | connect to| MOSI|         |\n");
    printf("|       | Dout| connect to| MISO|         |\n");
    printf("|       | CLK | connect to| SCLK|         |\n");
    printf("|       | CH0 | connect to| 3.3V|         |\n");
    printf("|       | CH1 | connect to| GND |         |\n");
    printf("|                                   OSOYOO|\n");
    printf("|*****************************************|\n");
    printf("\n");

} 

int main (int argc, char *argv [])
{
    // LEDPIN is wiringPi Pin #1 or GPIO #18
    // we choose this pin since it supports PWM as
    // PWM is not supported by any other GPIO pins.
    const int LEDPIN = 1;
    int loadSpi = 0;        // default is to not load the SPI driver
    int analogChannel = 0;  // default is to display all of the MCP3008 channels
    int spiChannel = 0;     // default is to use SPI channel 0 on the Raspberry Pi
    int bBright = 0;        // default for brightness project is off.
    int bPhoto = 0;         // default for photoresitor project is off.
    int channelConfig = CHAN_CONFIG_SINGLE;

    print_info();

    if (argc < 2) {
        fprintf (stderr, "\n%s\n", usage) ;
        return 1 ;
    }


    if((strcasecmp (argv [1], "all") == 0) )
        argv[1] = "0";

    int iScan = sscanf (argv[1], "%i", &analogChannel);
    if ( iScan != 1 || analogChannel < 0 || analogChannel > 8 ) {
        // specified MCP3008 channel is out of range.
        printf ("%s\n",  usage) ;
        return 1 ;
    }

    // we are using this application to drive a number of different projects and
    // project variants.
    //   -b  change the brightness of an LED proportional to an ADC channel value
    //   -p  change the brightness of an LED inversely proportional to an ADC channel value
    //
    // The settings for -b are to hook a potentiometer to a channel on an ADC and use the
    // value read to be the illumination level to set an LED.
    //
    // The settings for -p are to hook a photoresistor circuit to a channel on an ADC and
    // use the value read to be the ambient light level and to reduce the LED illuminiation
    // if the room is well lit and to increase the LED illumination if the room is dark.
    int i;
    for (i = 2; i < argc; i++) {
        if (strcasecmp (argv [i], "-l") == 0 || strcasecmp (argv [i], "-load") == 0)
            loadSpi = 1;
        else if (strcasecmp (argv [i], "-ce1") == 0)
            spiChannel = 1;
        else if (strcasecmp (argv [i], "-d") == 0 || strcasecmp (argv [i], "-diff") == 0)
            channelConfig = CHAN_CONFIG_DIFF;
        else if (strcasecmp (argv [i], "-b") == 0 || strcasecmp (argv [i], "-bright") == 0)
            bBright = 1;
        else if (strcasecmp (argv [i], "-p") == 0 || strcasecmp (argv [i], "-photo") == 0)
            bPhoto = 1;
    }

    //

    if (loadSpi) {
        // in some environments the SPI driver must be loaded. if requested then
        // we use the gpio utility of the wiringPi library to load it.
        if (system("gpio load spi") == -1) {
            fprintf (stderr, "Can't load the SPI driver: %s\n", strerror (errno)) ;
            exit (EXIT_FAILURE) ;
        }
    }

    if (bBright || bPhoto) {
        printf (" sudo needed to run this. waiting 7 seconds for control-C.\n");
        delay (7000);
    }


    if (wiringPiSetup() == -1) {
        printf ("Setup wiringPi Failed!\n");
        return -1;
    }

    int myFd = wiringPiSPISetup (spiChannel, 10000);
    if (myFd < 0) {
        fprintf (stderr, "Can't open the SPI bus: %s\n", strerror (errno)) ;
        exit (EXIT_FAILURE) ;
    }


    //
    if (analogChannel > 0) {
        int  iLoop = 0;

        if (bBright || bPhoto) {
            // both the -b project and the -p project use PWM to control
            // the level of illumination of an LED.
            pinMode (LEDPIN, PWM_OUTPUT);
            pwmSetMode(PWM_MODE_MS);

            iLoop = 20;
        }

	do {
            // a specific channel on the MCP3008 was requested so read only that channel.
            printf("MCP3008(CE%d,%s): analogChannel %d = %d\n", spiChannel,
                   (channelConfig == CHAN_CONFIG_SINGLE)
                       ? "single-ended" : "differential", analogChannel,
                   myAnalogRead(spiChannel, channelConfig, analogChannel-1));
            if (iLoop) {
                if (bBright) {
                    // -b project so set the LED illumination proportional to the input voltage
                    // detected by the ADC as modified by a potentiometer.
                    int iBrightness = myAnalogRead(spiChannel, channelConfig, analogChannel - 1);
                    pwmWrite (LEDPIN, iBrightness);
                }
                if (bPhoto) {
                    // -p project so set the LED illumination inversely proportional to the input
                    // voltage detected by the ADC as modified by the photoresistor.
                    int iPhoto = myAnalogRead(spiChannel, channelConfig, analogChannel - 1);
                    pwmWrite (LEDPIN, 1023 - iPhoto);
                }
                delay (3000);
                iLoop--;
            }
	} while (iLoop > 0);
    } else {
        // iterate over all channels of the MCP3008. There are 8 channels available.
        for (i = 0; i < 8; i++) {
            printf("MCP3008(CE%d,%s): analogChannel %d = %d\n", spiChannel,
                 (channelConfig==CHAN_CONFIG_SINGLE)
                     ? "single-ended" : "differential", i+1,
                 myAnalogRead(spiChannel, channelConfig, i));
        }
    }

    close (myFd) ;

    // cleanup the environment. set each pin to low
    // and set the mode to INPUT. These steps make sure
    // the equipment is safe to manipulate and prevents
    // possible short and equipment damage from energized pin.
    pinMode(LEDPIN, INPUT);
    digitalWrite (LEDPIN, LOW);

    return 0;
}

