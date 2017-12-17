# this make file uses two different libraries for the build.
#   libmosquitto is the mosquitto MQTT library
#      use sudo apt-get install libmosquitto-dev
#      use sudo apt-get install mosquitto mosquitto-clients

#   libfastjson is the Fast JSON library for JSON text handling
#      use sudo apt-get install libfastjson-dev

mqtttest: mqtttest.c
	cc -o mqtttest mqtttest.c -lmosquitto -lfastjson

