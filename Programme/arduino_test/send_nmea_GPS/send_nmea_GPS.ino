// demo: CAN-BUS Shield, send data
#include "mcp_can.h"
#include "gps_data_parser.h"
#include <SPI.h>

// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;

const int led = 13;
boolean state = false;

const int nodeID = 1;
const int sentenceSize = 80;
GPS_PARSER parser(true);

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
    Serial1.begin(9600);
    Serial.begin(9600);
    
    while (!Serial1) {
        ; // wait for Serial1 port to connect. Needed for Leonardo only
    }
    while (!Serial) {
        ; // wait for Serial1 port to connect. Needed for Leonardo only
    }
    
  //set the gps signal led
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  
START_INIT:

    if(CAN_OK == CAN.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
    {
        //Serial.println("CAN BUS Shield init ok!");
        digitalWrite(led, HIGH);
    }
    else
    {
        //Serial.println("CAN BUS Shield init fail");
        //Serial.println("Init CAN BUS Shield again");
        state = !state;
        digitalWrite(led, (state ? HIGH : LOW));
        delay(150);
        goto START_INIT;
    }
}

unsigned char buff[80];
void loop()
{
    static unsigned long time = 0;
    unsigned long time2 = 0;
    static unsigned char sentence[sentenceSize];
    static int i = 0;
    
    if (Serial1.available()>0)
    {
      unsigned char ch = Serial1.read();
      if (ch != '\n' && i < sentenceSize)
      {
        sentence[i] = ch;
        i++;
      }
      else
      {
       sentence[i] = '\0';
       if(parser.isGPRMC(sentence))
       {
         if(i < 28)
         {
         // send data:  id node, extended frame, data len = i max 29, stmp: data buf
          CAN.sendMsgBuf(nodeID, 1, i, sentence);
         }
         else
         { //si la chaine est trop grande nous allons la decouper en secance de 28 charactere
           int cpt = 0;
           unsigned char buff[29];
           while( cpt < i)
           {
             buff[cpt%28] = sentence[cpt];
             cpt++;
             if(cpt%28 == 0)
             {
               CAN.sendMsgBuf(nodeID, 1, 28, buff);
             }
           }
           CAN.sendMsgBuf(nodeID, 1, (cpt%28), buff);
         }
       }
       i = 0;
      }
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
