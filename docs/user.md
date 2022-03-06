---
order: 2
---
# User Manual

## Modes

Change the mode by holding down the encoder switch and turning clockwise or anticlockwise.

### 1. Phase Difference

Each output wave is the same frequency but phase shifted by 45 degrees.

Inputs:
* **SYNC**: 
* **WAVE**: The waveform generated for all outputs. Sine, Triangle, Saw or Pulse.
* **RATE**: Bipolar frequency control. The wave will be 'stopped' at the top position and moving clockwise will increase frequency. Moving anti-clockwise will decrease the frequency into the negative, which will cause the phase shifted waves to rotate in the opposite direction.
* **PHASE**: The phase difference between waves. Full clockwise will give a 1/8 phase difference so all 8 outputs give a full 360 degrees with equal spacing.
* **AMP**: Amplitude of the wave on all outputs.

Outputs:
* **OUTPUTS 1-8**: The phase shifted wave forms.
* **TRIG**: Outputs a trigger for each cycle, the same frequency as the waves.

---

### 2. Frequency Relationships

The frequencies of each output are different but related to each other by a frequency division.

Inputs:
* **SYNC**: 
* **WAVE**: The waveform generated for all outputs. Sine, Triangle, Saw or Pulse.
* **RATE**: Base frequency of outputs.
* **PHASE**: 
* **AMP**: Amplitude of the wave on all outputs.

Outputs:
* **OUTPUTS 1-8**: Waveforms with frequency relationships dependent upon the selected submode.
* **TRIG**: Outputs a trigger for each cycle, the same frequency as the waves.

Submode frequency divisions:
1. Whole numbers: 1 / 2 / 3 / 4 / 5 / 6 / 7 / 8
2. Powers of 2: 1 / 2 / 4 / 8 / 16 / 32 / 64 / 128
3. Irrational numbers: 1 / zeta 3 / root 2 / phi / e / pi / feigenbaum constant / e^pi
4. Solar system planets: Mercury / Venus / Earth / Mars / Jupiter / Saturn / Uranus / Neptune

---

### 3. Filter

Low frequency oscilaltor with low pass filter.

Inputs:
* **SYNC**: 
* **WAVE**: The frequency of the low pass filter applies to the waveform.
* **RATE**: Frequency of the output waveform.
* **PHASE**: The resonance of the low pass filter.
* **AMP**: Amplitude of the wave on all outputs.

Outputs:
* **OUTPUT 1**: Filtered Sine wave.
* **OUTPUT 2**: Filtered Triangle wave.
* **OUTPUT 3**: Filtered Saw wave.
* **OUTPUT 4**: Filtered Pulse wave.
* **TRIG**: Outputs a trigger for each cycle, the same frequency as the waves.

---

### 4. Clock Divider

A clock source providing various subdivisions of an external or internal clock.

Inputs:
* **SYNC**: External clock, an external clock signal should be autodetected and used instead of internal clock.
* **WAVE**: Shuffle X Axis. Only applies to internal clock.
* **RATE**: Rate of internally generated clock.
* **PHASE**: Shuffle Y Axis. Only applies to internal clock.

Outputs:
* **OUTPUTS 1-8**: Divided clock signals.
* **TRIG**: The internal clock, or external clock if one is plugged in.

Submodes:
1. Integer Divisions: 1, 2, 3, 4, 5, 6, 7, 8
2. Even Divisions: 2, 4, 6, 8, 10, 12, 14, 16
3. Odd Divisions: 3, 5, 7, 9, 11, 13, 15, 17
4. Powers of 2: 2, 4, 8, 16, 32, 64, 128, 256
5. Prime Number Divisions: 2, 3, 5, 7, 11, 13, 17, 19
6. Fibonacci Sequence: 2, 3, 5, 8, 13, 21, 34, 55
7. Divisions based on 24 PPQN: 3, 6, 8, 12, 24, 32, 48, 96

The gate length of output gates will be based on the division of the previous output, allowing it to be used as accent CVs ans well as triggers.

---

### 5. Sequential Envelope

Rotating sequential envelope, where each trigger signal triggers the envelope on the next output, rotating through all outputs.

Inputs:
* **SYNC**: Trigger the envlelope.
* **WAVE**: Attack time of envelope.
* **RATE**: Decay time of envelope.
* **PHASE**: Length: Select the number of outputs to use for envelopes. Can use from 2 to 8 outputs.

Outputs:
* **OUTPUTS 1-8**: The envelope output. Depending on Length setting not all outputs may be used.
* **TRIG**: Trigger the next envelope in the cycle.

Submodes:
1. **Latched**: The envelope will remain in the sustain phase until the next trigger is recieved, then the envlope will decay will the next envelope starts its attack.
2. **Gated**: The envlope will remain in the sustain phase while there is a high voltage on the **SYNC** input. When this goes low the envelope will decay. The next envelope will not be triggered until the next gate signal is received.

---

### 6. Bouncing Ball

A ball dropped from a height, bounces off the 0V line, according the laws of gravity.

Inputs:
* **SYNC**: Trigger the bounce. Can be retriggered mid bounce to boost the ball back to initial height.
* **WAVE**: Damping. Determines the force that the ball bounces back up after each hit of the floor.
* **RATE**: Speed of the bouncing ball.
* **PHASE**: N/A
* **AMP**: Height of the bouncing ball.

Outputs:
* **OUTPUTS 1,3,5,7**: The bouncing ball outputs. Each output has different damping settings applied.
* **OUTPUTS 2,3,4,5**: A stepped voltage representing the bounce height of each bounce from the previous output.
* **TRIG**: Trigger the next envelope in the cycle.

Submodes:
* **Bounce**: Output continuous curve representing the current ball height + stepped bounce height on every other output.
* **Triggers**: Output a trigger for each time the ball hits the floor + stepped bounce height on every other output.
* **Rotate**: Rotates to the next output for each bounce, cycling through all 8 outputs until the ball stops.

---

### 7. Strange Attractor

Various 3 dimensional strange attractors with threee outputs, one for each axis.

Inputs:
* **SYNC**: 
* **WAVE**: 
* **RATE**: Speed of the strange attractor.
* **PHASE**: 
* **AMP**: Amplitude of the strange attractor.

Outputs:
* **OUTPUTS 1,2,3**: X, Y and Z co-ordinates of the strange attractor.
* **OUTPUTS 4,5,6**: X, Y and Z co-ordinates of the same strange attractor with slighly different starting position.
* **TRIG**: Gate, triggers on when Z axis goes above 0 and off below 0.

Submodes:
* Lorenz Attractor
* Lorenz 83 Attractor
* Thomas Attractor
* Aizawa Attractor
* Dadras Attractor
* Chen Attractor
* Rossler Attractor
* Halvorsen Attractor
* Chua Multi Scroll Attractor
* Rabinovich-Fabrikant Attractor
* Three Scroll Unified Attractor, 
* Four Wing Attractor

---

### 8. Double Pendulum

TODO

---

### 9. Three Body Simulation

TODO

---

### 10. Random

TODO

---

### 11. Delay

TODO

---

### 12. Voltage Reference

TODO

---

### 13. Audio Rate Oscillator

TODO
