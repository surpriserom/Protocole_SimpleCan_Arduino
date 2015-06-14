//base sur la demo du shield pour la reception
//recupere les message sur le bus et compare les identifiants
//affiche les message des identifiant decoder et leur valeur

#include <mcp_can.h>
#include <SPI.h>

#include <ParseCan.h>

const int SPI_CS_PIN = 9;
const int led = 13;
boolean state = false;

ParseCan parser(true);

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{ 
  //set the test led
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

START_INIT:

    if(CAN_OK == CAN.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
    {
    }
    else
    {
        delay(100);
        goto START_INIT;
    }
}

void loop()
{
    char buf[8];
	
  	float nb1 = 25.24;
    int nb2 = 245;
    unsigned char buff[8];
	
	unsigned char stmp[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	
    parser.intToUChar(buff,0,nb2);
    parser.floatToUChar(buff,2,nb1);
	
    CAN.sendMsgBuf(MSG_test, 0, 8, buff);
	delay(500);
	
    //creer un clignotement asynchrone pour avoir une information visuel de debogage
    state = !state;
    digitalWrite(led, (state ? HIGH : LOW));
	  
    CAN.sendMsgBuf(0x25, 0, 8, stmp);
	delay(250);
	
    //creer un clignotement asynchrone pour avoir une information visuel de debogage
    state = !state;
    digitalWrite(led, (state ? HIGH : LOW));    
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
