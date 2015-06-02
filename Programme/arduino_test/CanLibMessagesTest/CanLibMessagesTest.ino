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

void setup()
{
  Serial1.begin(115200);  // Initialize Serial1 communications with computer to use Serial1 monitor

  //Set CAN speed. Note: Speed is now 500kbit/s so adjust your CAN monitor

  CAN.begin(bitrate);

  //delay(4000);  // Delay added just so we can have time to open up Serial1 Monitor and CAN bus monitor. It can be removed later...

  // Output will be formatted as a CSV file, for capture and analysis
  Serial1.println(F("millis(),ID,Length,Data0,Data1,Data2,Data3,Data4,Data5,Data6,Data7"));
}


// Create a function to read message and display it through Serial1 Monitor
void readMessage()
{
  unsigned long can_ID; // assign a variable for Message ID
  byte can_length; //assign a variable for length
  byte can_data[8] = {0}; //assign an array for data

  if (CAN.available() == true) // Check to see if a valid message has been received.
  {
    CAN.read(&can_ID, &can_length, can_data); // read Message and assign data through reference operator &

    Serial1.print(millis());
    Serial1.print(F(",0x"));
    Serial1.print(can_ID, HEX); // Displays received ID
    Serial1.print(',');
    Serial1.print(can_length, HEX); // Displays message length
    for (byte i = 0; i < can_length; i++)
    {
      Serial1.print(',');
      if (can_data[i] < 0x10) // If the data is less than 10 hex it will assign a zero to the front as leading zeros are ignored...
      {
        Serial1.print('0');
      }
      Serial1.print(can_data[i], HEX); // Displays message data
    }
    Serial1.println(); // adds a line
  }
}


// Finally arduino loop to execute above function with a 50ms delay
void loop()
{
  readMessage();
  delay(50);
}

