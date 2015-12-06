
**DIY-Gameboy Project**
============
------------

**Copyright Notice**
------------

This project uses the Unlicense. It is free and unencumbered software released into the public domain.

For more information, please refer to http://unlicense.org

**Overview**
------------

A handheld gaming device made using a simple circuit and an Arduino Uno. This project uses an ethernet shield's micro sd slot to
read integer values to be used to access different control structures (if statements) that contain hardcoded games. This gives the 
illusion that the gameboy is reading the games completely from the SD card like a game cartridge despite the reality that the games
are hardcoded into the sketch and just inaccessible until it's cartridge is accessed. The games on the gameboy will be played with
a potentiometer and push button switch as input and an lcd module as output.

**Project Completion Progress**
------------
A demonstration build of project has been completed however in it's current state the SD card game cartridge swapping feature has not been tested or completed. However, the three example games can be run and played on the demonstration build just fine. For more information on the demonstration build see below.

**Libraries**
------------

This project uses the SD card library that is automatically included in the official Arduino IDE to use the SD card slot on the ethernet shield.
You must include the <SD.h> header file in your code to use this library. Refer to https://www.arduino.cc/en/Reference/SD for more information on the SD library.

This project also uses the LiquidCrystal library that is automatically included in the official Arduino IDE to drive the LCD screen. You must include the <LiquidCrystal.h> header file in your code to use this library. Refer to https://www.arduino.cc/en/Reference/LiquidCrystal for more information on the Liquid Crystal Library.

**Materials**
------------

- Arduino Uno
- 1 LCD Screen based on the Hitachi HD44780 chipset
- 2 Rotary Potentiometers
- 1 Push Button Switch
- Battery to DC Power Module Compatible with Arduino Uno
- Jumper Wires
- Soldering Kit
- (optional) Ethernet Shield for Game Cartridge Swapping Feature
- (optional) Bread Board to Make Circuit Management Easier

**Instructions**
------------

#### **Design**

The design of this portable game console is simple. The two potentiometers, push button switch, piezo buzzer and LCD screen are all wired to the arduino UNO with the option of attatching the ethernet shield on top.  

- The potentiometer attatched to the LCD screen adjusts the contrast
- The second potentiometer is wired to pin A1 and is used for analog game control
- The push button switch is wired to digital pin 8 and used as a digital button using the arduino's internal pull up resister for game control
- The piezo buzzer is wired to digital pin 9 and used for game sound
- The arduino is powered by the battery to DC module



**Below is an image of the cicuit diagram of the build:**

**Note:**  
The LCD screen's pin 15 is wired to 3 volts and the LCD screen's pin 16 is wired to ground. This is to utilize the LCD screens backlight and is not necessary.

![Circuit Diagram](http://i.imgur.com/P3uf4fD.jpg)

**Below is an image of the demonstration build's circuit before the soldering of the LCD screen:**

**Note:**  

The 12 wires in the back of the image are attatched to the breadboard according to the circuit diagram.

Off screen: The piezo buzzer, potentiometers and push button are all attatched to the arduino according to the circuit diagram.

![Circuit Diagram](http://i.imgur.com/SgkcfKT.jpg)

#### **Games**

Currently there are three example games written for the console:
- TicTacToe
- Rhythm Hero
- War

All three games compile and load on the console.  

**Note:**  
Be aware that War is incomplete and the enemies do not shoot back as of yet and that Rhythm Hero has a buggy cursor. See the documentation in the game's code for more information.

  #### **Installation**
Wires were soldered together and placed into a cardboard box with paper taped to it that acts as the console's case. Holes were cut in the front of the case to let the push button switch, joystick potentiometer and lcd screen through for outside use. A similar whole was cut on the side of the case for the contrast adjusting potentiometer. And a final hole was cut in the back of the case on the bottom for the battery module to go through and provide the console with power.

**Below are images of the final demonstration build.**

![demonstration build front](http://i.imgur.com/USVvitw.jpg)
![demonstration build side](http://i.imgur.com/MGreaOl.jpg)
![demonstration build back](http://i.imgur.com/4ws9i3O.jpg)


**Manifest**
------------

**(incomplete) Sketch to drive SD card game cartridge swapping functionality:**  
- gameboy.ino  

**Game Sketch Examples:**  
- TicTacToe.ino
- War.ino
- RhythmHero.ino


**Contact Info**
------------

This project was designed and created entirely by Brett Prokopchuk for a CS 207 class.
He can be contacted at:
**email:** brett-prokopchuk@hotmail.com
**twitter:** @brettprokopchuk
