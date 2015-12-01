/*
Rhythm Hero Game Sketch

This sketch uses a 4x20 hitachi hd44780 lcd screen, potentiometer connected to a1, piezo buzzer connected to pin 9 and push button connected to pin 8 of an arduino uno to play
the game Rhythm Hero a very dumbed down guitar hero clone. It and uses the potentiometer as control and button for action.

Bugs: 
Cursor tends to jump. Very hard to make the cursor remain stationary while screen autoscrolls.

Made by Brett Prokopchuk
Nov, 2015
This code is in the public domain.	 
 */
 
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int POTPIN = A1; //potentiometer connected to A1
int pot_value; //for reading value of potentiometer
const int speakerPin = 9; //piezo speaker connected to pin 9 for sound
const int buttonPin = 8; //push button uses arduino pull up resister. Connecected to pin 8 

bool gameOver = false; //exit loop after time limit has elapsed. Allows space to reset game.
int randNumber; //random number to generate music notes 
int queue[99]; //acts as queue so game knows position of music notes when button is pressed.
int order = 0; //order for queue
int order2 = 0; //order for queue
int score = 0; //keeps track of player score in game
int actionTime = 20; //amount of spaces away notes start at is 20. Count down to zero to know when button presses matter.
int stay = 1; //to help make cursor not scroll
int timeLimit = 40; //time limit till game ends
int i = 20; //starting position for notes. Fluctuates every loop.
int playerPosition; //position potentiometer is in (1-4)

const byte n = 0; //used to hold the music note glyph

byte note[8] = //glyph of the music note
  { B00000,
    B00100,
    B00110,
    B00111,
    B00100,
    B11100,
    B11100,
    B11100};
    
    
void setup() {
  lcd.begin(19, 4); // set up the LCD's number of columns and rows: 
  pinMode(8,INPUT_PULLUP); //initialize push button using arduino pull up resister 
  Serial.begin(9600); //initialize serial for debugging/testing purposes
  lcd.createChar(0,note); //create char from glyph 1
  
  //intro to game
  lcd.clear();
  lcd.setCursor(7,1);
  lcd.print("Rhythm");
  lcd.setCursor(8,2);
  lcd.print("Hero");
  delay(3000);
  lcd.clear();
  
}


void loop(){
  
  while(!gameOver)//exit loop after time limit
  {
  
  //read voltage from the potentiometer
  pot_value = analogRead(POTPIN);
  
  //save a random number from 0 to 3
  randNumber = random(4);
  queue[order] = randNumber; //keep track of position of the music notes and have them in a queue
  order++; //go to next slot in queue
  
 //generate music note in random positon and scroll it
 lcd.noCursor();
 lcd.autoscroll();
 lcd.setCursor(i,randNumber);
 lcd.write(n);
 lcd.noAutoscroll();
  
     
  //get rid of notes at end
  lcd.setCursor(stay, 0);
  lcd.print(" ");
  lcd.setCursor(stay, 1);
  lcd.print(" ");
  lcd.setCursor(stay, 2);
  lcd.print(" ");
  lcd.setCursor(stay, 3);
  lcd.print(" ");
  
  //activate cursor for game navigation
  lcd.cursor();
  lcd.blink();
  
  Serial.println(pot_value); //use for debugging
  
//use potentiometer signal to navigate board and choose position to make move
if(pot_value <= 250)//position 1
{
 lcd.setCursor(stay, 0);
 playerPosition = 0;
}
else
if(pot_value > 250 && pot_value <= 500)//position 2
{
   lcd.setCursor(stay, 1);
   playerPosition = 1;
}
else
if(pot_value > 500 && pot_value <= 750)//position 3
{
   lcd.setCursor(stay, 2);
   playerPosition = 2;
}
else
if(pot_value > 750 && pot_value <= 1023)//position 4
{
   lcd.setCursor(stay, 3);
   playerPosition = 3;
}
   
   //us number minipulation so cursor doesnt move with note
   if(stay == 19)
   stay = 0;
   else
   stay++;
   
   //use number manipulation to make notes scroll one by one
   if(i == 20)
   i = 1;
   else
   i++;

int buttonState = digitalRead(8); //read if player has pressed button to make move


//if actionTime is 0 then notes have arrived at player's cursor
 if(actionTime > 0){
actionTime --;}
else{
  
if(buttonState == LOW && queue[order2] == playerPosition)//if player gets note with button
{
score++; //increase score by one
 tone(speakerPin, 300); //make sound indication
 delay(150);
 noTone(speakerPin);
}
 order2++; //queue next note position
 
}

  delay(600); //delay scrolling
  
  if(millis()/1000 == timeLimit) //if over time limit
    gameOver = true; //end game
  
}
  
  //end game screen
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print("Game Over");
  lcd.setCursor(6,2);
  lcd.print("Score: ");
  lcd.print(score); //print score
  lcd.noCursor();
  delay(3000);
  timeLimit = (timeLimit*2) + 3;

  while(1!=2) //never ending loop. Game currently breaks after round 1.
  {
  }
  
}
