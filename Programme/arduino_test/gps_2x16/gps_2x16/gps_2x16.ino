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

SoftwareSerial gpsSerial(10, 11); // RX, TX (TX not used)
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
     displayGPS();
    }
  }
  
}


/**
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
  char field[20][20];
  getFieldName(field[0]);
  if (strcmp(field[0], "$GPRMC") == 0)
  {
    parseField(field);
    (strcmp(field[2], "A") == 0?  HIGH : LOW));
    
    //prmeiere ligne
    lcd.setCursor(0, 0);
    lcd.print();
    Serial.print(field);
    getField(field, 4); // N/S
    Serial.print(field);
    lcd.setCursor(0, 1);
    lcd.print();
  }
}

void parseField(char** buffer)
{
  int sentencePos = 0;
  int fieldPos = 0;
  while (sentencePos < sentenceSize)
  {
    buffer[sentencePos][fieldPos] = sentence[fieldPos];
    if (sentence[fieldPos] == ',')
    {
      buffer[sentencePos][fieldPos] = '\0';
      sentencePos ++;
    }
    fieldPos ++;
  }
}

void getFieldName(char* buffer)
{
  int fieldPos = 0;
  boolean endField = false;
  while (sentencePos < sentenceSize || !endField)
  {
    endField = (sentence[fieldPos] == ',');
    buffer[fieldPos] = sentence[fieldPos];
    fieldPos ++;
  }
  buffer[fieldPos] = '\0';
}
