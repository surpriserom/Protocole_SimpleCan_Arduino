/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

#define ECHOPIN A0        // Pin to receive echo pulse
#define TRIGPIN A1        // Pin to send trigger pulse
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 4,5,6,7);
const int bouton = 2;
const int bouton2 = 3;
const int backlight = 10;
boolean state = true;
int buttonState = 0;
int buttonStateOld = LOW;
int buttonState2 = LOW;
int buttonStateOld2 = LOW;
int oldS = 1;
int time = 0;
int hMnS[3];

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  pinMode(backlight, OUTPUT);
  pinMode(bouton, INPUT); 
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
  digitalWrite(backlight, HIGH);   
  
  Serial.begin(9600);
  Serial.println("Hello World");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  time = millis()/1000;
  hMnS[0]=time/3600;
  hMnS[1]=(time%3600)/60;
  hMnS[2]=(time%3600)%60;
  if(oldS != hMnS[2]){
    if(hMnS[0]<10){
      lcd.print("0");
    }
    lcd.print(hMnS[0]);
    lcd.print("h :");
    if(hMnS[1]<10){
      lcd.print("0");
    }
    lcd.print(hMnS[1]);
    lcd.print("mn :");
    if(hMnS[2]<10){
      lcd.print("0");
    }
    lcd.print(hMnS[2]);
    lcd.print("s");
    oldS = hMnS[2];
    Serial.print(hMnS[0]);
    Serial.print("H ");
    Serial.print(hMnS[1]);
    Serial.print("mn ");
    Serial.print(hMnS[2]);
    Serial.println("S");
  }
  
  buttonState=digitalRead(bouton);
  if(buttonState == HIGH && buttonStateOld == LOW){
   if(state){
        state = false;
        digitalWrite(backlight, LOW); 
    }
    else{
        state = true;
        digitalWrite(backlight, HIGH); 
    }
  }
  buttonStateOld=buttonState;
  
 
  buttonState2=digitalRead(bouton2);
  if(buttonState2 == HIGH && buttonStateOld2 == LOW){
    digitalWrite(TRIGPIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW);
    float distance = pulseIn(ECHOPIN, HIGH)/58;
    Serial.print("distance : ");
    Serial.println(distance);
    lcd.setCursor(0, 0);
    lcd.print("distance :     ");
    lcd.setCursor(11, 0);
    lcd.print(distance);
  } 
  buttonStateOld2=buttonState2;
}

