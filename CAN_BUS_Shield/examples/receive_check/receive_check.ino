// demo: CAN-BUS Shield, receive data with check mode
// send data coming to fast, such as less than 10ms, you can use this way
// loovee, 2014-6-13


#include <SPI.h>
#include "mcp_can.h"


// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;

const int led = 13;

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
    Serial1.begin(9600);
    
  //set the gps signal led
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

START_INIT:

    if(CAN_OK == CAN.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
    {
        Serial1.println("CAN BUS Shield init ok!");
    }
    else
    {
        Serial1.println("CAN BUS Shield init fail");
        Serial1.println("Init CAN BUS Shield again");
        delay(100);
        goto START_INIT;
    }
}


void loop()
{
    unsigned char len = 0;
    unsigned char buf[8];
    unsigned long time = 0;

    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        unsigned char canId = CAN.getCanId();
        
        Serial1.println("-----------------------------");
        Serial1.println("get data from ID: ");
        Serial1.println(canId);

        for(int i = 0; i<len; i++)    // print the data
        {
            Serial1.print(buf[i]);
            Serial1.print("\t");
        }
        Serial1.println();
    }
    
    if(time < millis())
    {
      digitalWrite(led, digitalRead(led)^1);
      time += 500;
    }
    
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/


