/*
*  Serial: 0 (RX) and 1 (TX). 
* Used to receive (RX) and transmit (TX) TTL serial data using the ATmega32U4 hardware serial capability.
* Note that on the Leonardo, the Serial class refers to USB (CDC) communication; 
* for TTL serial on pins 0 and 1, use the Serial1 class. 
*
* wirred pin D0 -> rx
* not pluged pin D1 -> TX
*/

#include <Can.h>

const int sentenceSize = 80;
char sentence[sentenceSize];

const uint8_t can_filter[] = 
{
	// Group 0
	MCP2515_FILTER(0),				// Filter 0
	MCP2515_FILTER(0),				// Filter 1
	
	// Group 1
	MCP2515_FILTER_EXTENDED(0),		// Filter 2
	MCP2515_FILTER_EXTENDED(0),		// Filter 3
	MCP2515_FILTER_EXTENDED(0),		// Filter 4
	MCP2515_FILTER_EXTENDED(0),		// Filter 5
	
	MCP2515_FILTER(0),				// Mask 0 (for group 0)
	MCP2515_FILTER_EXTENDED(0),		// Mask 1 (for group 1)
};

void setup() {
  Serial1.begin(9600);
      while (!Serial1) {
        ; // wait for Serial1 port to connect. Needed for Leonardo only
      }
      
      // Initialize MCP2515
      CAN.mcp2515_init(BITRATE_250_KBPS);
      CAN.activateInterrupt();
      // Load filters and masks
      //can.mcp2515_static_filter(can_filter);
      CAN.resetFiltersAndMasks();
}

void loop() {
  static int i = 0;
  if (Serial1.available()>0)
  {
    char ch = Serial1.read();
    if (ch != '\n' && i < sentenceSize)
    {
      sentence[i] = ch;
      i++;
    }
    else
    {
     sentence[i] = '\0';
     i = 0;
     displayGPS();
    }
  }
}

/*
* $GPRMC,225446,A,4916.45,N,12311.12,W,000.5,054.7,191194,020.3,E*68
field Name -> 0 -> $GPRMC
field Heure Fixe -> 1 -> 225446 -> 22H 54mn 46s
field gps signal valide -> 2 -> A -> A = ok | V = Warning
field Latitude -> 3 -> 4916.45 -> 49 deg. 16.45 min
field -> 4 -> N -> N = north
field lognitude -> 5 -> 12311.12 -> 123 deg. 11.12 min
field -> 6 -> W -> W = west
field vitesse -> 7 -> 000.5 -> 000.5 = vitesse sol, Knots
field cap -> 8 -> 054.7 -> cap (vrai)
field date fixe -> 9 -> 191194 -> Date du fix 19 Novembre 1994
field -> 10 -> 020.3 -> Déclinaison Magnetique 20.3 deg Est
field cheksum -> 11 -> E*68 -> cheksum 68
*/
void displayGPS()
{
  char field[20];
  char buff[50];
  boolean signal = false;
   can_t message;
  
  getField(field, 0);
  if (strcmp(field, "$GPRMC") == 0)
  {
    //test if gps signal is good
	getField(field, 2);
    signal = (strcmp(field, "A") == 0?  true : false);
    
    
    if(signal)
    {
      //premeiere ligne
	  getField(field, 3);
	  strcat(buff, "lat:  ");
	   strcat(buff, field[0]+"");
	   strcat(buff, field[1]+"");
	   strcat(buff, "deg  ");
	   strcat(buff, field +2);
	   strcat(buff, "min ");
	  getField(field, 4);
	   strcat(buff, field);
      //envoi latitude sur bus can
	  CAN.printString2Can(buff);
      //seconde ligne
	  getField(field, 5);
	  strcat(buff, "long: ");
	  strcat(buff, field[0]+"");
	  strcat(buff, field[1]+"");
	  strcat(buff, field[2]+"");
	  strcat(buff, "deg ");
	  strcat(buff, field +3);
	  strcat(buff, "min ");
	  getField(field, 6);
	  strcat(buff, field);
      //envoi longitude sur bus can
	  CAN.printString2Can(buff);
     }
     else
     {
       CAN.printString2Can("signal GPS non valide");
     }
  }
}

void getField(char* buffer, int index)
{
  int sentencePos = 0;
  int fieldPos = 0;
  int commaCount = 0;
  while (sentencePos < sentenceSize)
  {
    if (sentence[sentencePos] == ',')
    {
      commaCount ++;
      sentencePos ++;
    }
    if (commaCount == index)
    {
      buffer[fieldPos] = sentence[sentencePos];
      fieldPos ++;
    }
    sentencePos ++;
  }
  buffer[fieldPos] = '\0';
}
