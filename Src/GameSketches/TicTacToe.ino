/*
TicTacToe Game Sketch

This sketch uses a 4x20 hitachi hd44780 lcd screen, potentiometer connected to a1, piezo buzzer connected to pin 9 and push button connected to pin 8 of an arduino uno to play
the game tic tac toe. It is multiplayer (can not play against computer) and uses the potentiometer as control and button for action.

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
int turn = 1; //Uses to cycle from player 1's turn to player 2's turn

int p1 = 0; //used to keep track of position 1 on the tic tac toe board
int p2 = 0; //used to keep track of position 2 on the tic tac toe board
int p3 = 0; //used to keep track of position 3 on the tic tac toe board
int p4 = 0; //used to keep track of position 4 on the tic tac toe board
int p5 = 0; //used to keep track of position 5 on the tic tac toe board
int p6 = 0; //used to keep track of position 6 on the tic tac toe board
int p7 = 0; //used to keep track of position 7 on the tic tac toe board
int p8 = 0; //used to keep track of position 8 on the tic tac toe board
int p9 = 0; //used to keep track of position 9 on the tic tac toe board

const int x1 = 1; //used to hold top half of X glyph for middle three rows of tic tac toe board
const int x2 = 2; //used to hold bottom half of X glyph for middle three rows of tic tac toe board
const int o1 = 6; //used to hold top half of O glyph for middle three rows of tic tac toe board
const int o2 = 7; //used to hold bottom half of O glyph for middle three rows of tic tac toe board
const int d = 3; //used to hold glyph for lines of tic tac toe board going down
const int a1 = 4; //used to hold glyph for lines of tic tac toe board going across. The top half of it.
const int a2 = 5; //used to hold glyph for lines of tic tac toe board going across. The bottom half of it.


byte ex1[8] = //glyph of top half of x for middle row of board
  { B11111,
    B11111,
    B11111,
    B11111,
    B10001,
    B10001,
    B01010,
    B00100};
    
    byte ex2[8] = //glyph of bottom half of x for middle row of board
  { B01010,
    B10001,
    B10001,
    B00000,
    B11111,
    B11111,
    B11111,
    B11111};
        
    byte oh1[8] =//glyph of top half of o for middle row of board
  { B11111,
    B11111,
    B11111,
    B11111,
    B01110,
    B10001,
    B10001,
    B10001};
    
    byte oh2[8] = //glyph of bottom half of o for middle row of board
  { B10001,
    B10001,
    B01110,
    B00000,
    B11111,
    B11111,
    B11111,
    B11111};
    
    byte down[8] = //glyph of tic tac toe board lines going down
  { B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111};
    
   byte across1[8] = //glyph of tic tac toe board lines going across. The top half.
  { B00000,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111,
    B11111,
    B11111};
    
   byte across2[8] = //glyph of tic tac toe board lines going across. The bottom half.
  { B11111,
    B11111,
    B11111,
    B11111,
    B00000,
    B00000,
    B00000,
    B00000};
    
    
void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 4);
  pinMode(8,INPUT_PULLUP); //initialize push button using arduino pull up resister 
  Serial.begin(9600); //initialize serial for debugging/testing purposes
  lcd.createChar(1,ex1); //create char from glyph 1
  lcd.createChar(2,ex2); //create char from glyph 2
  lcd.createChar(6,oh1); //create char from glyph 3
  lcd.createChar(7,oh2); //create char from glyph 4
  lcd.createChar(3,down); //create char from glyph 5
  lcd.createChar(4,across1); //create char from glyph 6
  lcd.createChar(5,across2); //create char from glyph 7

  
  //intro to game
  lcd.clear();
  lcd.setCursor(6,1);
  lcd.print("Tic Tac");
  lcd.setCursor(8,2);
  lcd.print("Toe");
  delay(3000);
  lcd.clear();
  
  
   //down of board
  lcd.setCursor(8, 0);
  lcd.write(d);
  lcd.setCursor(8, 1);
  lcd.write(d);
  lcd.setCursor(8, 2);
  lcd.write(d);
  lcd.setCursor(8, 3);
  lcd.write(d);
  lcd.setCursor(12, 0);
  lcd.write(d);
  lcd.setCursor(12, 1);
  lcd.write(d);
  lcd.setCursor(12, 2);
  lcd.write(d);
  lcd.setCursor(12, 3);
  lcd.write(d);

  //accross of board
  //bottom a1
  lcd.setCursor(5, 2);
  lcd.write(a1);
  lcd.setCursor(6, 2);
  lcd.write(a1);
  lcd.setCursor(7, 2);
  lcd.write(a1);
  lcd.setCursor(9, 2);
  lcd.write(a1);
  lcd.setCursor(10, 2);
  lcd.write(a1);
  lcd.setCursor(11, 2);
  lcd.write(a1);
  lcd.setCursor(13, 2);
  lcd.write(a1);
  lcd.setCursor(14, 2);
  lcd.write(a1);
  lcd.setCursor(15, 2);
  lcd.write(a1);
  
  //top a2
  lcd.setCursor(5, 1);
  lcd.write(a2);
  lcd.setCursor(6, 1);
  lcd.write(a2);
  lcd.setCursor(7, 1);
  lcd.write(a2);
  lcd.setCursor(9, 1);
  lcd.write(a2);
  lcd.setCursor(10, 1);
  lcd.write(a2);
  lcd.setCursor(11, 1);
  lcd.write(a2);
  lcd.setCursor(13, 1);
  lcd.write(a2);
  lcd.setCursor(14, 1);
  lcd.write(a2);
  lcd.setCursor(15, 1);
  lcd.write(a2);


}

void loop() {

    //read voltage from the potentiometer
  pot_value = analogRead(POTPIN);
  
  //activate cursor for game navigation
  lcd.cursor();
  lcd.blink();
  
//use potentiometer signal to navigate board and choose position to make move
if(pot_value <= 113)//position 1
{
 lcd.setCursor(6, 0);
}
else
if(pot_value > 113 && pot_value <= 226)//position 2
{
   lcd.setCursor(10, 0);
}
else
if(pot_value > 226 && pot_value <= 339)//position 3
{
   lcd.setCursor(14, 0);
}
else
if(pot_value > 339 && pot_value <= 452)//position 4
{
   lcd.setCursor(6, 2);
}
else
if(pot_value > 452 && pot_value <= 565)//position 5
{
   lcd.setCursor(10, 2);
}
else
if(pot_value > 565 && pot_value <= 678)//position 6
{
   lcd.setCursor(14, 2);
}
else
if(pot_value > 678 && pot_value <= 791)//position 7
{
   lcd.setCursor(6, 3);
}
else
if(pot_value > 791 && pot_value <= 904)//position 8
{
   lcd.setCursor(10, 3);
}
else
if(pot_value > 904)//position 9
{
   lcd.setCursor(14, 3);
}




int buttonState = digitalRead(8); //read if player has pressed button to make move

//below is the code for making a move based on where the curser was when the player hit the button.

//NOT MIDDLE, EX
if((buttonState == LOW) && (pot_value <= 339 || pot_value > 678) && turn == 1){


if(pot_value <= 113 && p1 == 0)//position 1
{
 lcd.print("X");
 turn = 2;
 p1 = 1;
 tone(speakerPin, 300);
 delay(300);
 noTone(speakerPin);
}
else
if(pot_value > 113 && pot_value <= 226 && p2 == 0)//position 2
{
 lcd.print("X");
 turn = 2;
 p2 = 1;
 tone(speakerPin, 300);
 delay(300);
 noTone(speakerPin);
}
else
if(pot_value > 226 && pot_value <= 339 && p3 == 0)//position 3
{
 lcd.print("X");
 turn = 2;
 p3 = 1;
 tone(speakerPin, 300);
 delay(300);
 noTone(speakerPin);
}
else
if(pot_value > 678 && pot_value <= 791 && p7 == 0)//position 7
{
 lcd.print("X");
 turn = 2;
 p7 = 1;
 tone(speakerPin, 300);
 delay(300);
 noTone(speakerPin);
}
else
if(pot_value > 791 && pot_value <= 904 && p8 == 0)//position 8
{
 lcd.print("X");
 turn = 2;
 p8 = 1;
 tone(speakerPin, 300);
 delay(300);
 noTone(speakerPin);
}
else
if(pot_value > 904 && p9 == 0)//position 9
{
 lcd.print("X");
 turn = 2;
 p9 = 1;
 tone(speakerPin, 300);
 delay(300);
 noTone(speakerPin);
}

delay(700);
}


else //NOT MIDDLE OH
if((buttonState == LOW) && (pot_value <= 339 || pot_value > 678) && turn == 2){
 
 if(pot_value <= 113 && p1 == 0)//position 1
{
 lcd.print("O");
 p1 = 2;
 turn = 1;
 tone(speakerPin, 300);
 delay(300);
 noTone(speakerPin);
}
else
if(pot_value > 113 && pot_value <= 226 && p2 == 0)//position 2
{
 lcd.print("O");
 p2 = 2;
 turn = 1;
 tone(speakerPin, 300);
 delay(300);
 noTone(speakerPin);
}
else
if(pot_value > 226 && pot_value <= 339 && p3 == 0)//position 3
{
 lcd.print("O");
 p3 = 2;
 turn = 1;
 tone(speakerPin, 300);
 delay(300);
 noTone(speakerPin);
}
else
if(pot_value > 678 && pot_value <= 791 && p7 == 0)//position 7
{
 lcd.print("O");
 p7 = 2;
 turn = 1;
 tone(speakerPin, 300);
 delay(300);
 noTone(speakerPin);
}
else
if(pot_value > 791 && pot_value <= 904 && p8 == 0)//position 8
{
 lcd.print("O");
 p8 = 2;
 turn = 1;
 tone(speakerPin, 300);
 delay(300);
 noTone(speakerPin);
}
else
if(pot_value > 904 && p9 == 0)//position 9
{
 lcd.print("O");
 p9 = 2;
 turn = 1;
 tone(speakerPin, 300);
 delay(300);
 noTone(speakerPin);
}
 
 delay(700);
}


else //MIDDLE EX
if((buttonState == LOW) && (pot_value > 339 || pot_value <= 678) && turn == 1){

 
if(pot_value > 339 && pot_value <= 452 && p4 == 0)//position 4
{
   lcd.noCursor();
   lcd.write(x2);
   lcd.setCursor(6, 1);
   lcd.write(x1);
   p4 = 1;
   turn = 2;
   tone(speakerPin, 300);
   delay(300);
   noTone(speakerPin);
   delay(700);
}
else
if(pot_value > 452 && pot_value <= 565 && p5 == 0)//position 5
{
   lcd.noCursor();
   lcd.write(x2);
   lcd.setCursor(10, 1);
   lcd.write(x1);
   p5 = 1;
   turn = 2;
   tone(speakerPin, 300);
   delay(300);
   noTone(speakerPin);
   delay(700);
}
else
if(pot_value > 565 && pot_value <= 678 && p6 == 0)//position 6
{
   lcd.noCursor();
   lcd.write(x2);
   lcd.setCursor(14, 1);
   lcd.write(x1);
   p6 = 1;
   turn = 2;
   tone(speakerPin, 300);
   delay(300);
   noTone(speakerPin);
   delay(700);
}
 
}


else// MIDDLE OH
if((buttonState == LOW) && (pot_value > 339 || pot_value <= 678) && turn == 2){
 
 
 if(pot_value > 339 && pot_value <= 452 && p4 == 0)//position 4
{
   lcd.noCursor();
   lcd.write(o2);
   lcd.setCursor(6, 1);
   lcd.write(o1);
   p4 = 2;
   turn = 1;
   tone(speakerPin, 300);
   delay(300);
   noTone(speakerPin);
   delay(700);
}
else
if(pot_value > 452 && pot_value <= 565 && p5 == 0)//position 5
{
   lcd.noCursor();
   lcd.write(o2);
   lcd.setCursor(10, 1);
   lcd.write(o1);
   p5 = 2;
   turn = 1;
   tone(speakerPin, 300);
   delay(300);
   noTone(speakerPin);
   delay(700);
}
else
if(pot_value > 565 && pot_value <= 678 && p6 == 0)//position 6
{
   lcd.noCursor();
   lcd.write(o2);
   lcd.setCursor(14, 1);
   lcd.write(o1);
   p6 = 2;
   turn = 1;
   tone(speakerPin, 300);
   delay(300);
   noTone(speakerPin);
   delay(700);
}
 
 
}



//win conditon check

//ex wins
if(((p1 == p2) && (p1 == p3) && (p1==1)) || ((p4 == p5) && (p4 == p6) && (p4==1)) 
 || ((p7 == p8) && (p7 == p9) && (p7==1)) || ((p1 == p4) && (p1 == p7)&& (p1==1))
 || ((p2 == p5) && (p2 == p8)&& (p2==1)) || ((p3 == p6) && (p3 == p9) && (p3==1)) 
 || ((p1 == p5) && (p1 == p9) && (p1==1)) || ((p7 == p5) && (p5 == p3) && (p5==1)))
 {
   lcd.clear();
  lcd.setCursor(6,0);
  lcd.print("Game Over");
  lcd.setCursor(7,2);
  lcd.print("X Wins!");
  delay(3000);
  p1 = 0;
  p2 = 0;
  p3 = 0;
  p4 = 0;
  p5 = 0;
  p6 = 0;
  p7 = 0;
  p8 = 0;
  p9 = 0;
  lcd.clear();
  //reset game
  
  //down of board
  lcd.setCursor(8, 0);
  lcd.write(d);
  lcd.setCursor(8, 1);
  lcd.write(d);
  lcd.setCursor(8, 2);
  lcd.write(d);
  lcd.setCursor(8, 3);
  lcd.write(d);
  lcd.setCursor(12, 0);
  lcd.write(d);
  lcd.setCursor(12, 1);
  lcd.write(d);
  lcd.setCursor(12, 2);
  lcd.write(d);
  lcd.setCursor(12, 3);
  lcd.write(d);

  //accross of board
  //bottom a1
  lcd.setCursor(5, 2);
  lcd.write(a1);
  lcd.setCursor(6, 2);
  lcd.write(a1);
  lcd.setCursor(7, 2);
  lcd.write(a1);
  lcd.setCursor(9, 2);
  lcd.write(a1);
  lcd.setCursor(10, 2);
  lcd.write(a1);
  lcd.setCursor(11, 2);
  lcd.write(a1);
  lcd.setCursor(13, 2);
  lcd.write(a1);
  lcd.setCursor(14, 2);
  lcd.write(a1);
  lcd.setCursor(15, 2);
  lcd.write(a1);
  
  //top a2
  lcd.setCursor(5, 1);
  lcd.write(a2);
  lcd.setCursor(6, 1);
  lcd.write(a2);
  lcd.setCursor(7, 1);
  lcd.write(a2);
  lcd.setCursor(9, 1);
  lcd.write(a2);
  lcd.setCursor(10, 1);
  lcd.write(a2);
  lcd.setCursor(11, 1);
  lcd.write(a2);
  lcd.setCursor(13, 1);
  lcd.write(a2);
  lcd.setCursor(14, 1);
  lcd.write(a2);
  lcd.setCursor(15, 1);
  lcd.write(a2);
   
 }
 else //oh wins
 if(((p1 == p2) && (p1 == p3) && (p1==2)) || ((p4 == p5) && (p4 == p6) && (p4==2)) 
 || ((p7 == p8) && (p7 == p9) && (p7==2)) || ((p1 == p4) && (p1 == p7)&& (p1==2))
 || ((p2 == p5) && (p2 == p8)&& (p2==2)) || ((p3 == p6) && (p3 == p9) && (p3==2)) 
 || ((p1 == p5) && (p1 == p9) && (p1==2)) || ((p7 == p5) && (p5 == p3) && (p5==2)))
 {
   lcd.clear();
  lcd.setCursor(6,0);
  lcd.print("Game Over");
  lcd.setCursor(7,2);
  lcd.print("O Wins!");
  delay(3000);
  p1 = 0;
  p2 = 0;
  p3 = 0;
  p4 = 0;
  p5 = 0;
  p6 = 0;
  p7 = 0;
  p8 = 0;
  p9 = 0;
  lcd.clear();
  //reset game
  
  //down of board
  lcd.setCursor(8, 0);
  lcd.write(d);
  lcd.setCursor(8, 1);
  lcd.write(d);
  lcd.setCursor(8, 2);
  lcd.write(d);
  lcd.setCursor(8, 3);
  lcd.write(d);
  lcd.setCursor(12, 0);
  lcd.write(d);
  lcd.setCursor(12, 1);
  lcd.write(d);
  lcd.setCursor(12, 2);
  lcd.write(d);
  lcd.setCursor(12, 3);
  lcd.write(d);

  //accross of board
  //bottom a1
  lcd.setCursor(5, 2);
  lcd.write(a1);
  lcd.setCursor(6, 2);
  lcd.write(a1);
  lcd.setCursor(7, 2);
  lcd.write(a1);
  lcd.setCursor(9, 2);
  lcd.write(a1);
  lcd.setCursor(10, 2);
  lcd.write(a1);
  lcd.setCursor(11, 2);
  lcd.write(a1);
  lcd.setCursor(13, 2);
  lcd.write(a1);
  lcd.setCursor(14, 2);
  lcd.write(a1);
  lcd.setCursor(15, 2);
  lcd.write(a1);
  
  //top a2
  lcd.setCursor(5, 1);
  lcd.write(a2);
  lcd.setCursor(6, 1);
  lcd.write(a2);
  lcd.setCursor(7, 1);
  lcd.write(a2);
  lcd.setCursor(9, 1);
  lcd.write(a2);
  lcd.setCursor(10, 1);
  lcd.write(a2);
  lcd.setCursor(11, 1);
  lcd.write(a2);
  lcd.setCursor(13, 1);
  lcd.write(a2);
  lcd.setCursor(14, 1);
  lcd.write(a2);
  lcd.setCursor(15, 1);
  lcd.write(a2);
   
 }
 else //tie
  if((p1!=0)&&(p2!=0)&&(p3!=0)&&(p4!=0)&&(p5!=0)&&(p6!=0)&&(p7!=0)&&(p8!=0)&&(p9!=0))
 {
      lcd.clear();
  lcd.setCursor(6,0);
  lcd.print("Game Over");
  lcd.setCursor(7,2);
  lcd.print("Draw!");
  delay(3000);
  p1 = 0;
  p2 = 0;
  p3 = 0;
  p4 = 0;
  p5 = 0;
  p6 = 0;
  p7 = 0;
  p8 = 0;
  p9 = 0;
  lcd.clear();
  //reset game
  
  //down of board
  lcd.setCursor(8, 0);
  lcd.write(d);
  lcd.setCursor(8, 1);
  lcd.write(d);
  lcd.setCursor(8, 2);
  lcd.write(d);
  lcd.setCursor(8, 3);
  lcd.write(d);
  lcd.setCursor(12, 0);
  lcd.write(d);
  lcd.setCursor(12, 1);
  lcd.write(d);
  lcd.setCursor(12, 2);
  lcd.write(d);
  lcd.setCursor(12, 3);
  lcd.write(d);

  //accross of board
  //bottom a1
  lcd.setCursor(5, 2);
  lcd.write(a1);
  lcd.setCursor(6, 2);
  lcd.write(a1);
  lcd.setCursor(7, 2);
  lcd.write(a1);
  lcd.setCursor(9, 2);
  lcd.write(a1);
  lcd.setCursor(10, 2);
  lcd.write(a1);
  lcd.setCursor(11, 2);
  lcd.write(a1);
  lcd.setCursor(13, 2);
  lcd.write(a1);
  lcd.setCursor(14, 2);
  lcd.write(a1);
  lcd.setCursor(15, 2);
  lcd.write(a1);
  
  //top a2
  lcd.setCursor(5, 1);
  lcd.write(a2);
  lcd.setCursor(6, 1);
  lcd.write(a2);
  lcd.setCursor(7, 1);
  lcd.write(a2);
  lcd.setCursor(9, 1);
  lcd.write(a2);
  lcd.setCursor(10, 1);
  lcd.write(a2);
  lcd.setCursor(11, 1);
  lcd.write(a2);
  lcd.setCursor(13, 1);
  lcd.write(a2);
  lcd.setCursor(14, 1);
  lcd.write(a2);
  lcd.setCursor(15, 1);
  lcd.write(a2);
 }

}
