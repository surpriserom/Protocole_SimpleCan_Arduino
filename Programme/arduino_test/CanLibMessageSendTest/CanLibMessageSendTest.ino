/* CAN communications example

  Topic: Send messages using write(ID, frameType, length, data) function
  Authors: Pedro Cevallos & Neil McNeight
  Created: 05/07/14
  Updated: 06/18/14

  Example shows how to send messages using CAN
  This example uses Serial Monitor to display received messages.

  As per wiki information:
  "CAN bus is a message-based protocol, designed specifically for automotive
  applications but now also used in other areas such as aerospace, maritime,
  industrial automation and medical equipment."

  For more info http://en.wikipedia.org/wiki/Controller_area_network

 */

#include <Arduino.h>
#include "CAN.h"

#if defined(ARDUINO_ARCH_AVR) // Arduino with SPI interface to MCP2515 chip
#include <SPI.h>
#include "CAN_MCP2515.h"
#elif defined(ARDUINO_ARCH_SAM) // Arduino Due
#include <CAN_SAM3X.h>
#elif defined(__MK20DX256__) // Teensy 3.1
#include <CAN_K2X.h>
#else
#error "Your CAN controller is currently unsupported."
#endif

// Define our CAN speed (bitrate).
#define bitrate CAN_BPS_500K

const int sentenceSize = 80;
unsigned char sentence[sentenceSize];
const int led = 13;
boolean led_state = false;

void setup()
{
  Serial1.begin(9600); // Initialize Serial communications with computer to use serial monitor
  
  while (!Serial1) {
     ; // wait for Serial1 port to connect. Needed for Leonardo only
  }
      
  pinMode(led, OUTPUT);//used to check  if programme is ON
  digitalWrite(led, HIGH);

  //Set CAN speed. Note: Speed is now 500kbit/s so adjust your CAN monitor
  
  CAN.begin(bitrate);
}

void writeStandardMessage()
{
  unsigned long ID = 0x555; // Random Standard Message ID
  byte length = 8; // Data length
  unsigned char buff[8];
  int i=0;
  int j = 0;
  uint32_t timehack = millis();
  while(i < sentenceSize || sentence[i] != '\0')
  {
    i++;
    buff[j] = sentence[i];
    j++;
    if(j == 8)
    {
      j=0;
      CAN.write(ID, CAN_STANDARD_FRAME, length, buff); // Load message and send
    }
  }
  if(j != 0)
  {
    CAN.write(ID, CAN_STANDARD_FRAME, j, buff); // Load message and send
  }
}

// Finally arduino loop to execute above functions with a 250ms delay
void loop()
{
  static int i = 0;
  static unsigned int led_timer = 0;
  
  if(Serial1.available() > 0)
  {
      unsigned ch = Serial1.read();
      if(ch != '\n' && i < sentenceSize)
      {
        sentence[i] = ch;
        i++;
      }
      else
      {
        sentence[i] = '\0';
        i = 0;
        writeStandardMessage();
      }
  }
  
  
  if(led_timer >= 5000 && led_state)
  {
    led_state= false;
    led_timer = 0;
    digitalWrite(led, LOW);
   }
   else
   {
     if(led_timer >= 10000 && !led_state)
     {
        led_state= true;
        led_timer = 0;
        digitalWrite(led, HIGH);
     }
     else
     {
       led_timer++;
     }
   }
}
