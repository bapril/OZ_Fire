# OZ_FIRE

## Overview

This is a simple self-contained Arduino powered prop campfire for theatrical use.

## Acknowledgements
* Adafruit for the NeoPixel library.

## Construction

### Materials
* 2x2' piece of 3/4" Plywood as a base. (painted black)
* Foam to build the rocks.
* wood/sticks depending on the type/size fire you want.
* Arduino UNO Rev3
* Arduino proto-shield for easy wiring.
* 1 4" PC fan
* 4 2-3" Drywall screws to mount the fan above the plywood.
* Strip of 8 RGBW neopixels
* Battery (18V Ryobi)
* Battery clip
* Bridge Rectifier (or 4 diodes)
* 7812 12V voltage rectifier.
* N-channel MOSFET

### Circuit
![Image of circuit](https://github.com/bapril/OZ_Fire/images/circuit.png)

Key elements: (Left to Right, then Top Down)
* Battery, I use a 18V Ryobi +ONE battery, connected by a clip freed from an old drill.
* Bridge rectifier, prevents clipping the batter on backwards from becoming a problem.
* 7812 rectifier, to turn the ~18V into 12V that the Arduino can take in (I use a barrel-jack).
* Arduino Uno Rev3.
* Button and pull-down resistor. (Pin 2).
* N-channel MOSFET feeding a large PC fan with a cap. to take the whine out of the PWM.
* A strip of (8) RGBW Neopixels tied to Pin 6
