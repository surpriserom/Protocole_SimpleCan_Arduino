 /*
 LCD 2x16 wirring
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 GPS wirring
 * rx -> 10
 * tx -> 9
 
 LED valide
 * led gps valide -> 7
 */
 
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

SoftwareSerial gpsSerial(9, 10); // RX, TX (TX not used)
const int sentenceSize = 80;
const int backlight = 7;

char sentence[sentenceSize];

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
  // Print a message to the LCD.
  lcd.print("hello, world!");
  
  //set the gps signal led
  pinMode(backlight, OUTPUT);
  digitalWrite(backlight, LOW);
  
  gpsSerial.begin(9600);
  //Serial.begin(9600);
}

void loop() 
{
  static int i = 0;
  if (gpsSerial.available()>0)
  {
    char ch = gpsSerial.read();
    if (ch != '\n' && i < sentenceSize)
    {
      sentence[i] = ch;
      i++;
    }
    else
    {
     sentence[i] = '\0';
     i = 0;
     //Serial.println(sentence);
     displayGPS();
    }
  }
  
}


/*
* $GPRMC,225446,A,4916.45,N,12311.12,W,000.5,054.7,191194,020.3,E*68
field Name -> 0 -> $GPRMC
field Heure Fixe -> 1 -> 225446 -> 22H 54mn 46s
field gps signal valide -> 2 -> A -> A = ok | V = Warning
field Latitude -> 3 -> 4916.45 -> 49 deg. 16.45 min
field -> 4 -> N -> N = north
field lognitude -> 5 -> 12311.12 -> 123 deg. 11.12 min
field -> 6 -> W -> W = west
field vitesse -> 7 -> 000.5 -> 000.5 = vitesse sol, Knots
field cap -> 8 -> 054.7 -> cap (vrai)
field date fixe -> 9 -> 191194 -> Date du fix 19 Novembre 1994
field -> 10 -> 020.3 -> Déclinaison Magnetique 20.3 deg Est
field cheksum -> 11 -> E*68 -> cheksum 68
*/
void displayGPS()
{
  char field[20];
  boolean signal = false;
  static boolean prev= false;
   getField(field, 0);
  if (strcmp(field, "$GPRMC") == 0)
  {
    //test if gps signal is good
	getField(field, 2);
    signal = (strcmp(field, "A") == 0?  true : false);
    
    if(prev != signal)
    {
      lcd.clear();  
    }
    prev = signal;
    
    if(signal)
    {
      digitalWrite(backlight, HIGH);
      //premeiere ligne
      lcd.setCursor(0, 0);
	  getField(field, 3);
	  lcd.print(field[0]);
	  lcd.print(field[1]);
	  lcd.print("  ");
	  lcd.print(field +2);
	  lcd.print("mn ");
	  getField(field, 4);
	  lcd.print(field);
      //seconde ligne
      lcd.setCursor(0, 1);
	  getField(field, 5);
	  lcd.print(field[0]);
	  lcd.print(field[1]);
	  lcd.print(field[2]);
	  lcd.print(" ");
	  lcd.print(field +3);
	  lcd.print("mn ");
	  getField(field, 6);
	  lcd.print(field);
     }
     else
     {
       lcd.setCursor(0, 0);
       lcd.print("signal GPS non");
       lcd.setCursor(0, 1);
       lcd.print("valide");
       digitalWrite(backlight, LOW);
       delay(200);
       digitalWrite(backlight, HIGH);
       delay(100);
     }
  }
}

void getField(char* buffer, int index)
{
  int sentencePos = 0;
  int fieldPos = 0;
  int commaCount = 0;
  while (sentencePos < sentenceSize)
  {
    if (sentence[sentencePos] == ',')
    {
      commaCount ++;
      sentencePos ++;
    }
    if (commaCount == index)
    {
      buffer[fieldPos] = sentence[sentencePos];
      fieldPos ++;
    }
    sentencePos ++;
  }
  buffer[fieldPos] = '\0';
}
