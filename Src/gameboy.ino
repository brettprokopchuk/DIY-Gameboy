/*
Gameboy Sketch

This program uses an ethernet shield to read integer values from an sd card to act as a game cartidge. These integer values open up access to hardcoded games that are to be played on an 
lcd screen. This creates the illusion that this gameboy project is reading games completely from the sd cards despite the games being hardcoded into the sketch.

Made by Brett Prokopchuk
Oct 29, 2015
This code is in the public domain.	 
 */
 
#include <SD.h>

File myFile;
enum gameStates {noGame = 0, Game1 = 1, Game2 = 2};
int readGame = 0;

void setup()
{
 // Open serial communications 
  Serial.begin(9600);

  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
   
   
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

}

void loop()
{
  
  // open the file on the sd card for reading:
  myFile = SD.open("game.txt");
  if (myFile) {
    Serial.println("game.txt:"); //give serial feed back for debugging
    
        // read the integer from the sd card cartridge and save it to the readGame variable
    while (myFile.available()) {
    	readGame = myFile.read();
    }
    // close the file:
    myFile.close();
  } else {
  	// if the file didn't open then readGame should be 0
    readGame = 0;
  }
    
    
    if (readGame = noGame) //there is no game cartridge/SD card in the game/SD card slot
    {
      //put desired code for no game here
    }

    if (readGame = Game1) //the game cartridge/SD card in the slot is reading integer 1/game 1
    {
      //put game code for first game here.
    }
    
    if (readGame = Game2) //the game cartridge/SD card in the slot is reading integer 2/game 2
    {
      //put game code for second game here.
    }


}


