# `Esp8266L12` library

## To drive the L12ActuonixLinearActuator with the ESP8266 board in Arduino frameworks.


## Tools and prerequisites

 - vsCode
 - platformIO plugin for vsCode
 - [esp8266-arduino sdk](https://arduino-esp8266.readthedocs.io/)
 - etc.

## Motivation

  When I try to use the Arduino esp8266 SDK for developing driving logic for L12 Actuonix Linear Actuator, 

  I wrote a library `ESP8266Actuonix` to basically control the actuator.

## Briefly intro to L12 Actuonix Linear Actuator

  The 12 in L12 means the size is 12mm for the shell of stroke. They also offer L16 for larger size.

  The powersupply for this actuator could be 5-6V version and 12V version.

  The actuator could have a wire which output a voltage. That is ratio with the length of stroke extened.

  * so, this ask the lib can read the stroke length via AnalogRead() *

  The actuator could receive control signal in 4-20mA, 1kHz PWM, RemoteControl signal (refer the datasheet of L12 actuator).

  * this ask the lib can send 1KHz PWM to control the stroke of L12 actuator*

  For more advanced control stratege, such as closed loop control, the user of this lib can contribute and submit.

## Refer the Servo lib in Arduino

  Declare the `Esp8266L12` class with functions below:

```  Servo.attach(pwm_pin_out);  # to be implemented. refer Servo lib.
  Esp8266L12 actuator;   //declare
```

The implementation is done with refering the Servo library in Arduino SDK.

## Usage

	add this folder into lib folder in your platformIO project path.
	like: 
	   ./lib/Esp8266L12
	
	refer the code in `examples` subfolder.

check the example code for details.

You may need a motor driving board for the Motor's High-currency.

Adding close-loop control and contribute this repo. will be welcomed. :)





