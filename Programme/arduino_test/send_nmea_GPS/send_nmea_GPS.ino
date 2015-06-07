#include "mcp_can.h"
#include <SPI.h>
#include "gps_parser.h"

// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;
const int led = 13;
boolean state = false;

const INT32U nodeID = 0x01;

const int sentenceSize = 80;
GPS_PARSER parser(true);

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

unsigned char sentence[sentenceSize];
void loop()
{
    static unsigned long time = 0;
    unsigned long time2 = 0;
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
       if(parser.isGPRMC((char *) sentence))
       {
         if(i < 28)
         {
         // send data:  id node, extended frame, data len = i max 29, stmp: data buf
          CAN.sendMsgBuf(nodeID, 0, i, sentence);
         }
         else
         { //si la chaine est trop grande nous allons la decouper en secance de 28 charactere
           int cpt = 0;
           unsigned char buff[29];
           while( cpt < i)
           {
             buff[cpt%8] = sentence[cpt];
             cpt++;
             if(cpt%8 == 0)
             {
               CAN.sendMsgBuf(nodeID, 0, 8, buff);
             }
           }
           CAN.sendMsgBuf(nodeID, 0, (cpt%8), buff);
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
    
    //on verifie les message toute les 100ms pour eviter de saturer le bus
    //delay(100); 
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
