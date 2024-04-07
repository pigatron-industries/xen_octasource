---
order: 2
---
# User Manual

{% include img.html src="images/octosource_panel.png" height="640" %}

* Apply an input CV applies an offset to the knob ranges. If knobs are at 12 o'clock then a -5V/+5V CV will be the same range as the knobs. Applying an offset will also allow the knob range to go higher or lower than normal.
* Changing the range switch for most modes will just switch the output voltage range from -5V/+5V to 0V/10V. Some modes, such as clock and envelope modes will remain at 0V when idle, regardless of range switch position, but will alter the maximum voltage when triggered.

Change the mode by holding down the encoder switch and turning clockwise or anticlockwise.

### 1. Phase Difference

Each output wave is the same frequency but phase shifted by 45 degrees.

Inputs:
* **SYNC**: Soft Sync - If a clock pulse is detected then synchronises the frequency of the output waveforms with the clock pulse.
* **MODE**: Hard Sync - A clock pulse on this input will hard reset the waves back to their original phases. 
* **WAVE**: Waveform - The waveform generated for all outputs. Sine, Triangle, Saw or Pulse.
* **RATE**: Bipolar frequency control. The wave will be 'stopped' at the top position and moving clockwise will increase frequency. Moving anti-clockwise will decrease the frequency into the negative, which will cause the phase shifted waves to rotate in the opposite direction. If a clock pulse is detected on the **SYNC** input then this acts as a frequency multiplier instead.
* **PHASE**: The phase difference between waves. Full clockwise will give a 1/8 phase difference so all 8 outputs give a full 360 degrees with equal spacing.
* **AMP**: Amplitude of the wave on all outputs.

Outputs:
* **OUTPUTS 1-8**: The phase shifted wave forms.
* **TRIG**: Outputs a trigger for each cycle of the waves.

Example of 8 phase shifted sine waves

![Phase shifted sine waves](images/phase_difference.drawio.png)

---

### 2. Frequency Relationships

The frequencies of each output are different but related to each other by a frequency division.

Inputs:
* **SYNC**: Soft Sync - If a clock pulse is detected then synchronises the frequency of the output waveforms with the clock pulse.
* **WAVE**: Waveform - The waveform generated for all outputs. Sine, Triangle, Saw or Pulse.
* **RATE**: Base frequency of outputs. If a clock pulse is detected on the **SYNC** input then this acts as a frequency multiplier/divider instead. Clockwise multiplies, anti-clockwise divides.
* **PHASE**: 
* **AMP**: Amplitude of the wave on all outputs.

Outputs:
* **OUTPUTS 1-8**: Waveforms with frequency relationships dependent upon the selected submode.
* **TRIG**: Outputs a trigger for each cycle of base frequency wave.

Submode frequency divisions:
1. Whole numbers: 1 / 2 / 3 / 4 / 5 / 6 / 7 / 8
2. Powers of 2: 1 / 2 / 4 / 8 / 16 / 32 / 64 / 128
2. Musical Intervals: 1:1 / 6:5  / 5:4 / 4:3 / 3:2 / 8:5 / 5:3 / 2:1
3. Irrational numbers: 1 / zeta 3 / root 2 / phi / e / pi / feigenbaum constant / e^pi
4. Solar system planets: Mercury / Venus / Earth / Mars / Jupiter / Saturn / Uranus / Neptune

---

### 3. Filter

Low frequency oscillator with low pass filter.

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

### 4. Clock Divider / Multiplier

A clock source providing various subdivisions and multiplications of an external or internal clock.
If using internal clock, a clock distortion can be added to create different types of shuffle effects.

Each output can be set individually using the left encoder. Push the encoder to change the output and rotate to set the division or multiplication.

Inputs:
* **SYNC**: External clock, an external clock signal should be autodetected and used instead of internal clock.
* **WAVE**: Clock Distortion X Axis. Only applies to internal clock.
* **RATE**: Rate of internally generated clock. If external clock is supplied then sets the multiplier or divider of that clock signal.
* **PHASE**: Clock Distortion Y Axis. Only applies to internal clock.
* **AMP**: The number of clock pulses the distortion is applied over.

Outputs:
* **OUTPUTS 1-8**: Divided clock signals.
* **TRIG**: The internal clock, or external clock if one is plugged in.

The gate length of output gates will be based on the division of the previous output, allowing it to be used as accent CVs as well as triggers.

Clock divider outputs example

![Clock Divider Outputs](images/clock_divider.drawio.png)

How altering clock distortion X and Y values can produce different types of shuffle:

![Clock Distortion](images/clock_divider_swing.drawio.png)

---


### 6. Sequential Envelope

Rotating sequential envelope, where each trigger signal triggers the envelope on the next output, rotating through all outputs.

Inputs:
* **SYNC**: Trigger the envlelope.
* **WAVE**: Attack time of envelope.
* **RATE**: Decay time of envelope.
* **PHASE**: Length: Select the number of outputs to use for envelopes. Can use from 2 to 8 outputs.
* **AMP**: Amplitude of envelope.

Outputs:
* **OUTPUTS 1-8**: The envelope output. Depending on Length setting not all outputs may be used.
* **TRIG**: Trigger the next envelope in the cycle.

Submodes:
1. **Latched**: The envelope will remain in the sustain phase until the next trigger is recieved, then the envlope will decay will the next envelope starts its attack.
2. **Gated**: The envlope will remain in the sustain phase while there is a high voltage on the **SYNC** input. When this goes low the envelope will decay. The next envelope will not be triggered until the next gate signal is received.

