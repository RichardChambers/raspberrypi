/*
 * mqtttest [-ps msgqueue] [-h hostname]
 *     -p msgqueue    -> publish messages to message queue msgqueue
 *     -s msgqueue    -> subscribe to message queue msgqueue
 *     -h hostname    -> publish or subscribe to broker on hostname
 *     -d             -> dump the SQLite database to standard output
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

// include the SQLite3 library for embedded database engine.
// we will be taking in the JSON messages and storing the
// data in an SQLite3 database.
#include <sqlite3.h>

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
	}
	else if (strcmp (*arg, "-d") == 0) {
		return 4;
	} else {
		return 0;
	}
}

sqlite3 *db = 0;

int helptext(void) {
	printf("mqtttest [-ps msgqueue] [-h hostname]\n");
	printf("    -p msgqueue    -> publish messages to message queue msgqueue\n");
	printf("    -s msgqueue    -> subscribe to message queue msgqueue\n");
	printf("    -h hostname    -> publish or subscribe to broker on hostname\n");
	printf("    -d             -> dump the SQLite database to standard output\n");
}

void func(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *m)
{
	static int xCount = 0;
	char *ud = (char *)userdata;
	fjson_object *newObj = NULL;
	fjson_object *o = NULL;
	fjson_object *l = NULL;
	char  *field = "count";
	char  *field2 = "level";
	int   iCount = -1;
	int   iLevel = -1;

	newObj = fjson_tokener_parse (m->payload);
	if (!fjson_object_object_get_ex(newObj, field2, &l)) {
		printf("Field %s does not exist\n", field2);
	} 
	if (!fjson_object_object_get_ex(newObj, field, &o)) {
		printf("Field %s does not exist\n", field);
	} else {

		printf (" new_obj.to_string()=%s  \"%s\" = %d -> %d\n", fjson_object_to_json_string(newObj),
			field, fjson_object_get_int(o), fjson_object_get_int(l));

	if (db) {
		char *pErrorMsg;
		int rc = 0;
		char InsertStmt [521] = {0};
		sprintf (InsertStmt, 
			"insert into temps (myDevice, myDate, myTemp) VALUES (\"%s\", \"%4.4d\", %d);",
			"DEV-01", fjson_object_get_int(o), fjson_object_get_int(l)); 
		rc = sqlite3_exec (db, InsertStmt, NULL, NULL, &pErrorMsg);
		if (rc) {
			printf ("error with insert %s\n", pErrorMsg);
		}
	}
	}

	fjson_object_put(newObj);

}

char  *pMsgTopic = "topic/test";

void my_connect_callback(struct mosquitto *mosq, void *obj, int result)
{
	int i;
	struct mosq_config *cfg;

	if (result == 0) {
		printf (" callback \n");
		mosquitto_subscribe(mosq, NULL, pMsgTopic, 0);
	}
}

int dumpcallback(void *NotUsed, int argc, char **argv, char **azColName) {
	NotUsed = 0;
    
	for (int i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
    
	printf("\n");

	return 0;
}

int dumpdatabase (void) {
	int rc;

	rc = sqlite3_open ("mytest.db", &db);
	if (rc) {
		printf ("Can't open database: %d\n", rc);
		db = 0;
	} else {
		char *pErrorMsg;
		char SelectStmt [521] = 
		"select myDevice, myDate, myTemp from temps;";
		int rc = sqlite3_exec (db, SelectStmt, dumpcallback, NULL, &pErrorMsg);
		if (rc) {
			printf ("error with create db %s\n", pErrorMsg);
		}
	}
	return 0;
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

	if (argc < 2) {
		helptext();
		return 3;
	}
	mosquitto_lib_init();
	mosq = mosquitto_new (NULL, true, NULL);
	if (! mosq) {
		printf (" Error: Unable to initialize Mosquitto library.\n");
		return 1;
	}

	if (argc > 1) {
		char **argline = argv + 1;

		switch (iswitch(argline)) {
			case 0:
				helptext();
				return 3;
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
			case 4:   // -d
				dumpdatabase ();
				return 0;
			default:
				break;
		}
	}

	if (iService == 1) {
		int iCount;

		iRet = mosquitto_connect (mosq, pHostName, MQTT_PORT, 5);
		if (iRet) {
			printf ("Can't connect to Mosquitto server %s\n", pHostName);
			return 1;
		}

		for (iCount = 0; iCount < 10; iCount++) {
			sprintf (MsgBuffer, "{\"item\" : \"mqtttest\", \"count\": %d  }", iCount);

			// specify a value of 5 for keepalive. must be other than 0.
			// with a value of 0 we are seeing reconnect attempts regularly.
			// unless there is enough traffic to prevent communication pings.
			iRet = mosquitto_publish (mosq, NULL, pMsgTopic, strlen (MsgBuffer), MsgBuffer, 0, false);
			if (iRet) {
				printf ("Can't publish to Mosquitto server %s\n", pHostName);
				return 2;
			}
			printf("publish: count %d\n", iCount);
			sleep (1);
		}
	} else if (iService == 2) {

		printf (" option = %d %s\n", iService, pMsgQueue);

		int rc = remove ("mytest.db");
		if (rc) {
			printf ("Error remove %d\n", rc);
		}

		rc = sqlite3_open ("mytest.db", &db);
		if (rc) {
			printf ("Can't open database: %d\n", rc);
			db = 0;
		} else {
			char *pErrorMsg;
			char CreateStmt [521] = 
			"create table temps (myDevice text key NOT NULL, myDate text key NOT NULL, myTemp INT);";
			int rc = sqlite3_exec (db, CreateStmt, NULL, NULL, &pErrorMsg);
			if (rc) {
				printf ("error with create db %s\n", pErrorMsg);
			}
		}

		mosquitto_connect_callback_set(mosq, my_connect_callback);
		mosquitto_message_callback_set(mosq, func);
		// specify a value of 5 for keepalive. must be other than 0.
		// with a value of 0 we are seeing reconnect attempts regularly.
		// unless there is enough traffic to prevent communication pings.
		iRet = mosquitto_connect(mosq, pHostName, MQTT_PORT, 5);
		if (iRet) {
			printf ("Can't connect to Mosquitto server %s\n", pHostName);
		}

		mosquitto_loop_forever (mosq, -1, 1);

	}


	// cleanup before exit
	sleep (1);
	mosquitto_disconnect (mosq);
	sleep (1);
	mosquitto_destroy (mosq);
	sleep (1);
	mosquitto_lib_cleanup();

	if (db) {
		sqlite3_close(db);
	}

	return 0;
}
