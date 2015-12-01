
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int POTPIN = A1; //potentiometer connected to A1
int pot_value; //for reading value of potentiometer
const int speakerPin = 9; //piezo speaker connected to pin 9 for sound
const int buttonPin = 8; //push button uses arduino pull up resister. Connecected to pin 8

int randomPos1; //random x position for enemy
int randomPos2; //random y position for enemy
int randomSpawn; //random amount of enemies to spawn
int randomShoot; //random value to decide if enemy should shoot
int score = 0; //how many enemies you killed
bool dead = false; //if you died

int e1y; //y pos of enemy 1
int e1x; //x pos of enemy 1
int e2y; //y pos of enemy 2
int e2x; //x pos of enemy 2
int e3y; //y pos of enemy 2
int e3x; //x pos of enemy 2
 
int py; //y pos of player

const byte p = 0; //used to hold the player glyph
const byte e = 1; //used to hold the enemy glyph
const byte b = 2; //used to hold the bullet glyph
const byte w = 3; //used to hold the wall glyph

byte player[8] = //glyph of the player
  { B11100,
    B11100,
    B11000,
    B11111,
    B11000,
    B11000,
    B11100,
    B00000};
    
 byte enemy[8] = //glyph of the enemy
  { B01110,
    B01110,
    B00100,
    B11111,
    B00100,
    B00100,
    B01010,
    B10001};
    
   byte bullet[8] = //glyph of the bullet
  { B00000,
    B00000,
    B11111,
    B11111,
    B11111,
    B00000,
    B00000,
    B00000};
    
   byte wall[8] = //glyph of the wall
  { B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110};
    
  void setup() {
  lcd.begin(19, 4); // set up the LCD's number of columns and rows: 
  pinMode(8,INPUT_PULLUP); //initialize push button using arduino pull up resister 
  Serial.begin(9600); //initialize serial for debugging/testing purposes
  lcd.createChar(0,player); //create char from glyph 1
   lcd.createChar(1,enemy); //create char from glyph 2
  lcd.createChar(2,bullet); //create char from glyph 3
  lcd.createChar(3,wall); //create char from glyph 4
  
  //intro to game
  lcd.clear();
  lcd.setCursor(9,1);
  lcd.print("War");
  delay(3000);
  lcd.clear();
  
  //get random positions for enemies
    //save a random number from 0 to 3
  randomPos1 = random(4);
  //save a random number from 4 to 17
  randomPos2 = random(4,17);
    //save a random number from 1 to 3
  randomSpawn = random(1,3);

lcd.setCursor(randomPos2, randomPos1);
lcd.write(e);
  
}

