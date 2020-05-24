
# OctaSource

8 output low frequency oscillator, with various modes to created related low frequency control voltages for synthesizers.

Uses [PJRC Teensy 4.0](https://www.pjrc.com/teensy-4-0/) and [MikroElektronika PIXI Click](https://www.mikroe.com/pixi-click) for IO.

### Features
* Requires a +12V/0V/-12V bipolar power supply.
* Output voltage range is -5V to 5V by default. (The MAX11300 IC used can also output a range of 0 to 10V, this is changeable in code)
* Rate control - Can can go backwards as well as forwards.
* Wave control - Changes the waveshape of the output between ramp, triangle, since and square.
* Amplitude control - Change amplitude of all 8 outputs. (Labelled as length in the prototype photos)
* CV inputs to change these 3 parameters, also with voltage range -5V to 5V.
* A mode switch to switch between differnet modes (see list below).
* Trigger input which is used in some modes. Triggers when voltage exceeds 3V.
* Trigger output which is used in some modes.


### Prototype

<img src="images/octasource_prototype_032020_1.jpg" height="500" /> <img src="images/octasource_prototype_032020_2.jpg" height="500" />


---

## Modes

There are various modes which can be cycled through by pressing the mode switch.

### 1 Phased

Each output wave is the same frequency but phase shifted by 45 degrees.
* Trigger: Will reset the phases back to initial values.

### 2 Multiplied

Each output is multiplied by a whole number of the previous output.
* Trigger: Will reset the phases back to initial values.

Submodes:
1. Multiply by 2
2. Multiply by 3


### 3 Uncorrelated

A range of frequency outputs that are uncorrelated to each other. In this case multiplied by an irrational number, Pi.
* Trigger: This mode starts off each wave at a completely random phase. When a trigger is received the phases are re-randomised, so can be used to create almost completely random voltages.


---

## Synchronising Multiple Modules

2 Octasource modules can be synchronised with each other. The 2 modules serial ports must be connected together by attaching a wire from pin 8 (TX) on the first module to pin 7 (RX) on the second module, and vice versa. Once they are connected one of modules can be put into slave mode by holding down the mode switch for more than 3 seconds, then releasing it.

After doing this the frequency control on the master module will also affect the slave module.

Submodes:
1. Multiply by square root of 2
2. Multiply by golden ratio
3. Multiply By Euler's number
4. Multiply by pi

---

## Calibration

Hold down mode switch while powering on. The top LED will light up red.

Release the mode switch, and turn all potentiometers to the leftmost position.

Press the mode switch. The top LED will turn blue.

Turn all potentiometers to the rightmost position.

Press the mode switch.

The module is now calibrated.
