# Simon Game
A miniature version of the Simon game, using an ESP32 microcontroller, 4 buttons, 4 LEDs and an active buzzer.
By default you need to complete 5 levels to win.
After a win you'll hear a victory melody, if you click unsuccessfully, a sad melody will play.
### Note that resistors in front of the LEDs are not necessary, as 3.3V is perfectly acceptable. If you're using an Arduino (5V) or other power source, be sure to protect the LEDs with appropriate resistors.
#### With a slight modification to the code (changing the number of clicks), you can customize the number of levels to win.
More information about the history and rules of the game: https://en.wikipedia.org/wiki/Simon_(game)
