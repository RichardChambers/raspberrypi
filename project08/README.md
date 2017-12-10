## Raspberry Pi Starter Kit Lesson 11: Raspberry Pi Control the LED Brightness

http://osoyoo.com/2017/06/30/pi3-photoresistor-led/

This lesson is an application and circuit in which an LED's level of illumination is
detected using a light sensor, a photo-resistor, attached to a channel of a MCP3008 ADC.

Much of the circuitry of project07, the first project with the MCP3008 ADC, can be reused
in this project, project08. The difference is that instead of having a unvarying 3.3v
rail line voltage into CH0 of the ADC you instead have a line voltage whose level is
influenced by the amount of light a photo-resister is exposed to.

A photo-resister is a variable resister whose resistance value varies depending on the
level of light it is exposed to. The amount of resistance is inversely proportional to
the level of light. When the light is brighter, the photo-resistor has less resistance,
when the light is darker and less bright the resistance increases.

See https://en.wikipedia.org/wiki/Photoresistor

The light detecting part of this circuit is made up of a sub-circuit with two resistors
connecting the 3.3v rail with GND with a connection between the two resistors and CH0
of the MCP3008 ADC. One resistor is the photo-resistor connected to GND. The other is a
10K ohm pullup resistor connected to the 3.3v rail.

See this discussion of a pullup resistor https://learn.sparkfun.com/tutorials/pull-up-resistors

What this sub-circuit does is that when the photo-resistor is in a dark, low light environment
then it's resistance is high so the ADC see a high voltage on the input to CH0. As the light
increases and the photo-resistor's resistance decreases the ADC will see decreasing voltage
levels as an input on CH0.

