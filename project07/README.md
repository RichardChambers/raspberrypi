## Raspberry Pi Starter Kit Lesson 10: Raspberry Pi SPI Ports
http://osoyoo.com/2017/06/29/raspberry-pi-mcp3008/

This is an introductory lesson on using the MCP3008 ADC (Analogue to Digital Converter) with the
Raspberry Pi to dected analogue signals, convert the signal into a digital number representing the
the relative voltage level, and sending the digital number to the Raspberry Pi using the SPI
(Serial Peripheral  Interface Bus) interface.

This introductory lesson is on how to hook up the MCP3008 to the Raspberry Pi. The inputs to
the ADC are GND, which should return a digital value of zero, and the 3.3v rail, which should
return the max value of 1023, and which is the same as the reference voltage that is also tied
to the 3.3v rail.

### Lesson variation

After completing the initial lesson with the two fixed voltage sources feeding into CH0 and CH1
of the ADC I then looked for a means of creating a variable voltage to feed into CH2. I thought
that it might be possible to simulate an analog output sensor by using one of the 10k ohm potentiamters
that come with the Osoyoo starter kit. I asked the question on Electrical Engineering StackExchange
and received an affirmative.

After trying it out I then made another change by adding an LED whose level of brightness was governed
by using PWM through GPIO #18, selecting a Duty Cycle which corresponded to the values reported by
the ADC. Since the MCP3008 provides a value from 0 to 1023 and the default range for GPIO #18 when
used as a PWM pin is 1024, the only application changes needed were to use GPIO #18 as PWM and to use
whatever value was read from CH2 as the Duty Cycle.

So the two lesson physical wiring changes were as follows.

Using a 10k potentiometer, connect one side pin to 3.3v and the other side pin to GND. Connect the
middle pin to CH2 of the MCP3008.

Next connect GPIO #18 to a 200 ohm resistor and then the resistor to the anode of the LED. Connect
the cathode of the LED to GND.

Then modify the C source code to initialize GPIO #18 as PWM and have a loop so that the potentiometer
setting as reported by the ACD is read and then used to set the Duty Cycle of GPIO #18 followed by a
delay to allow time for the illumination level to be visible before checking the voltage level from
the potentiometer and making a change in the LED brightness level again.

## Online resources

Interfacing an SPI ADC (MCP3008) chip to the Raspberry Pi using C++ (spidev

   http://hertaville.com/interfacing-an-spi-adc-mcp3008-chip-to-the-raspberry-pi-using-c.html
