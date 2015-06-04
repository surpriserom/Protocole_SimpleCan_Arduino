// demo: CAN-BUS Shield, send data
#include "mcp_can.h"
#include <SPI.h>

// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;
const int led = 13;
boolean state = false;

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
    //Serial.begin(9600);
    
  //set the gps signal led
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  
START_INIT:

    if(CAN_OK == CAN.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
    {
       // Serial.println("CAN BUS Shield init ok!");
        digitalWrite(led, HIGH);
    }
    else
    {
        //Serial.println("CAN BUS Shield init fail");
        //Serial.println("Init CAN BUS Shield again");
        state = !state;
        digitalWrite(led, (state ? HIGH : LOW));
        delay(100);
        goto START_INIT;
    }
}

unsigned char stmp[8] = {0, 1, 2, 3, 4, 5, 6, 7};
void loop()
{
    // send data:  id = 0x00, standrad frame, data len = 8, stmp: data buf
    CAN.sendMsgBuf(0x00, 0, 8, stmp);
    
    state = !state;
    digitalWrite(led, (state ? HIGH : LOW));
    delay(250);                       // send data per 250ms
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
