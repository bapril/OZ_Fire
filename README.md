# OZ_FIRE
![Image of top](https://raw.githubusercontent.com/bapril/OZ_Fire/master/images/Top.jpg)
## Overview

This is a simple self-contained Arduino powered prop campfire for theatrical use.

## Acknowledgements
* Adafruit for the NeoPixel library.

## Operation

Connecting the battery should power on the Arduino only. The power LED on the UNO should be lit. Pressing the button once will move the unit into ramp-up mode where the power LED activity and brightness as well as the fan speed will grow until full power is reached. At full power the logic automatically moves into the run mode. Pushing the button again will move to the ramp-down mode moving towards power off. The time this takes can be adjusted in code. Pressing the button during the ramp-down will go to instant off.

The debounce code on the button is written for a theatrical setting. Pressing and holding the button will trigger one state change. (no matter how long you hold the button). The button could be placed so it can be actuated by foot, or by a "poker" in the fire. 

## Construction
![Image of Detail](https://raw.githubusercontent.com/bapril/OZ_Fire/master/images/Detail.jpg)
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
* Optional 7805 rectifier to take some load off of the Uno

### Circuit
![Image of circuit](https://raw.githubusercontent.com/bapril/OZ_Fire/master/images/circuit.png)

Key elements: (Left to Right, then Top Down)
* Battery, I use a 18V Ryobi +ONE battery, connected by a clip freed from an old drill.
* Bridge rectifier, prevents clipping the batter on backwards from becoming a problem.
* 7812 rectifier, to turn the ~18V into 12V that the Arduino can take in (I use a barrel-jack).
* Arduino Uno Rev3.
* Button and pull-down resistor. (Pin 2).
* N-channel MOSFET feeding a large PC fan with a cap. to take the whine out of the PWM.
* A strip of (8) RGBW Neopixels tied to Pin 6