void loop(){
  
  //clock
  if(millis()/1000 < 100){
  lcd.setCursor(18,0);
  lcd.print(millis()/1000);
  }
  else
  {
  lcd.setCursor(18,0);
  lcd.print(millis()/10000);
  }
  
    //score
  lcd.setCursor(18,3);
  lcd.print(score);
  
    //wall
  lcd.setCursor(17,0);
  lcd.write(w);
  lcd.setCursor(17,1);
  lcd.write(w);
  lcd.setCursor(17,2);
  lcd.write(w);
  lcd.setCursor(17,3);
  lcd.write(w);
  
  //read voltage from the potentiometer
  pot_value = analogRead(POTPIN);
  Serial.println(pot_value); //use for debugging
  
//use potentiometer signal to navigate board and choose position to make move
if(pot_value <= 250)//position 1
{
 lcd.setCursor(0, 1);
 lcd.print(" ");
 lcd.setCursor(0, 2);
 lcd.print(" ");
 lcd.setCursor(0, 3);
 lcd.print(" ");
  
 //put player in position
 lcd.setCursor(0, 0);
 lcd.write(p);
 
 py = 0;
}
else
if(pot_value > 250 && pot_value <= 500)//position 2
{
 lcd.setCursor(0, 0);
 lcd.print(" ");
 lcd.setCursor(0, 2);
 lcd.print(" ");
 lcd.setCursor(0,3);
 lcd.print(" ");
  
 //put player in position
 lcd.setCursor(0, 1);
 lcd.write(p);
 
 py=1;
}
else
if(pot_value > 500 && pot_value <= 750)//position 3
{
 lcd.setCursor(0, 0);
 lcd.print(" ");
 lcd.setCursor(0, 1);
 lcd.print(" ");
 lcd.setCursor(0, 3);
 lcd.print(" ");
  
 //put player in position
 lcd.setCursor(0, 2);
 lcd.write(p);
 py = 2;
}
else
if(pot_value > 750 && pot_value <= 1023)//position 4
{
 lcd.setCursor(0, 0);
 lcd.print(" ");
 lcd.setCursor(0, 1);
 lcd.print(" ");
 lcd.setCursor(0, 2);
 lcd.print(" ");
  
  //put player in position
 lcd.setCursor(0, 3);
 lcd.write(p);
 
 py=3;
}

if(millis()/1000 % 10 == 0) //every 10 seconds spawn an enemy
{
  lcd.clear();
  
  
if(pot_value <= 250)//position 1
{
 lcd.setCursor(0, 1);
 lcd.print(" ");
 lcd.setCursor(0, 2);
 lcd.print(" ");
 lcd.setCursor(0, 3);
 lcd.print(" ");
  
 //put player in position
 lcd.setCursor(0, 0);
 lcd.write(p);
 
 py = 0;
}
else
if(pot_value > 250 && pot_value <= 500)//position 2
{
 lcd.setCursor(0, 0);
 lcd.print(" ");
 lcd.setCursor(0, 2);
 lcd.print(" ");
 lcd.setCursor(0,3);
 lcd.print(" ");
  
 //put player in position
 lcd.setCursor(0, 1);
 lcd.write(p);
 
 py = 1;
}
else
if(pot_value > 500 && pot_value <= 750)//position 3
{
 lcd.setCursor(0, 0);
 lcd.print(" ");
 lcd.setCursor(0, 1);
 lcd.print(" ");
 lcd.setCursor(0, 3);
 lcd.print(" ");
  
 //put player in position
 lcd.setCursor(0, 2);
 lcd.write(p);
 
 py = 2;
}
else
if(pot_value > 750 && pot_value <= 1023)//position 4
{
 lcd.setCursor(0, 0);
 lcd.print(" ");
 lcd.setCursor(0, 1);
 lcd.print(" ");
 lcd.setCursor(0, 2);
 lcd.print(" ");
 
  //put player in position
 lcd.setCursor(0, 2);
 lcd.write(p);
 
 py = 3;
}
  
  //save a random number from 0 to 3
  randomPos1 = random(4);
  //save a random number from 4 to 17
  randomPos2 = random(4,16);
  //save a random number from 1 to 3
  randomSpawn = random(1,3);
  
  e1y = randomPos1; //enemy 1 position
  e1x = randomPos2;
  
lcd.setCursor(randomPos2, randomPos1);
lcd.write(e);

  //clock
  if(millis()/1000 < 100){
  lcd.setCursor(18,0);
  lcd.print(millis()/1000);
  }
  else
  {
  lcd.setCursor(18,0);
  lcd.print(millis()/10000);
  }
  
  //score
  lcd.setCursor(18,3);
  lcd.print(score);
  
  //wall
  lcd.setCursor(17,0);
  lcd.write(w);
  lcd.setCursor(17,1);
  lcd.write(w);
  lcd.setCursor(17,2);
  lcd.write(w);
  lcd.setCursor(17,3);
  lcd.write(w);

delay(990);
}
  
  
  int buttonState = digitalRead(8); //read if player has pressed button to make move

if(buttonState == LOW)//if player has shot
{
 //use potentiometer signal to navigate board and choose position to make move
if(pot_value <= 250)//position 1
{
  for(int i=1; i < 17; i++){
    lcd.setCursor(i, 0);
   lcd.write(b);
  if(i>1)
   {
   lcd.setCursor(i-1, 0);
   lcd.print(" ");
   delay(100);
   } 
   lcd.setCursor(16, 0);
   lcd.print(" ");
  }
  
  if(e1y == 0){
  score++;
  e1y = 9;}
}
else
if(pot_value > 250 && pot_value <= 500)//position 2
{
  for(int i=1; i < 17; i++){
    lcd.setCursor(i, 1);
   lcd.write(b);
  if(i>1)
   {
   lcd.setCursor(i-1, 1);
   lcd.print(" ");
   delay(100);
   } 
   lcd.setCursor(16, 1);
   lcd.print(" ");
  }
  
  if(e1y == 1){
  score++;
  e1y = 9;}
}
else
if(pot_value > 500 && pot_value <= 750)//position 3
{
  for(int i=1; i < 17; i++){
    lcd.setCursor(i, 2);
   lcd.write(b);
  if(i>1)
   {
   lcd.setCursor(i-1, 2);
   lcd.print(" ");
   delay(100);
   } 
   lcd.setCursor(16, 2);
   lcd.print(" ");
  }
  if(e1y == 2){
  score++;
  e1y = 9;
  }
}
else
if(pot_value > 750 && pot_value <= 1023)//position 4
{
  for(int i=1; i < 17; i++){
    lcd.setCursor(i, 3);
   lcd.write(b);
  if(i>1)
   {
   lcd.setCursor(i-1, 3);
   lcd.print(" ");
   delay(100);
   } 
   lcd.setCursor(16, 3);
   lcd.print(" ");
  }
  if(e1y == 3){
  score++;
  e1y = 9;
  }
}
 
  
}

//not working yet
/*

  //save a random number from 0 to 3 
  randomShoot = random(10);
  
  if(randomShoot % 0)
  {
    

     
if(e1y==0)//position 1
{
  for(int i=e1x; i >= 0; i--){
    lcd.setCursor(i, 0);
   lcd.write(b);
  if(i<e1x)
   {
   lcd.setCursor(i-1, 0);
   lcd.print(" ");
   delay(100);
   } 
   lcd.setCursor(0, 0);
   lcd.print(" ");
  }
  
  if(py == 0)
  dead = true;

}
else
if(e1y==2)//position 2
{
  for(int i=e1x; i >= 0; i--){
    lcd.setCursor(i, 1);
   lcd.write(b);
  if(i<e1x)
   {
   lcd.setCursor(i-1, 1);
   lcd.print(" ");
   delay(100);
   } 
   lcd.setCursor(0, 1);
   lcd.print(" ");
  }
  
  if(py == 1)
  dead = true;
  
}
else
if(e1y==2)//position 3
{
   for(int i=e1x; i >= 0; i--){
    lcd.setCursor(i, 2);
   lcd.write(b);
  if(i<e1x)
   {
   lcd.setCursor(i-1, 2);
   lcd.print(" ");
   delay(100);
   } 
   lcd.setCursor(0, 2);
   lcd.print(" ");
  }
  
  if(py == 2)
  dead = true;
}
else
if(e1y==3)//position 4
{
  for(int i=e1x; i >= 0; i--){
    lcd.setCursor(i, 3);
   lcd.write(b);
  if(i<e1x)
   {
   lcd.setCursor(i-1, 3);
   lcd.print(" ");
   delay(100);
   } 
   lcd.setCursor(0, 3);
   lcd.print(" ");
  }
  
  if(py == 3)
  dead = true;    
    
    
  }

  }
*/

//not working yet
/*
if(dead)
{
 lcd.clear();
  lcd.setCursor(6,1);
  lcd.print("You Died.");
  lcd.setCursor(6,3);
  lcd.print("Score: ");
  lcd.print(score);
  delay(99999);
}
 */ 
  



}
