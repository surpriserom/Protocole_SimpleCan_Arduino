//fonction pour decouper les messages CAN
//basée sur le code de http://savvymicrocontrollersolutions.com/arduino.php?article=adafruit-ultimate-gps-shield-seeedstudio-can-bus-shield

#include "parseCan.h"

//convertie 2 caractere d'un tableau en entier
int ucharToInt(unsigned char *buff, int offset)
{
	int nb = (buff[offset] << 8) & 0xffff + (buff[offset+1] & 0xffff);
	return nb;
}
float ucharToFloat(unsigned char *buff, int offset);

void intToUChar(unsigned char *buff, int offset, int val);
void foatToUChar(unsigned char *buff, int offset, float val); 