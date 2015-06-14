/*------------------------------------------------------+
|            Code for float and int parsing             |
+-------------------------------------------------------*/
#include <ParseCan.h>

//led pour voir si le programme tourne
const int led = 13;
boolean test = false;

ParseCan parserCan(true);

void setup()
{
	//port serie usb
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for Serial port to connect. Needed for Leonardo only
   }
  
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  
  Serial.println("CanTest started\n");
}

void loop()
{
  	float nb1 = 25.24;
    int nb2 = 245;
    unsigned char buff[6];
    Serial.println(nb1);
    Serial.println(nb2);
    parserCan.intToUChar(buff,0,nb2);
    parserCan.floatToUChar(buff,2,nb1);
    Serial.print(buff[0], HEX);
    Serial.print(' ');
    Serial.print(buff[1], HEX);
    Serial.print(' ');
    Serial.print(buff[2], HEX);
    Serial.print(' ');
    Serial.print(buff[3], HEX);
    Serial.print(' ');
    Serial.print(buff[4], HEX);
    Serial.print(' ');
    Serial.println(buff[4], HEX);
    Serial.println(parserCan.ucharToFloat(buff,2));
    Serial.println(parserCan.ucharToInt(buff,0));
}