![Sequential Envelope](images/sequential_envelope.drawio.png)

---

### 7. Bouncing Ball

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
* **TRIG**:

Submodes:
* **Bounce**: Output continuous curve representing the current ball height + stepped bounce height on every other output.
* **Triggers**: Output a trigger for each time the ball hits the floor + stepped bounce height on every other output.
* **Rotate**: Rotates to the next output for each bounce, cycling through all 8 outputs until the ball stops.

![Bouncing Ball](images/bouncing_ball.drawio.png)

---

### 8. Strange Attractor

Various 3 dimensional strange attractors with three outputs, one for each axis.

Inputs:
* **SYNC**: 
* **WAVE**: 
* **RATE**: Speed of the strange attractor.
* **PHASE**: 
* **AMP**: Amplitude of the strange attractor.

Outputs:
* **OUTPUTS 2,3,4**: X, Y and Z co-ordinates of the strange attractor.
* **OUTPUTS 8,7,6**: X, Y and Z co-ordinates of the same strange attractor with slighly different starting position.
* **TRIG**: Gate, triggers on when Z axis goes above 0 and off below 0.

Submodes:
1. Lorenz Attractor
2. Lorenz 83 Attractor
3. Thomas Attractor
4. Aizawa Attractor
5. Dadras Attractor
6. Chen Attractor
7. Rossler Attractor
8. Halvorsen Attractor
9. Chua Multi Scroll Attractor
10. Rabinovich-Fabrikant Attractor
11. Three Scroll Unified Attractor
12. Four Wing Attractor

---

### 9. Double Pendulum

A 2 dimensional double pendulum simulation.

Inputs:
* **SYNC**: 
* **WAVE**: Mass of the second pendulum. Can be changed from 0.2 to 2 times the mass of the first pendulum. 12 o'clock position has bothe masses the same.
* **RATE**: Speed of the double pendulum simulation.
* **PHASE**: Ratio of pendulum lengths. Anti-clockwise, pendulum 1 length is 0 and pendulum 2 length is max. Clockwise, pendulum 1 length is max and pendulum 2 length is 0. 12 o'clock position length of both pendulums is the same.
* **AMP**: Amplitude of the double pendulum simulation.

Outputs:
* **OUTPUTS 1,2**: X, Y position of end of pendulum 1.
* **OUTPUTS 3,4**: X, Y position of end of pendulum 2.
* **TRIG**: 

---

### 10. Three Body Simulation

A 2 dimensional simulation of three planetary bodies in various orbits.

Inputs:
* **SYNC**: 
* **WAVE**: The size of the simulation space. Larger spaces effectively zoom out from the simulation allowing the planets more space to move around before hitting the edges.
* **RATE**: Speed of the double pendulum simulation.
* **PHASE**: Damping. If a planet hits the edge of space it bounces back with a lower speed determined by this input.
* **AMP**: Amplitude of the outputs.

Outputs:
* **OUTPUTS 2,8**: X, Y position of planet 1.
* **OUTPUTS 3,7**: X, Y position of planet 2.
* **OUTPUTS 4,6**: X, Y position of planet 3.
* **TRIG**: 

Submodes:
1. Basic orbit. Astable orbit of 2 smaller planets around a centre massive planet
2. Figure 8 stable. A stable figure 8 which slowly drifts rotationally.
3. Figure 8 Chaotic. A more chatoric Figure 8 orbit.
4. Broucke. Broucke orbit.
5. Broucke Asymetrical. An assymetrical Broucke orbit.
6. Chaotic Bounce. Completely chaotic orbit where the planets may bounce off the sides of the space with a speed dependent on the Damping setting.
7. Chaotic Antigrav. Completely chaotic orbit where the planets are repelled from the sides of space by an amount depending on the Damping setting.
8. Chaotic Wrap. Completely chaotic orbit where the planets can wrap around to the other side of space.
9. Chaotic 100/1/1. Chaotic orbit with one large mass and two smaller masses.
10. Chaotic 100/10/1. Chaotic orbit with three different masses.

---

### 11. Random

Stepped random voltage and trigger outputs.

Inputs:
* **SYNC**: 
* **WAVE**: Chance. The chance of outputting trigger 1 as opposed to trigger 2.
* **RATE**: Clock rate of steps and triggers.
* **PHASE**: 
* **AMP**: Amplitude of stepped voltage outputs.

Outputs:
* **OUTPUTS 1,3**: One of these outputs will trigger per clock cycle depedning on chance setting.
* **OUTPTUS 5,7**: One of these outputs will trigger per clock cycle depedning on chance setting.
* **OUTPUTS 2,4,6,8**: Random stepped voltage.
* **TRIG**: 

---

### 11. Delay

Delays or slews an input voltage by different amounts on each output.

Inputs:
* **SYNC**: The input voltage to delay.
* **WAVE**: 
* **RATE**: The delay time.
* **PHASE**: 
* **AMP**: 

Outputs:
* **OUTPUTS 1-8**: The delayed or slewed voltage. Each output delays by delay time multipled by output number.
* **TRIG**: 

Submodes:
1. Delay
2. Slew

---

### 12. Voltage Reference

Fixed voltage references.

Outputs:
* **OUTPUTS 1-8**: -5V, -2V, -1V, 0V, 0V, 1V, 2V, 5V
