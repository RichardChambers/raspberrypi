Raspberry Pi Starter Kit Lesson 8: Raspberry Pi Starter Kit Lesson 8: Raspberry Pi Drive Active Buzzer
http://osoyoo.com/2017/06/28/raspberry-pi-3-buzzer/

This lesson uses the Raspberry Pi to drive an active buzzer to make a sound. The program changes the level of a pin from HIGH to LOW
and back in a timed loop to stop and start the buzzer.

An active buzzer is a buzzer component or package that has the buzzer sound making device, an oscillation circuit, in the component,
hence active. An active buzzer can generate only a single frequency because the tone frequency depends on the the
oscillation circuit frequency which, for an active buzzer is fixed. For an active buzzer all you need to do is to supply
current to the device to start it buzzing and stop current to the device to stop the buzzing.

A passive buzzer (piezo transducer) is a buzzer component that makes a noise when current is applied and the pitch or tone
the buzzer creates depends on the voltage of the circuit. A passive buzzer is able to generate different frequencies which
depend on the voltage applied to the device.

The circuit is simple. A patch wire is run from 3.3v to the buzzer's positive electrode, the anode. A second patch wire is run from
the buzzer's negative electrode, the cathode, to GPIO #18.
