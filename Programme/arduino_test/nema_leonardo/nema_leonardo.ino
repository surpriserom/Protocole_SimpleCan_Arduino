/*
* wirred pin D0 -> rx
* not pluged pin D1 -> TX
*/
#include <SoftwareSerial.h>

SoftwareSerial nemaSerial(9, 10);

const int sentenceSize = 80;
char sentence[sentenceSize];

void setup() {
  nemaSerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  static int i = 0;
  if (nemaSerial.available()>0)
  {
    char ch = nemaSerial.read();
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
  
  getField(field, 0);
  if (strcmp(field, "$GPRMC") == 0)
  {
    //test if gps signal is good
	getField(field, 2);
    signal = (strcmp(field, "A") == 0?  true : false);
    
    
    if(signal)
    {
      //premeiere ligne
	  getField(field, 3);
	  Serial.print("lat:  ");
	  Serial.print(field[0]);
	  Serial.print(field[1]);
	  Serial.print("deg  ");
	  Serial.print(field +2);
	  Serial.print("min ");
	  getField(field, 4);
	  Serial.println(field);
      //seconde ligne
	  getField(field, 5);
	  Serial.print("long: ");
	  Serial.print(field[0]);
	  Serial.print(field[1]);
	  Serial.print(field[2]);
	  Serial.print("deg ");
	  Serial.print(field +3);
	  Serial.print("min ");
	  getField(field, 6);
	  Serial.println(field);
     }
     else
     {
       Serial.println("signal GPS non valide");
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
