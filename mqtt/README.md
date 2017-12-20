## Using MQTT with Raspberry Pi

MQTT is a message communication protocol that is designed to be lightweight and
to work well with small micro-controllers to send data back and forth. There are
two parts to MQTT, the broker which is a kind of message server, and the client,
which is the application that sends and receives messages.

MQTT uses a publish and subscribe model. The broker is a central point which clients
can contact in order to subscribe to a data source. Clients send messages to the broker
which then repeats the message to all other clients which have subscribed to that
message channel.

The mosquitto utilities package has two applications that can assist with testing after
the install of mosquitto as well as to test you own applications. The most basic test
is to use these utilities to check after the install of mosquitto. You can use each of
these utilities running in its own terminal window for testing.
 - mosquitto_sub -t "topic/test"
 - mosquitto_pub -t "topic/test"

### Protocol alternatives

MQTT is one of several types of publish/subscribe messaging protocols. Some messaging
protocols are heavier than MQTT offering more services. The following article provides
an overview of three of the most commonly used protocols: AMQP, MQTT, and STOMP. There is CoAP as well

Choosing your messaging protocoll: AMQP, MQTT, or STOMP
https://blogs.vmware.com/vfabric/2013/02/choosing-your-messaging-protocol-amqp-mqtt-or-stomp.html

STOMP materials are at https://stomp.github.io/

AMQP materials are at https://www.amqp.org/

CoAP materials are at http://coap.technology/

See as well the following:

 - All About Messaging Protocols: What Are the Differences? http://www.eejournal.com/article/20150420-protocols/
 - IoT Standards and Protocols https://www.postscapes.com/internet-of-things-protocols/
 - MQTT and CoAP, IoT Protocols https://www.eclipse.org/community/eclipse_newsletter/2014/february/article2.php
 - Practical MQTT with Paho https://www.infoq.com/articles/practical-mqtt-with-paho
 - MQTT community wiki in GitHub https://github.com/mqtt/mqtt.github.io/wiki
 - Adafruit Message Queue Telemetry Transport https://learn.adafruit.com/adafruit-io/mqtt-api
 - Simple Messaging with MQTT (Java) https://www.oracle.com/corporate/features/simple-messaging-with-mqtt.html
 - Reliable message delivery with Mosquitto (MQTT) https://www.electricmonk.nl/log/2017/02/20/reliable-message-delivery-with-mosquitto-mqtt/
 
 For explorations into the underlying MQTT protocol see the following:
  - IoT – MQTT Publish and Subscriber C Code https://blog.feabhas.com/2012/04/iot-mqtt-publish-and-subscriber-c-code/

### Available packages for MQTT

There are a number of different open source MQTT product offerings available. Mosquitto seems to be most
commonly used. Eclipse Paho is also frequently mentioned.

See the following documentation resources:
 - Mosquitto man pages from Eclipse Foundation https://www.eclipse.org/mosquitto/man/mosquitto-8.php
 - How to install and secure (Ubuntu) from DigitalOcean https://www.digitalocean.com/community/tutorials/how-to-install-and-secure-the-mosquitto-mqtt-messaging-broker-on-ubuntu-16-04
 - Writing an MQTT client C for ActiveMQ http://kevinboone.net/mosquitto-test.html
 
It appears that most recently Mosquitto is a standard Raspbian install and is available
by using apt-get as in:

 - sudo apt-get install mosquitto mosquitto-clients

To get the development packages for Mosquitto C development (header and library files) use:

 - sudo apt-get install libmosquitto-dev

To get the development packages for Mosquitto plug-in development use:

 - sudo apt-get install mosquitto-dev

Setting up a local MQTT broker on the Raspberry Pi https://arduinodiy.wordpress.com/2017/02/04/setting-up-a-local-mqtt-broker-on-the-raspberry-pi/

Raspberry Pi as a MQTT server https://lowvoltage.github.io/2017/07/13/Raspberry-Pi-MQTT-Server

### JSON text messages

As MQTT sends and receives text, using JSON with MQTT seems a natural fit.

The FastJSON development library can be installed using apt-get. See https://github.com/rsyslog/libfastjson

 - sudo apt-get install libfastjson-dev

There is also GLIB JSON https://wiki.gnome.org/Projects/JsonGlib

### Adding SQLite3 for a database engine

The SQLite3 database engine, embedded engine, provides a nice SQL database engine which supports a good subset of SQL.

To install the development libraries and headers for C development:
 - sudo apt-get install libsqlite3-dev
