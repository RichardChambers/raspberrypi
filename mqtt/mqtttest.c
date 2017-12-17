/*
 * mqtttest [-ps msgqueue] [-h hostname]
 *     -p msgqueue    -> publish messages to message queue msgqueue
 *     -s msgqueue    -> subscribe to message queue msgqueue
 *     -h hostname    -> publish or subscribe to broker on hostname
 *
 * You can use the standard mosquitto utilities to assist with testing
 * of this application using the standard utilities in another terminal
 * window.
 *
 * The first test involves whether everything mosquitto is installed correctly
 *
 *     mosquitto_sub -t "topic/test"
 *
 *     mosquitto_pub -t "topic/test"
*/

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


#define MQTT_PORT 1883

int iswitch (char **arg)
{
	if (strcmp (*arg, "-p") == 0) {
		return 1;
	}
	else if (strcmp (*arg, "-s") == 0) {
		return 2;
	}
	else if (strcmp (*arg, "-h") == 0) {
		return 3;
	} else {
		return 0;
	}
}

void func(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *m)
{
    char *ud = (char *)userdata;

    printf("%s -> %s %s\n", ud, m->topic, m->payload);
}

	char  *pMsgTopic = "topic/test";

void my_connect_callback(struct mosquitto *mosq, void *obj, int result)
{
	int i;
	struct mosq_config *cfg;

	if (result == 0) {
		mosquitto_subscribe(mosq, NULL, pMsgTopic, 0);
	}
}


int main (int argc, char *argv[])
{
	struct mosquitto *mosq = NULL;
	struct mosquitto_message *msg;

        char  *pMsgQueue = NULL;
        char  *pHostName = "localhost";
        char  *pPassWord = "";
        int   iService = 0;
	int   iRet = 0;

	fjson_object *newObj = NULL;

	char  MsgBuffer[512] = {0};

	mosquitto_lib_init();
	mosq = mosquitto_new (NULL, true, NULL);
	if (! mosq) {
		printf (" Error: Unable to initialize Mosquitto library.\n");
		return 1;
	}

	if (argc > 1) {
		char **argline = argv + 1;

		switch (iswitch(argline)) {
			case 1:     // -p
				iService = 1;
				argline++;
				if (argc > 2) {
					pMsgQueue = *argline;
					argline++;
				} else {
					printf ("bad arguments -p\n");
					return 3;
				}
				break;
			case 2:    // -s
				iService = 2;
				argline++;
				if (argc > 2) {
					pMsgQueue = *argline;
					argline++;
				} else {
					printf ("bad arguments -s\n");
					return 3;
				}
				break;
			case 3:    // -h
				iService = 3;
				argline++;
				if (argc > 2) {
					pHostName = *argline;
					argline++;
				} else {
					printf ("bad arguments -h\n");
					return 3;
				}
				break;
			default:
				break;
		}
	}

	if (iService == 1) {
		iRet = mosquitto_connect (mosq, pHostName, MQTT_PORT, 0);
		if (iRet) {
			printf ("Can't connect to Mosquitto server %s\n", pHostName);
			return 1;
		}

		sprintf (MsgBuffer, "Hello World");

		iRet = mosquitto_publish (mosq, NULL, pMsgTopic, strlen (MsgBuffer), MsgBuffer, 0, false);
		if (iRet) {
			printf ("Can't publish to Mosquitto server %s\n", pHostName);
			return 2;
		}
	} else if (iService == 2) {

		printf (" option = %d %s\n", iService, pMsgQueue);

		mosquitto_connect_callback_set(mosq, my_connect_callback);
		mosquitto_message_callback_set(mosq, func);
		iRet = mosquitto_connect_bind(mosq, pHostName, MQTT_PORT, 0, NULL);
		if (iRet) {
			printf ("Can't connect to Mosquitto server %s\n", pHostName);
		}

		mosquitto_loop_forever (mosq, -1, 1);

	}


	printf (" option = %d %s\n", iService, pMsgQueue);

	newObj = fjson_tokener_parse ("{\"glossary\":{\"title\": \"a title\", \"count\":3 }}");

	printf (" new_obj.to_string()=%s\n", fjson_object_to_json_string(newObj));

	fjson_object_put(newObj);

	// cleanup before exit
	sleep (1);
	mosquitto_disconnect (mosq);
	sleep (1);
	mosquitto_destroy (mosq);
	sleep (1);
	mosquitto_lib_cleanup();

	return 0;
}
