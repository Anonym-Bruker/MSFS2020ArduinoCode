/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

int countN = 0;
int countR = 0;
int countL = 0;
byte heading = 0;
int cursor = 0;
int gearDownN = 0;
int onN = HIGH;
int gearDownR = 0;
int onR = HIGH;
int gearDownL = 0;
int onL = HIGH;

int lever = 0;
int minIncrement = 10;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);

  lcd.clear(); 
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  lcd.setCursor(0, 0); // set cursor to first row
  lcd.print("Init done"); // print to lcd
 
}

void loop() {
    delay(10);
    if (Serial.available() > 0) {    
      byte incomingByte = 0;
      //      incomingByte = Serial.read(); // read the incoming byte:
      //      
      //      //if (incomingByte != -1 && heading != incomingByte) { // -1 means no data is available
      //        heading = incomingByte;
      //        lcd.setCursor(0, 0); // set cursor to first row
      //        lcd.print("Heading: "); // print out to LCD
      //        if(incomingByte == 35){
      //          cursor = 0;          
      //        }else{
      //          lcd.setCursor(cursor, 1); // set cursor to secon row
      //          lcd.print((char)incomingByte); // print out the retrieved value to the second row
      //          cursor++;
      //        }
      lcd.clear(); 
      int row = 0;
      for(int i=1; i<=6; i++) {
        String incomingString = Serial.readStringUntil(35);
        //String value1 = strtok(incomingString, "&");
        if(i<3){
          lcd.setCursor(0, row); // set cursor to row
          lcd.print(incomingString);
          row++;
        }else if(i<4){
          lcd.setCursor(13, row); // set cursor to row
          lcd.print(incomingString);          
        }else if(i<5){
          if(incomingString == "On"){
              gearDownN = 1;
          } else if(incomingString == "Off"){
              gearDownN = 0;
          } else if(incomingString == "Moving"){
              gearDownN = -1;
          }
        }else if(i<6){
          if(incomingString == "On"){
              gearDownR = 1;
          } else if(incomingString == "Off"){
              gearDownR = 0;
          } else if(incomingString == "Moving"){
              gearDownR = -1;
          }
        } else {
          if(incomingString == "On"){
              gearDownL = 1;
          } else if(incomingString == "Off"){
              gearDownL = 0;
          } else if(incomingString == "Moving"){
              gearDownL = -1;
          }
        }
      }
    } else {
       //Do nothing 
    }
    //Serial.println(gearDown);
    //Nose wheel
    if(gearDownN == 1) {
        countN = 0;
        digitalWrite(7,LOW);
     } else if(gearDownN == 0) {
        countN = 0;
        digitalWrite(7,HIGH);
     } else if(gearDownN == -1){
        countN++;
        //Serial.print(count);
        if(countN > 50 ){
           onN = HIGH;    
        } else {
           onN = LOW;
        }
        if (countN > 100){
          countN = 0;
        }
        digitalWrite(7,onN);
     }
    //Right wheel
    if(gearDownR == 1) {
        countR = 0;
        digitalWrite(8,LOW);
     } else if(gearDownR == 0) {
        countR = 0;
        digitalWrite(8,HIGH);
     } else if(gearDownR == -1){
        countR++;
        //Serial.print(count);
        if(countR > 50 ){
           onR = HIGH;    
        } else {
           onR = LOW;
        }
        if (countR > 100){
          countR = 0;
        }
        digitalWrite(8,onR);
     }
    //Left wheel
    if(gearDownL == 1) {
        countL = 0;
        digitalWrite(9,LOW);
     } else if(gearDownL == 0) {
        countL = 0;
        digitalWrite(9,HIGH);
     } else if(gearDownL == -1){
        countL++;
        //Serial.print(count);
        if(countL > 50 ){
           onL = HIGH;    
        } else {
           onL = LOW;
        }
        if (countL > 100){
          countL = 0;
        }
        digitalWrite(9,onL);
     }
        //int test = analogRead(A0);
        //if (abs(lever - test) < minIncrement){
        //if (test == lever){
          //No change, do nothing
        //} else {
        //  test = test / minIncrement;
        //  test = test * minIncrement;
        //  lever = test;
          //Serial.println(lever);
        //}
      //Serial.print(10);     
    
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //if(!digitalRead(7) == 1){
    //  lcd.print("Button pressed");
    //   count = 0;
    //}else{
    //    count ++;
    //lcd.print("              ");
    //    lcd.setCursor(0, 1);
    //    lcd.print(count);
  //}
}
