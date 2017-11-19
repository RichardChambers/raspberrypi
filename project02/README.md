This project is for Osoyoo Raspberry Pi Starter Kit Lesson #5.

Raspberry Pi Starter Kit Lesson 5: Flowing LED at URL:
  http://osoyoo.com/2017/06/25/raspberry-pi-flowing-led/ 

The goal of this lesson is to have several LEDs on the breadboard and to then control the LEDs turning on an off to
create a lightshow.

There are two approaches to this project.

The first approach, laid out in the Osoyoo lesson, is to have the LEDs receive
their power from the 3.3v supply and to then change the lit/unlit by toggling
a GPIO pin LOW to light the LED and HIGH to turn it off.

The second approach is to have the LEDs receive their power from the GPIO pin
itself, which is 3.3v, and to then change the lit/unlit by toggling the
GPIO pin HIGH to light the LED and LOW to turn it off.

The first approach uses all LEDs receiving their power from the 3.3v source
along a power rail of the breadboard with the ground being the GPIO pin.

The second approach uses each LED receiving its power from the GPIO 3.3v
and all LEDs using the ground rail of the breadboard.

There is one thing to be aware of with the second approach. Each side of
the GPIO board has its own ground. This means that if you are using GPIO
pins from different sides of the T connector then you will need to have
the ground rail on each side of the breadboard connected to a GND pin
on that side of the T connector.

If the individual LED circuit does not have a wire to a GND pin on the side
of the LED's GPIO pin then the LED will not light because the circuit is
broken.
