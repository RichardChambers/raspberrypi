# raspberrypi
Experiments with my Raspberry Pi 3 Model B

These experiments are based on the lesson plans from the web site of
OsoYoo which sells the Raspberry Pi Starter Kit which is what is
being used for these projects.

See URL:
  http://osoyoo.com/2017/07/13/raspberry-pi-3-starter-learning-kit-introduction/ 

Each project is in a folder within this repository.

The project source code is in the C or C++ programming language and uses
the wiringPi library in order to interface with the Raspberry Pi GPIO board.

WARNING: Be careful about the pins connected and used in experiments. The Raspberry Pi GPIO board has both 3.3v and 5v power pins. You can overload the I/O pins, which are 3.3v, by connecting them accidently to the 5v pin and render your Raspberry Pi dead.

The library was already part of my Raspbian build and I did not need to
install it. You can check if it is already installed by using the following
command line:

    gpio -v

which should print out something like:

    pi@raspberrypi:~ $ gpio -v
    gpio version: 2.44
    Copyright (c) 2012-2017 Gordon Henderson
    This is free software with ABSOLUTELY NO WARRANTY.
    For details type: gpio -warranty
    
    Raspberry Pi Details:
      Type: Pi 3, Revision: 02, Memory: 1024MB, Maker: Embest 
      * Device tree is enabled.
      *--> Raspberry Pi 3 Model B Rev 1.2
      * This Raspberry Pi supports user-level GPIO access.
    pi@raspberrypi:~ $ 

The wiringPi GPIO Interface library for the Raspberry Pi is at URL:
  http://www.wiringpi.com

The web site has a blog with quite a bit of information about using
the library and the Raspberry Pi. The library has also been ported to
other boards and several different programming languages.

Documentation on the Raspberry Pi GPIO board seems to be a bit sparse however here are some resources.

First of all a YouTube 19 minute video: Raspberry Pi: Using GPIO Inputs https://www.youtube.com/watch?v=NAl-ULEattw

http://www.mosaic-industries.com/embedded-systems/microcontroller-projects/raspberry-pi/gpio-pin-electrical-specifications

http://www.susa.net/wordpress/2012/06/raspberry-pi-relay-using-gpio/

https://grantwinney.com/using-pullup-and-pulldown-resistors-on-the-raspberry-pi/


The gpio utility of the wiringPi library has a readall command that shows the
mapping of wiringPi pin designators and the official name of the pin.

    pi@raspberrypi:~ $ gpio readall
     +-----+-----+---------+------+---+---Pi 3---+---+------+---------+-----+-----+
     | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
     +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
     |     |     |    3.3v |      |   |  1 || 2  |   |      | 5v      |     |     |
     |   2 |   8 |   SDA.1 |   IN | 1 |  3 || 4  |   |      | 5v      |     |     |
     |   3 |   9 |   SCL.1 |   IN | 1 |  5 || 6  |   |      | 0v      |     |     |
     |   4 |   7 | GPIO. 7 |   IN | 1 |  7 || 8  | 0 | IN   | TxD     | 15  | 14  |
     |     |     |      0v |      |   |  9 || 10 | 1 | IN   | RxD     | 16  | 15  |
     |  17 |   0 | GPIO. 0 |   IN | 0 | 11 || 12 | 0 | IN   | GPIO. 1 | 1   | 18  |
     |  27 |   2 | GPIO. 2 |   IN | 0 | 13 || 14 |   |      | 0v      |     |     |
     |  22 |   3 | GPIO. 3 |   IN | 0 | 15 || 16 | 0 | IN   | GPIO. 4 | 4   | 23  |
     |     |     |    3.3v |      |   | 17 || 18 | 0 | IN   | GPIO. 5 | 5   | 24  |
     |  10 |  12 |    MOSI |   IN | 0 | 19 || 20 |   |      | 0v      |     |     |
     |   9 |  13 |    MISO |   IN | 0 | 21 || 22 | 0 | IN   | GPIO. 6 | 6   | 25  |
     |  11 |  14 |    SCLK |   IN | 0 | 23 || 24 | 1 | IN   | CE0     | 10  | 8   |
     |     |     |      0v |      |   | 25 || 26 | 1 | IN   | CE1     | 11  | 7   |
     |   0 |  30 |   SDA.0 |   IN | 1 | 27 || 28 | 1 | IN   | SCL.0   | 31  | 1   |
     |   5 |  21 | GPIO.21 |   IN | 1 | 29 || 30 |   |      | 0v      |     |     |
     |   6 |  22 | GPIO.22 |   IN | 1 | 31 || 32 | 0 | IN   | GPIO.26 | 26  | 12  |
     |  13 |  23 | GPIO.23 |   IN | 0 | 33 || 34 |   |      | 0v      |     |     |
     |  19 |  24 | GPIO.24 |   IN | 0 | 35 || 36 | 0 | IN   | GPIO.27 | 27  | 16  |
     |  26 |  25 | GPIO.25 |   IN | 0 | 37 || 38 | 0 | IN   | GPIO.28 | 28  | 20  |
     |     |     |      0v |      |   | 39 || 40 | 0 | IN   | GPIO.29 | 29  | 21  |
     +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
     | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
     +-----+-----+---------+------+---+---Pi 3---+---+------+---------+-----+-----+
    pi@raspberrypi:~ $ 
