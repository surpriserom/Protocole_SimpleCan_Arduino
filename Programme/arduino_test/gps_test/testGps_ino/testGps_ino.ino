/*------------------------------------------------------+
|            Code for testing GPS receiver              |
|  Receiver type Cirus CN-06                            |
| Gps module  ublox Neo-6m-0-001                        |
+-------------------------------------------------------*/
#include <SoftwareSerial.h>

SoftwareSerial gpsSerial(10, 11); // RX, TX (TX not used)
const int sentenceSize = 80;

char sentence[sentenceSize];

void setup()
{
  Serial.begin(9600);
  gpsSerial.begin(9600);
}

void loop()
{
  static bool first = true;
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
  if(first)
  {
    Serial.println("Gps Test started\n"); 
    first = false;
  }
  
}

void displayGPS()
{
  char field[20];
  getField(field, 0);
  if (strcmp(field, "$GPRMC") == 0)
  {
    Serial.print("Nav:");
    getField(field, 2);  // number
    Serial.print((strcmp(field, "A") == 0? "Valide" : "Erronne"));
    Serial.print(" | Lat: ");
    getField(field, 3);  // number
    Serial.print(field);
    getField(field, 4); // N/S
    Serial.print(field);
    
    Serial.print(" Long: ");
    getField(field, 5);  // number
    Serial.print(field);
    getField(field, 6);  // E/W
    Serial.println(field);
  }
  else
  {
    if (strcmp(field, "$GPGGA") == 0)
    {
      getField(field, 1);//h
      Serial.print(field[0]);
      Serial.print(field[1]);
      Serial.print("h ");
      //getField(field, 1);  // mn
      Serial.print(field[2]);
      Serial.print(field[3]);
      Serial.print("mn ");
      //getField(field, 1);  // s
      Serial.print(field[4]);
      Serial.print(field[5]);
      Serial.println("s ");
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


