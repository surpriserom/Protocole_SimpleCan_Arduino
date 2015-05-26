#include "SimpleCAN.h"

//Instance of SimpleCANClass
SimpleCANClass SimpleCAN;

void isrSimpleCAN() {
    SimpleCAN.matchAndRetrieve();
}

//ISR
void SimpleCANClass::matchAndRetrieve(){
	
	uint32_t bufID = 0;
	uint8_t statu = 0;
	uint8_t frameType = 0;
	

	CAN.mcp2515_read_id_complete(&bufID,&statu,&frameType);

	//Tests if the array contains a node matching the ID in the buffer
	
	int i = 0;
	NetworkVariable currentNV;
	uint32_t currentID = 0;
	do{
		currentNV = SimpleCAN.VarArray[i];
		currentID = currentNV.id;
		i++;
	}
	while(i != N && currentID != bufID);

	if(i != N+1)
	{
		//Continue to read the message in the buffer and convert it
		can_t msg;
		CAN.mcp2515_get_data(&msg,frameType,statu);
		mapReceive(&SimpleCAN.VarArray[i-1].data,msg.data,msg.length);
	}
}

void SimpleCANClass::init(uint8_t bitrate){

	//Initialisation of the MCP2515
	CAN.mcp2515_init(bitrate);
  	// Reset filters and masks
 	CAN.resetFiltersAndMasks();
	// Initialization of network variable array
	for (int i=0; i<N; i++){
		this->VarArray[i].id = 0;
		this->VarArray[i].data = 0;
		this->VarArray[i].length = 0;
	}
	// Configuration of interrupts
	attachInterrupt(0,isrSimpleCAN,FALLING);
	//Run the ISR to check if an interruption has already occured
	isrSimpleCAN();
}

void SimpleCANClass::election(uint32_t id){
	/* Node start sending its ID on the bus just after the init process
	* Then other nodes know each other IDs and could start an election
	* The minimum ID will win the election and will be responsible of sync process
	*/
	leader = false;
	can_t msg;
	msg.id=id;
	msg.data[0]='S';
	msg.length=1;
	msg.flags.rtr=0;
	msg.flags.extended=0;
	CAN.mcp2515_send_message(&msg);
}

void SimpleCANClass::synchronisation(){
	/*Init interruption
	* Timer: 1
	* Prescaler: 64
	* Target frequency: 10hz
	* Int Mode: CTC
	*/
	cli();//stop interrupts
	//set timer1 interrupt at 10Hz
	TCCR1A = 0;// set entire TCCR1A register to 0
	TCCR1B = 0;// same for TCCR1B
	TCNT1  = 0;//initialize counter value to 0
	// set compare match register for 10hz increments
	OCR1A = F_CPU*10/(TCLOCK*64); //24999 = (16*10^6) / (10*64) - 1 (must be <65536)
	// turn on CTC mode
	TCCR1B |= (1 << WGM12);
	// Set CS10 and CS11 bit for 64 prescaler
	TCCR1B |= (1 << CS11);
	TCCR1B |= (1 << CS10);
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);
	sei();//allow interrupts
}

//***************Tools for debugging****************//
//This function allows the transmission of text message into a CAN message. The string is automatically cut to fit into a frame.
//For better results, use short messages (<=8 characters) to use only one frame.
void SimpleCANClass::printString2Can(char data[]){
	can_t msg;
	int compt=0;
	msg.id =0xFF;
	msg.flags.rtr = 0;
	msg.flags.extended = 0;
	for(int i=0;i<strlen(data)+1;i++){
		if(data[i]!='\0'){
			msg.data[i%8]=data[i];
		}
		else {
			msg.length = (i-1)-8*compt;
			CAN.mcp2515_send_message(&msg);
			break;
		}
		if(i%8==7){
			msg.length = 8;
			CAN.mcp2515_send_message(&msg);
			compt++;
		}
	}
}

void SimpleCANClass::setVariable(uint32_t id, uint64_t data){
 	can_t msg;
	msg.flags.rtr = 0;
	msg.id=id;

	//Put data into data[8]
        mapSend(msg.data,data,id);

	//Precise how many bytes are used
	msg.length=8;

	//send the CAN message
	noInterrupts(); // needed to avoid conflicts while using SPI
	CAN.mcp2515_send_message(&msg);
	interrupts();
}



