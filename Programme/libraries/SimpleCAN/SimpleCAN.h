#ifndef SIMPLECAN_H
#define SIMPLECAN_H

#include "Arduino.h"
#include "../CAN/Can.h"
#include "sailingSpecifics.h"

#if defined (__cplusplus)
	extern "C" {
#endif

#include <stdint.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>



#if defined (__cplusplus)
}
#endif

typedef struct
{
	uint32_t id;
	uint64_t data;
	uint8_t length;
} NetworkVariable;

class SimpleCANClass
{
	public:
		//ISR
		void matchAndRetrieve();
		//Initialisation function with node ID
		void init(uint8_t bitrate);
		//Election process
		void election(uint32_t id);
		//Set synchronisation period
		void synchronisation();
		//New subscription
		void keepVariableUpdated(uint32_t id);
		//Update the variable
		void setVariable(uint32_t id,uint64_t val);
		//Get the variable
		uint64_t getVariable(uint32_t id);		
		
		
		void activateInterrupt(void);
		void resetFiltersAndMasks(void);
		
		/**mcp2515_get_message**/
		uint8_t mcp2515_get_message(can_t *);
		/**mcp2515**/
		void mcp2515_write_register(uint8_t, uint8_t);
		uint8_t mcp2515_read_register(uint8_t);
		void mcp2515_bit_modify(uint8_t, uint8_t, uint8_t);
		uint8_t mcp2515_read_status(uint8_t);
		bool mcp2515_init(uint8_t);
		
		/**USB**/
		bool usbcan_decode_message(char *str, uint8_t length);
		char usbcan_decode_command(char *str, uint8_t length);
		uint8_t char_to_byte(char *s);
		uint8_t hex_to_byte(char *s);
	
		/**Debugging*/
		//Automatically send the message into CAN frames. Split is made if necessary
		void printString2Can(char []);

	private:
		bool leader;
		NetworkVariable VarArray[N];
	
		
};

void isrSimpleCAN();

extern SimpleCANClass SimpleCAN;

#endif // SIMPLECAN_H
