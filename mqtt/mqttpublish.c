/*
 * mqttpublish [-p topic] [-h hostname]
 *     -p topic       -> publish messages to topic queue topic
 *     -h hostname    -> publish broker on hostname
 *     -m topic       -> monitor ADC channel 0 and publish values read
 *
 * You can use the standard mosquitto utilities to assist with testing
 * of this application using the standard utilities in another terminal
 * window.
 *
 * The first test involves whether everything mosquitto is installed correctly
 *
 *     mosquitto_sub -t "topic/test"
 *
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// include the fastjson library for JSON strings
// we will use the mosquitto MQTT library for sending
// and receiving JSON strings as out messages.
#include <libfastjson/json.h>

// include the mosquitto library for MQTT messages.
// we will be doing a publish or subscribe to a message
// queue supported by a mosquitto MQTT broker.
#include <mosquitto.h>

// include the pthread library for multi-threading.
// we will use the multi-threading library in order
// to have a thread running which samples the device
// connected to the Raspberry Pi and report the data
// using the MQTT library as JSON text.
#include <pthread.h>


// include the wiringPi library for talking to the Raspberry Pi
// GPIO and the breadboard.
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define CHAN_CONFIG_SINGLE  8
#define CHAN_CONFIG_DIFF    0


#define MQTT_PORT 1883

char  *pMsgTopic = "topic/test";

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


// the main thread function which samples the analog input
// and reports the value using MQTT to the designated broker.
void *checkSendMsg (void *pObj)
{
	// LEDPIN is wiringPi Pin #1 or GPIO #18
	// we choose this pin since it supports PWM as
	// PWM is not supported by any other GPIO pins.
	const int LEDPIN = 1;
	int analogChannel = 1;  // default is to display all of the MCP3008 channels
	int spiChannel = 0;     // default is to use SPI channel 0 on the Raspberry Pi
	int channelConfig = CHAN_CONFIG_SINGLE;

	struct mosquitto *mosq = pObj;
	char  *pDevice = "DEV-101-23";
	int   iCount = 0;
	int   iRet = 0;
	char  MsgBuffer[512] = {0};

	printf ("starting thread.\n");

	int myFd = wiringPiSPISetup (spiChannel, 10000);
	if (myFd < 0) {
		fprintf (stderr, "Can't open the SPI bus: %s\n", strerror (errno)) ;
		exit (EXIT_FAILURE) ;
	}

	pinMode (LEDPIN, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
        pwmSetClock (400);
        pwmSetRange (1024);

	do {
		char DateString[24] = "Dec-12-2017 10:06:32";

		int iLevel = myAnalogRead(spiChannel, channelConfig, analogChannel - 1);
 	
		pwmWrite (LEDPIN, iLevel);

		sprintf (MsgBuffer, "{ \"device\" : \"%s\", \"datetime\": \"%s\", \"count\": %d, \"level\" : %d }", pDevice, DateString, iCount, iLevel);
		iRet = mosquitto_publish (mosq, NULL, pMsgTopic, strlen (MsgBuffer)+1, MsgBuffer, 0, false);
		if (iRet) {
			printf ("Can't publish to Mosquitto server\n");
			break;
		}
		iCount++;
		sleep(1);
	} while (1);

	close (myFd) ;

	// cleanup the environment. set each pin to low
	// and set the mode to INPUT. These steps make sure
	// the equipment is safe to manipulate and prevents
	// possible short and equipment damage from energized pin.
	pinMode(LEDPIN, INPUT);
	digitalWrite (LEDPIN, LOW);

	return pObj;
}

int main (int argc, char *argv[])
{
	// Mosquitto MQTT data
	struct mosquitto *mosq = NULL;

        char  *pMsgQueue = NULL;
        char  *pHostName = "localhost";
        char  *pPassWord = "";
	int   iRet = 0;

	// pthread library data
	pthread_t  levelsThread;


        printf (" sudo needed to run this. waiting 7 seconds for control-C.\n");
        delay (7000);


	mosquitto_lib_init();
	mosq = mosquitto_new ("1234", true, NULL);
	if (! mosq) {
		printf (" Error: Unable to initialize Mosquitto library.\n");
		return 1;
	}

        // specify a value of 5 for keepalive. must be other than 0.
        // with a value of 0 we are seeing reconnect attempts regularly.
        // unless there is enough traffic to prevent communication pings.
	iRet = mosquitto_connect (mosq, pHostName, MQTT_PORT, 5);
	if (iRet) {
		printf ("Can't connect to Mosquitto server %s\n", pHostName);
		return 1;
	}

	if (wiringPiSetup() == -1) {
		printf ("Setup wiringPi Failed!\n");
		return -1;
	}

	iRet = pthread_create (&levelsThread, NULL, checkSendMsg, mosq);

	sleep (10);

	// cleanup before exit
	sleep (1);
	mosquitto_disconnect (mosq);
	sleep (1);
	mosquitto_destroy (mosq);
	sleep (1);
	mosquitto_lib_cleanup();

	return 0;
}
