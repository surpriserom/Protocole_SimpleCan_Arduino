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
    Serial1.begin(115200);
    
      while (!Serial1) {
        ; // wait for Serial1 port to connect. Needed for Leonardo only
      }
      
  //set the test led
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
    static unsigned long time = 0;
    volatile unsigned long time2 = millis();
    
    unsigned char len = 0;
    unsigned char buf[8];
	
    if(time2 > time )
    {
      //creer un clignotement asynchrone pour avoir une information visuel de debogage
      state = !state;
      digitalWrite(led, (state ? HIGH : LOW));
      time = time + (state ? 500 : 1000);
    }	
	
    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        CAN.readMsgBuf(&len,(unsigned char *) buf);    // read data,  len: data length, buf: data buf

        unsigned char canId = CAN.getCanId();
		float nb1 = 0.0;
		int nb2 = 0;
        
        switch(canId)
        {
          case MSG_test :
				nb1 = parser.ucharToFloat(buf,2);
				nb2 = parser.ucharToInt(buf,0);Serial1.println("-----------------------------");
				Serial1.println("get data from ID: ");
				Serial1.print(canId);
				Serial1.println("  | MSG_test");
				Serial1.print(" nb1 :");
				Serial1.println(nb1);
				Serial1.print(" nb2 :");
				Serial1.println(nb2);
            break;
            default:
				Serial1.println("-----------------------------");
				Serial1.println("get data from ID: ");
				Serial1.println(canId);

				for(int i = 0; i<len; i++)    // print the data
				{
					Serial1.print(buf[i]);
					Serial1.print("\t");
				}
				Serial1.println();
            break;
        }
    }   
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
