/* CAN communications example

  Topic: Receive Messages using read(ID, length, data) function
  Authors: Pedro Cevallos & Neil McNeight
  Created: 05/07/14
  Updated: 06/18/14

  Example shows how to receive messages using CAN
  This example uses Serial1 Monitor to display received messages

  As per wiki information:
  "CAN bus is a message-based protocol, designed specifically for automotive
  applications but now also used in other areas such as aerospace, maritime,
  industrial automation and medical equipment."

  For more info http://en.wikipedia.org/wiki/Controller_area_network

 */

#include <Arduino.h>
#include "Can.h"

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

void StreamPrint_progmem(Print &out,PGM_P format,...)
{
  // program memory version of printf - copy of format string and result share a buffer
  // so as to avoid too much memory use
  char formatString[128], *ptr;
  strncpy_P( formatString, format, sizeof(formatString) ); // copy in from program mem
  // null terminate - leave last char since we might need it in worst case for result's \0
  formatString[ sizeof(formatString)-2 ]='\0'; 
  ptr=&formatString[ strlen(formatString)+1 ]; // our result buffer...
  va_list args;
  va_start (args,format);
  vsnprintf(ptr, sizeof(formatString)-1-strlen(formatString), formatString, args );
  va_end (args);
  formatString[ sizeof(formatString)-1 ]='\0'; 
  out.print(ptr);
}
 
#define Serial1print(format, ...) StreamPrint_progmem(Serial1,PSTR(format),##__VA_ARGS__)
#define Streamprint(stream,format, ...) StreamPrint_progmem(stream,PSTR(format),##__VA_ARGS__)


void term_put_hex(const uint8_t val)
{
  uint8_t tmp = val >> 4;
  
  if (tmp > 9)
    tmp += 'A' - 10;
  else 
    tmp += '0';
  Serial1.write(tmp);
  
  tmp = val & 0x0f;
  
  if (tmp > 9) 
    tmp += 'A' - 10;
  else 
    tmp += '0';
  Serial1.write(tmp);
}

void setup()
{
  Serial1.begin(9600);  // Initialize Serial1 communications with computer to use Serial1 monitor

      while (!Serial1) {
        ; // wait for Serial1 port to connect. Needed for Leonardo only
      }
      
      delay(3000);  // Delay added just so we can have time to open up Serial1 Monitor and CAN bus monitor. It can be removed later...
      
      Serial1.println("Receiver on");
      
      // Initialize MCP2515
      CAN.mcp2515_init(BITRATE_250_KBPS);
      CAN.activateInterrupt();
      // Load filters and masks
      //can.mcp2515_static_filter(can_filter);
      CAN.resetFiltersAndMasks();
}

// Finally arduino loop to execute above function with a 50ms delay
void loop()
{
  static char buffer[40];
    static uint8_t pos; 
    can_t message;
    
    //Get the bootloader response if any
    if (CAN.mcp2515_get_message(&message))
    {
      uint8_t length = message.length;
      
      //Case of a remote frame			
      if (message.flags.rtr)
      {
        // print identifier if extended ID
        if (message.flags.extended) 
        {
          Serial1.print("R%081x",message.id);
        } 
        else  // print identifier
        {
          uint16_t id = message.id;
          Serial1.print("r%03x",id);
        }
        Serial1.write(length + '0');
      }
      else     //Case of a data frame			
      {
        // print identifier if extended ID
        if (message.flags.extended) 
        {
          Serial1.print("T%081x",message.id);
        } 
        else // print identifier
        {
          uint16_t id = message.id;
          Serial1.print("t%03x",id);
        }
        Serial1.write(length + '0');
      				
        // print data
        for (uint8_t i = 0; i < length; i++)
          term_put_hex(message.data[i]);
        }
          
      Serial1.write('\r');
    }
}
