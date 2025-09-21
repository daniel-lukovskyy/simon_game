# Simon Game
Tiny replica on simon game, using ESP32 microcontroller, 4 buttons, 4 LEDs, active buzzer.
By default there are 5 levels you should pass before win.
If you win you'll hear wining melody, if you missclick you'll hear a sad melody.
Notice that there is no need in resistors before LEDs because the voltage of 3.3V is acceptable, if you use Arduino (5V) or another source, make sure to safe your LEDs with apropriate resistors.
### By small code change (change Pushes number) you can adjust a level number till vuctory.
More info about the game history and rules : https://en.wikipedia.org/wiki/Simon_(game)
