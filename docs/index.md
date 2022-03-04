---
order: 1
---
# OctoSource

A Eurorack synthesiser module ith 8 control voltage outputs.

## Features
* Uses [PJRC Teensy 4.0](https://www.pjrc.com/teensy-4-0/) Microcontroller.
* Requires a +12V/0V/-12V bipolar power supply.
* Output voltage range is -5V to 5V by default. (The MAX11300 IC used can also output a range of 0 to 10V, this is changeable in code)
* Rate control - Can can go backwards as well as forwards.
* Wave control - Changes the waveshape of the output between ramp, triangle, since and square.
* Amplitude control - Change amplitude of all 8 outputs. (Labelled as length in the prototype photos)
* CV inputs to change these 3 parameters, also with voltage range -5V to 5V.
* A mode switch to switch between differnet modes (see list below).
* Trigger input which is used in some modes. Triggers when voltage exceeds 3V.
* Trigger output which is used in some modes.

## Documentation

* [User Manual](user.md)
* [Development History](development.md)
