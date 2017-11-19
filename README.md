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

http://www.mosaic-industries.com/embedded-systems/microcontroller-projects/raspberry-pi/gpio-pin-electrical-specifications

http://www.susa.net/wordpress/2012/06/raspberry-pi-relay-using-gpio/

https://grantwinney.com/using-pullup-and-pulldown-resistors-on-the-raspberry-pi/
