//fonction pour decouper les messages CAN
//basée sur le code de http://savvymicrocontrollersolutions.com/arduino.php?article=adafruit-ultimate-gps-shield-seeedstudio-can-bus-shield
//un int est stocke pour la leonardo sur 16octets
//un float est stocke sur 32 octets

#include "parseCan.h"

ParseCan::ParseCan(bool val)
{
  init = val;
}

//convertie 2 char d'un tableau en entier
int ParseCan::ucharToInt(unsigned char buff[], int offset)
{
	int nb = ((int) buff[offset] << 8) + buff[offset+1];
	return nb;
}

//convertie 4 char d'un tableau en float
float ParseCan::ucharToFloat(unsigned char buff[], int offset)
{
    union {
      float a;
      unsigned char bytes[4];
    } thing;
    for(int i = 0; i< 4; i++)
    {
      thing.bytes[i] = buff[offset+i];
    }
    return thing.a;
}

//stocke les 2 octets d'un int dans 2 case d'un tableau à partire de offset
void ParseCan::intToUChar(unsigned char buff[], int offset, int val)
{
	buff[offset] = (val >> 8) & 0xff;
	buff[offset+1] = val & 0xff;
}

//stocke les 4 octets d'un float dans 4 case d'un tableaux
void ParseCan::floatToUChar(unsigned char buff[], int offset, float val)
{
  union {
    float a;
    unsigned char bytes[4];
  } thing;
  thing.a = val;
  for(int i = 0; i< 4; i++)
  {
    buff[offset+i] = thing.bytes[i];
  }
}
