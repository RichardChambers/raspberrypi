# this make file uses two different libraries for the build.
#   libmosquitto is the mosquitto MQTT library
#      use sudo apt-get install libmosquitto-dev
#      use sudo apt-get install mosquitto mosquitto-clients

#   libfastjson is the Fast JSON library for JSON text handling
#      use sudo apt-get install libfastjson-dev

CFLAGS=-DWITH_POSIX

client: client.c
	cc $(CFLAGS) -o client client.c -lcoap-1 -lfastjson -lsqlite3

server: server.c
	cc $(CFLAGS) -o server server.c -lcoap-1 -lfastjson -lpthread -lwiringPi

