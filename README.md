# raspberrypi
Experiments with my Raspberry Pi 3 Model B

These experiments are based on the lesson plans from the web site of
OsoYoo which sells the Raspberry Pi Starter Kit which is what is
being used for these projects.

See URL:
  http://osoyoo.com/2017/07/13/raspberry-pi-3-starter-learning-kit-introduction/ 

The RPi Hub on eLinux.org has a ton of information https://elinux.org/RPi_Hub

Each project stored within this repository is in a folder with a README.md file. There are also pages in the repository wiki.

The project source code is in the C or C++ programming language and uses the wiringPi library in order to interface with the Raspberry Pi GPIO board. The wiringPi library has been ported to other languages that support C calls. And there are other libraries that provide
similar functionality as the wiringPi library.

Thus far I have seen GPIO interfaces for python, JavaScript, and Lua in addition to C. All of these languages are available on the Raspberry Pi.

WARNING: Be careful about the pins connected and used in experiments. The Raspberry Pi GPIO board has both 3.3v and 5v power pins. You can overload the I/O pins, which are 3.3v, by connecting them accidently to the 5v pin and render your Raspberry Pi dead.

See the Wiki page about the Broadcom board and the GPIO interface.

## Various notes

Remove After Washing label on Piezo buzzer - https://electronics.stackexchange.com/questions/98556/remove-after-washing-on-piezo-buzzer

Tutorial on Serial Communications https://learn.sparkfun.com/tutorials/serial-communication

Tutorial on Serial Peripheral Interface (SPI) https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi

Tutorial on Inter-integrated Circuit (I2C) https://learn.sparkfun.com/tutorials/i2c

Tutorial on Pull-up Resistors https://learn.sparkfun.com/tutorials/pull-up-resistors

The answers to this question are quite educational about pull-up resistors. How do I calculate the required value for a pull-up resistor? https://electronics.stackexchange.com/questions/23645/how-do-i-calculate-the-required-value-for-a-pull-up-resistor

Also on pull-up resistors, I2C Bus Pullup Resistor Calculation http://www.ti.com/lit/an/slva689/slva689.pdf

## Additional technologies to investigate

### Communication protocols

This slide share package of some 60 slides does a compare and contrast between four different IoT protocols
looking at the needs of two different IoT groups, Consumers and Industrial, which have differing needs
for reliability and robustness. [What's the Right Messaging Standard for the IoT?](https://www.slideshare.net/Angelo.Corsaro/whats-the-right-messaging-standard-for-the-iot).

There are several message broker server alternatives with RabbitMQ being one of the most well known.

RabbitMQ https://www.rabbitmq.com/

VerneMQ https://vernemq.com/

Apache ActiveMQ http://activemq.apache.org/

#### Protocol alternatives

The following article provides an overview of three of the most commonly used
protocols: AMQP, MQTT, and STOMP. There is CoAP as well

Choosing your messaging protocoll: AMQP, MQTT, or STOMP
https://blogs.vmware.com/vfabric/2013/02/choosing-your-messaging-protocol-amqp-mqtt-or-stomp.html

STOMP materials are at https://stomp.github.io/

AMQP materials are at https://www.amqp.org/

CoAP materials are at http://coap.technology/

CBOR materials are at http://cbor.io/

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

#### MQTT

MQTT Protocol Overview -Beginners Guide http://www.steves-internet-guide.com/mqtt/

MQTT 101 – How to Get Started with the lightweight IoT Protocol https://www.hivemq.com/blog/how-to-get-started-with-mqtt

Getting started with MQTT https://dzone.com/refcardz/getting-started-with-mqtt

### CoAP

CoAP web site http://coap.technology/

CoAP Messaging in Depth http://programmingwithreason.com/article-iot-coap.html
