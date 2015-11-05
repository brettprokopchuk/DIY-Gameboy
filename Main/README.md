
**DIY-Gameboy Project**
============
**Overview**
------------

A handheld gaming device made using a simple circuit and an Arduino Uno. This project uses an ethernet shield's micro sd slot to
read integer values to be used to access different control structures (if statements) that contain hardcoded games. This gives the 
illusion that the gameboy is reading the games completely from the SD card like a game cartridge despite the reality that the games
are hardcoded into the sketch and just inaccessible until it's cartridge is accessed. The games on the gameboy will be played with
a potentiometer and push button switch as input and an lcd module as output.

**Libraries**
------------

This project uses the SD card library that is automatically included in the Arduino software.
You must include the <SD.h> header file in your code to use this library.

**Sketch File:**
gameboy.ino

**Copyright Notice**
------------

This project uses the Unlicense. It is free and unencumbered software released into the public domain.

For more information, please refer to http://unlicense.org

**Contact Info**
------------

This project was designed and created entirely by Brett Prokopchuk for a CS 207 class.
He can be contacted at:
**email:** brett-prokopchuk@hotmail.com
**twitter:** @brettprokopchuk