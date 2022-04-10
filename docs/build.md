---
order: 3
---
# Build Guide

## Base Board

1. Solder surface mount components onto base board. The components highlighted in red above do NOT need to be soldered.

    {% include img.html src="images/octasource_mkii_baseboard_brd.drawio.png" height=1100 %}

2. Solder the power header (male header pins).

3. Solder the teensy header (female header). The 4 inner pins only need to be soldered if using a Teensy 4.0, solder the full 24 pin header on the outer rows, this will allow easy expansion to Teensy 4.1 if required later.

4. Solder the through hole voltage regulator.

5. Solder the male header pins on the opposite side of the board. Headers marked in red above do not need to be soldered.

## Control Board

1. Solder surface mount components on the back of the control board. Do NOT solder the components highlighted in red below.

    {% include img.html src="images/octasource_mkii_controls_brd_bottom.drawio.png" height=1100 %}

2. Solder the female header rows. Headers marked in red above do not need to be soldered.

3. Place the potentiometers, rotary encoder, jacks and switch onto the board but do not solder them yet. Also place the RGB LEDs, the longest pin goes on the outside.

4. Place the front panel over the controls so they all fit through the holes, and secure them to the panel.

5. Solder the controls onto the pcb.

6. This part is a bit fiddly. Remove the front panel again, and use a piece of sticky tape to secure the OLED display flush to the panel. Try to get it as straight as possible. Carefully place the front panel back onto the controls baord so that the OLED pins go through the 4 holes at the top of the PCB. Now solder the OLED pins to the board being careful not to move the OLED.

## Teensy

1. With a knife, cut the trace for powering via USB. Check there is no continuity with a meter.

2. Solder the male headers pin onto the teensy.

3. If using a Teensy 4.0 solder the surface mount headers to the underside of the Teensy. Recommend using low temperature solder paste for these. Apply the solder paste to the header pins and secure them in place using some female header. Be very carefult not to touch any of the other components with the soldering iron.