// blink an LED with JavaScript.
//
// requires the following:
//   nodejs as a container to run in
//      should already be in the Raspbian image
//   npm to install the onoff library
//      sudo apt-get install npm
//   onoff to interface with the GPIO board
//      sudo npm install onoff

// a simple and brute force sleep function that
// Javascript does not have as a built-in.
function sleep(delay) {
  var start = new Date().getTime();
  while (new Date().getTime() < start + delay);
}

var Gpio = require('onoff').Gpio;
var LED = new Gpio(17, 'out');     // use BCM pin numbering, not wiringPi

// a loop to blink the LED 10 times.
for (i=0; i < 10; i++) {
  LED.writeSync(0);
  sleep (1000);
  LED.writeSync(1);
  sleep (1000);
}

LED.unexport();