//New subscription to a network variable
void SimpleCANClass::keepVariableUpdated(uint32_t id){

	//Add it to the list
	int i=0;
	while(this->VarArray[i].id != 0){
		i++;
	}
	this->VarArray[i].id=id;
}



uint64_t SimpleCANClass::getVariable(uint32_t id){

	NetworkVariable currentNV;
	uint32_t currentID;

	int i = 0;
	do{
		currentNV = this->VarArray[i];
		currentID = currentNV.id;
		i++;
	}
	while(i != N+1 && currentID != id);

	if(i != N+1)
	{
		return currentNV.data;
		
	}
	else
	{
		return -1;
		
	}
	
}

//Activate Interrupt when receive a message on RX0 or RX1
void SimpleCANClass::activateInterrupt(void){
	mcp2515_write_register(CANINTE, 0x03);
}

void SimpleCANClass::resetFiltersAndMasks(void) {
	//disable first buffer
	setMaskOrFilter(0x20,   0b00000000, 0b00000000, 0b00000000, 0b00000000);
	setMaskOrFilter(0x00, 0b00000000, 0b00000000, 0b00000000, 0b00000000);
	setMaskOrFilter(0x04, 0b00000000, 0b00000000, 0b00000000, 0b00000000);

	//disable the second buffer
	setMaskOrFilter(0x24,   0b00000000, 0b00000000, 0b00000000, 0b00000000); 
	setMaskOrFilter(0x08, 0b00000000, 0b00000000, 0b00000000, 0b00000000);
	setMaskOrFilter(0x10, 0b00000000, 0b00000000, 0b00000000, 0b00000000); 
	setMaskOrFilter(0x14, 0b00000000, 0b00000000, 0b00000000, 0b00000000);
	setMaskOrFilter(0x18, 0b00000000, 0b00000000, 0b00000000, 0b00000000); 
}

/****************************mcp2515_get_message function to get an incoming msg***************************/
uint8_t SimpleCANClass::mcp2515_get_message(can_t *msg)
{
	/* Todo rewrite get_message en utilisant get_id_complete() and get_data()
	uint8_t status;
	uint8_t frameType;
	mcp2515_read_id_complete(&msg->id,&status,&frameType);
	mcp2515_get_data(msg,frameType,status);
    */

	
	uint8_t addr;

	#ifdef	RXnBF_FUNKTION
		if (!IS_SET(MCP2515_RX0BF))
			addr = SPI_READ_RX;
		else if (!IS_SET(MCP2515_RX1BF))
			addr = SPI_READ_RX | 0x04;
		else
			return 0;
	#else
		// read status
		uint8_t status = mcp2515_read_status(SPI_RX_STATUS);
	
		if (_bit_is_set(status,6)) {
			// message in buffer 0
			addr = SPI_READ_RX;
		}
		else if (_bit_is_set(status,7)) {
			// message in buffer 1
			addr = SPI_READ_RX | 0x04;
		}
		else {
			// Error: no message available
			return 0;
		}
	#endif

	RESET(MCP2515_CS);
	spi_putc(addr);

	// CAN ID reading and checking
	uint8_t tmp = mcp2515_read_id(&msg->id);
	#if SUPPORT_EXTENDED_CANID
		msg->flags.extended = tmp & 0x01;
	#else
		if (tmp & 0x01) {
			// Discard messages with extended ID
			SET(MCP2515_CS);
			#ifdef	RXnBF_FUNKTION
			if (!IS_SET(MCP2515_RX0BF))
			#else
			if (_bit_is_set(status, 6))
			#endif
				mcp2515_bit_modify(CANINTF, (1<<RX0IF), 0);
			else
				mcp2515_bit_modify(CANINTF, (1<<RX1IF), 0);
		
			return 0;
		}
	#endif

	// read DLC
	uint8_t length = spi_putc(0xff);
	#ifdef RXnBF_FUNKTION
		if (!(tmp & 0x01))
			msg->flags.rtr = (tmp & 0x02) ? 1 : 0;
		else
			msg->flags.rtr = (length & (1<<RTR)) ? 1 : 0;
	#else
		msg->flags.rtr = (_bit_is_set(status, 3)) ? 1 : 0;
	#endif

	length &= 0x0f;
	msg->length = length;
	// read data
	for (uint8_t i=0;i<length;i++) {
		msg->data[i] = spi_putc(0xff);
	}
	SET(MCP2515_CS);

	// clear interrupt flag
	#ifdef RXnBF_FUNKTION
	if (!IS_SET(MCP2515_RX0BF))
	#else
	if (_bit_is_set(status, 6))
	#endif
		mcp2515_bit_modify(CANINTF, (1<<RX0IF), 0);
	else
		mcp2515_bit_modify(CANINTF, (1<<RX1IF), 0);

	CAN_INDICATE_RX_TRAFFIC_FUNCTION;

	#ifdef RXnBF_FUNKTION
		return 1;
	#else
		return (status & 0x07) + 1;
	#endif
}

