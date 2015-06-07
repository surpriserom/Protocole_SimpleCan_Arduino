// demo: CAN-BUS Shield, receive data with check mode
// send data coming to fast, such as less than 10ms, you can use this way
// loovee, 2014-6-13


#include <SPI.h>
#include "mcp_can.h"


// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;

const int led = 13;
boolean state = false;

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
    Serial1.begin(9600);
    
      while (!Serial1) {
        ; // wait for Serial1 port to connect. Needed for Leonardo only
      }
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
    char buf[80];
    static unsigned long time = 0;
    unsigned long time2 = 0;
    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        CAN.readMsgBuf(&len,(unsigned char *) buf);    // read data,  len: data length, buf: data buf

        unsigned char canId = CAN.getCanId();
        
        Serial1.print("get data from ID: ");
        Serial1.println(canId);
        buf[len] = '\0';
        Serial1.println(buf);
    }
    
    time2 = millis();
    if(time2 > time )
    {
      state = !state;
      digitalWrite(led, (state ? HIGH : LOW));
      time = time + (state ? 500 : 1000);
    }
    
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/


