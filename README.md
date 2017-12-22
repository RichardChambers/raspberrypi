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

## Additional technologies to investigate

### Communication protocols

This slide share package of some 60 slides does a compare and contrast between four different IoT protocols
looking at the needs of two different IoT groups, Consumers and Industrial, which have differing needs
for reliability and robustness. [What's the Right Messaging Standard for the IoT?](https://www.slideshare.net/Angelo.Corsaro/whats-the-right-messaging-standard-for-the-iot).

#### MQTT

MQTT Protocol Overview -Beginners Guide http://www.steves-internet-guide.com/mqtt/

MQTT 101 – How to Get Started with the lightweight IoT Protocol https://www.hivemq.com/blog/how-to-get-started-with-mqtt

Getting started with MQTT https://dzone.com/refcardz/getting-started-with-mqtt

RabbitMQ https://www.rabbitmq.com/

VerneMQ https://vernemq.com/

### CoAP

CoAP web site http://coap.technology/

CoAP Messaging in Depth http://programmingwithreason.com/article-iot-coap.html