/****************************END mcp2515_get_message***************************/
// ----------------------------------------------------------------------------
bool SimpleCANClass::usbcan_decode_message(char *str, uint8_t length)
{
	can_t msg;
	uint8_t dlc_pos;
	bool extended;
	
	if (str[0] == 'R' || str[0] == 'T') {
		extended = true;
		dlc_pos = 9;
	}
	else {
		extended = false;
		dlc_pos = 4;
	}
	
	if (length < dlc_pos + 1)
		return false;
	
	// get the number of data-bytes for this message
	msg.length = str[dlc_pos] - '0';
	
	if (msg.length > 8)
		return false;		// too many data-bytes
	
	
	if (str[0] == 'r' || str[0] == 'R') {
		msg.flags.rtr = true;
		if (length != (dlc_pos + 1))
			return false;
	}
	else {
		msg.flags.rtr = false;
		if (length != (msg.length * 2 + dlc_pos + 1))
			return false;
	}
	
	// read the messge-identifier
	if (extended)
	{
		uint16_t id;
		uint16_t id2;
		
		id  = hex_to_byte(&str[1]) << 8;
		id |= hex_to_byte(&str[3]);
		
		id2  = hex_to_byte(&str[5]) << 8;
		id2 |= hex_to_byte(&str[7]);
		
		msg.id = (uint32_t) id << 16 | id2;
	}
	else {
		uint16_t id;
		
		id  = char_to_byte(&str[1]) << 8;
		id |= hex_to_byte(&str[2]);
		
		msg.id = id;
	}
	
	msg.flags.extended = extended;
	
	// read data if the message is no rtr-frame
	if (!msg.flags.rtr)
	{
		char *buf = str + dlc_pos + 1;
		uint8_t i;
		
		for (i=0; i < msg.length; i++)
		{
			msg.data[i] = hex_to_byte(buf);
			buf += 2;
		}
	}
	
	// finally try to send the message
	if (mcp2515_send_message( &msg ))
		return true;
	else
		return false;
}

// ----------------------------------------------------------------------------
char SimpleCANClass::usbcan_decode_command(char *str, uint8_t length)
{
	uint8_t temp;
	uint8_t i;
	if (length == 0)
		return('0');
	
	switch (str[0]) {
		case 'R':	// send frames
		case 'T':
		case 'r':
		case 't':	
			if ( !usbcan_decode_message(str, length) ) {
				goto error;
			}
			break;	
	}

	return('\r');	// command could be executed
	
error:
	return('7');		// Error in command
}

// -------------------------------------------------------------------------
void SimpleCANClass::mcp2515_write_register( uint8_t adress, uint8_t data )
{
	RESET(MCP2515_CS);

	spi_putc(SPI_WRITE);
	spi_putc(adress);
	spi_putc(data);

	SET(MCP2515_CS);
}

// -------------------------------------------------------------------------
uint8_t SimpleCANClass::mcp2515_read_register(uint8_t adress)
{
	uint8_t data;

	RESET(MCP2515_CS);

	spi_putc(SPI_READ);
	spi_putc(adress);

	data = spi_putc(0xff);	

	SET(MCP2515_CS);

	return data;
}

// -------------------------------------------------------------------------
void SimpleCANClass::mcp2515_bit_modify(uint8_t adress, uint8_t mask, uint8_t data)
{
	RESET(MCP2515_CS);

	spi_putc(SPI_BIT_MODIFY);
	spi_putc(adress);
	spi_putc(mask);
	spi_putc(data);

	SET(MCP2515_CS);
}

// ----------------------------------------------------------------------------
uint8_t SimpleCANClass::mcp2515_read_status(uint8_t type)
{
	uint8_t data;

	RESET(MCP2515_CS);

	spi_putc(type);
	data = spi_putc(0xff);
	spi_putc(0xff);
	SET(MCP2515_CS);

	return data;
}