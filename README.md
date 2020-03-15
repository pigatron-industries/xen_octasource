
# OctaSource

8 output low frequency oscillator.

Uses [PJRC Teensy 4.0](https://www.pjrc.com/teensy-4-0/) and [MikroElektronika PIXI Click](https://www.mikroe.com/pixi-click) for IO.

## Modes

There are various modes which can be cycled through by pressing the mode switch.

### 1 Phased

Each output wave is the same frequency but phase shifted by 45 degrees.

### 2 Multiplied

(NOT YET IMPLEMENTED)
Each output is double the frequency of the previous output.

### 3 Uncorrelated

(NOT YET IMPLEMENTED)
A range of frequency outputs that are uncorrelated to each other.

## Synchronising Multiple Modules

(NOT YET IMPLEMENTED)
The number of outputs can be extended by attaching another Octasource module. The 2 modules can be synchronised with each other.

## Calibration

Hold down mode switch while powering on. The top LED with light up red.

Release the mode switch, and turn all potentiometers to the leftmost position.

Press the mode switch. The top LED will turn blue.

Turn all potentiometers to the rightmost position.

Press the mode switch.

The module is now calibrated.
