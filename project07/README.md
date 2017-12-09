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

## Online resources

Interfacing an SPI ADC (MCP3008) chip to the Raspberry Pi using C++ (spidev

   http://hertaville.com/interfacing-an-spi-adc-mcp3008-chip-to-the-raspberry-pi-using-c.html
