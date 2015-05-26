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

/*************************USB Functions for bootloader****************************/
uint8_t SimpleCANClass::char_to_byte(char *s)
{
	uint8_t t = *s;
	
	if (t >= 'a')
		t = t - 'a' + 10;
	else if (t >= 'A')
		t = t - 'A' + 10;
	else
		t = t - '0';
	
	return t;
}
uint8_t SimpleCANClass::hex_to_byte(char *s)
{
	return (char_to_byte(s) << 4) | char_to_byte(s + 1);
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

void SimpleCANClass::setMaskOrFilter(uint8_t mask, uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3) {
	// change to configuration mode
	mcp2515_bit_modify(CANCTRL, 0xe0, (1<<REQOP2));
	while ((mcp2515_read_register(CANSTAT) & 0xe0) != (1<<REQOP2))
		;
	mcp2515_write_register(mask, b0);
	mcp2515_write_register(mask+1, b1);
	mcp2515_write_register(mask+2, b2);
	mcp2515_write_register(mask+3, b3);
	mcp2515_set_mode(NORMAL_MODE);
}

// ----------------------------------------------------------------------------
uint8_t SimpleCANClass::spi_putc(uint8_t data)
{
	// put byte in send-buffer
	SPDR = data;

	// wait until byte was send
	while( !( SPSR & (1<<SPIF) ) )
		;

	return SPDR;

}

/****************************mcp2515_read_id function to read an ID***************************/
#if	SUPPORT_EXTENDED_CANID
uint8_t SimpleCANClass::mcp2515_read_id(uint32_t *id)
{
	uint8_t first;
	uint8_t tmp;

	first = spi_putc(0xff);
	tmp   = spi_putc(0xff);

	if (tmp & (1 << IDE)) {
		spi_start(0xff);
	
		*((uint16_t *) id + 1)  = (uint16_t) first << 5;
		*((uint8_t *)  id + 1)  = spi_wait();
		spi_start(0xff);
	
		*((uint8_t *)  id + 2) |= (tmp >> 3) & 0x1C;
		*((uint8_t *)  id + 2) |=  tmp & 0x03;
	
		*((uint8_t *)  id)      = spi_wait();
	
		return TRUE;
	}
	else {
		spi_start(0xff);
	
		*((uint8_t *)  id + 3) = 0;
		*((uint8_t *)  id + 2) = 0;
	
		*((uint16_t *) id) = (uint16_t) first << 3;
	
		spi_wait();
		spi_start(0xff);
	
		*((uint8_t *) id) |= tmp >> 5;
	
		spi_wait();
	
		return FALSE;
	}
}

#else

uint8_t SimpleCANClass::mcp2515_read_id(uint16_t *id)
{
	uint8_t first;
	uint8_t tmp;

	first = spi_putc(0xff);
	tmp   = spi_putc(0xff);

	if (tmp & (1 << IDE)) {
		spi_putc(0xff);
		spi_putc(0xff);
	
		return 1;			// extended-frame
	}
	else {
		spi_start(0xff);
	
		*id = (uint16_t) first << 3;
	
		spi_wait();
		spi_start(0xff);
	
		*((uint8_t *) id) |= tmp >> 5;
	
		spi_wait();
	
		if (tmp & (1 << SRR))
			return 2;		// RTR-frame
		else
			return 0;		// normal-frame
	}
}
#endif	// SUPPORT_EXTENDED_CANID

/****************************END mcp2515_read_id***************************/

/****************************mcp2515_send_message function to send a CAN msg***************************/
uint8_t SimpleCANClass::mcp2515_send_message(const can_t *msg)
{
	// Read status of the MCP2515
	uint8_t status = mcp2515_read_status(SPI_READ_STATUS);

	/* Statusbyte:
	 *
	 * Bit	Function
	 *  2	TXB0CNTRL.TXREQ
	 *  4	TXB1CNTRL.TXREQ
	 *  6	TXB2CNTRL.TXREQ
	 */
	uint8_t address;
	if (_bit_is_clear(status, 2)) {
		address = 0x00;
	}
	else if (_bit_is_clear(status, 4)) {
		address = 0x02;
	} 
	else if (_bit_is_clear(status, 6)) {
		address = 0x04;
	}
	else {
		// All buffers are occupied,
		// Message can not be sent
		return 0;
	}

	RESET(MCP2515_CS);
	spi_putc(SPI_WRITE_TX | address);
	#if SUPPORT_EXTENDED_CANID
		mcp2515_write_id(&msg->id, msg->flags.extended);
	#else
		mcp2515_write_id(&msg->id);
	#endif
	uint8_t length = msg->length & 0x0f;

	// If the message contains a "Remote Transmit Request"?
	if (msg->flags.rtr)
	{
		// An RTR msg indeed has a length,
		// But contains no data
	
		// Setting the message length + RTR
		spi_putc((1<<RTR) | length);
	}
	else
	{
		// Setting the message length
		spi_putc(length);
	
		// Data
		for (uint8_t i=0;i<length;i++) {
			spi_putc(msg->data[i]);
		}
	}
	SET(MCP2515_CS);

	_delay_us(1);

	//Send CAN message
	//the last three bits in the RTS command specify which
	//Buffer to be sent.
	RESET(MCP2515_CS);
	address = (address == 0) ? 1 : address;
	spi_putc(SPI_RTS | address);
	SET(MCP2515_CS);

	CAN_INDICATE_TX_TRAFFIC_FUNCTION;

	return address;
}

/****************************END mcp2515_send_message***************************/
/*******************************mcp2515_set_mode function to set CAN mode******************************/
// ----------------------------------------------------------------------------
void SimpleCANClass::mcp2515_set_mode(can_mode_t mode)
{
	uint8_t reg = 0;

	if (mode == LISTEN_ONLY_MODE) {
		reg = (1<<REQOP1)|(1<<REQOP0);
	}
	else if (mode == LOOPBACK_MODE) {
		reg = (1<<REQOP1);
	}
	else if (mode == SLEEP_MODE) {
		reg = (1<<REQOP0);
	}
	
	// set the new mode
	mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), reg);
	while ((mcp2515_read_register(CANSTAT) & 0xe0) != reg) {
		// wait for the new mode to become active
	}
}

/*******************************END mcp2515_set_mode******************************/
// ----------------------------------------------------------------------------
#ifdef USE_SOFTWARE_SPI
	static uint8_t usi_interface_spi_temp;

	void SimpleCANClass::spi_start(uint8_t data) {
		usi_interface_spi_temp = spi_putc(data);
	}

	uint8_t SimpleCANClass::spi_wait(void) {
		return usi_interface_spi_temp;
	}
#else
	void SimpleCANClass::spi_start(uint8_t data) {
		SPDR = data;
	}

	uint8_t SimpleCANClass::spi_wait(void) {
		// Wait until the previous values are ​​written/transfer complete
		while(!(SPSR & (1<<SPIF)))
			;

		return SPDR;
	}
#endif
/*******************************BEG mcp2515_write_id******************************/
// ----------------------------------------------------------------------------
#if SUPPORT_EXTENDED_CANID
	void SimpleCANClass::mcp2515_write_id(const uint32_t *id, uint8_t extended)
	{
		uint8_t tmp;

		if (extended) {
			spi_start(*((uint16_t *) id + 1) >> 5);
	
			// Calculate next value
			tmp  = (*((uint8_t *) id + 2) << 3) & 0xe0;
			tmp |= (1 << IDE);
			tmp |= (*((uint8_t *) id + 2)) & 0x03;
	
			// Wait until the previous values are ​​written
			spi_wait();
	
			// Write remaining values
			spi_putc(tmp);
			spi_putc(*((uint8_t *) id + 1));
			spi_putc(*((uint8_t *) id));
		}
		else {
			spi_start(*((uint16_t *) id) >> 3);
	
			// Calculate next values
			tmp = *((uint8_t *) id) << 5;
			spi_wait();
	
			spi_putc(tmp);
			spi_putc(0);
			spi_putc(0);
		}
	}
#else
	void SimpleCANClass::mcp2515_write_id(const uint16_t *id)
	{
		uint8_t tmp;

		spi_start(*id >> 3);
		tmp = *((uint8_t *) id) << 5;
		spi_wait();

		spi_putc(tmp);
		spi_putc(0);
		spi_putc(0);
	}
#endif	// USE_EXTENDED_CANID
/*******************************END mcp2515_write_id******************************/
/*
// -------------------------------------------------------------------------
bool SimpleCANClass::mcp2515_init(uint8_t bitrate)
{
	if (bitrate >= 8)
		return false;

	SET(MCP2515_CS);
	SET_OUTPUT(MCP2515_CS);

	// Enable pins for the SPI interface
	RESET(P_SCK);
	RESET(P_MOSI);
	RESET(P_MISO);

	SET_OUTPUT(P_SCK);
	SET_OUTPUT(P_MOSI);
	SET_INPUT(P_MISO);

	// Set SPI setting
	mcp2515_spi_init();

	// MCP2515 reset by software reset 
	// then he is automatically in the configuration mode
	RESET(MCP2515_CS);
	spi_putc(SPI_RESET);

	_delay_ms(1);

	SET(MCP2515_CS);

	// Wait a bit until the MCP2515 has restarted
	_delay_ms(10);

	// CNF1 .. 3 register load (bit timing)
	RESET(MCP2515_CS);
	spi_putc(SPI_WRITE);
	spi_putc(CNF3);
	for (uint8_t i=0; i<3 ;i++ ) {
		spi_putc(pgm_read_byte(&_mcp2515_cnf[bitrate][i]));
	}
	// Enable / Disable the interrupts
	spi_putc(MCP2515_INTERRUPTS);
	SET(MCP2515_CS);

	// TXnRTS bits switch as inputs
	mcp2515_write_register(TXRTSCTRL, 0);

	#if defined(MCP2515_INT)
		SET_INPUT(MCP2515_INT);
		SET(MCP2515_INT);
	#endif

	#ifdef RXnBF_FUNKTION
		SET_INPUT(MCP2515_RX0BF);
		SET_INPUT(MCP2515_RX1BF);
	
		SET(MCP2515_RX0BF);
		SET(MCP2515_RX1BF);
	
		// Enable pin functions for RX0BF and RX1BF
		mcp2515_write_register(BFPCTRL, (1<<B0BFE)|(1<<B1BFE)|(1<<B0BFM)|(1<<B1BFM));
	#else
		#ifdef MCP2515_TRANSCEIVER_SLEEP
			// activate the pin RX1BF as GPIO which is connected 
			// to RS of MCP2551 and set it to 0
			mcp2515_write_register(BFPCTRL, (1<<B1BFE));
		#else
			// Disabling RXnBF Pins (High Impedance State)
			mcp2515_write_register(BFPCTRL, 0);
		#endif
	#endif

	//Testing whether that can be accessed on the registers described
	bool error = false;

	if (mcp2515_read_register(CNF2) != pgm_read_byte(&_mcp2515_cnf[bitrate][1])) {
		error = true;
	}

	// Device back into normal mode enable 
	// and enable / disable the Clkout pins
	mcp2515_write_register(CANCTRL, CLKOUT_PRESCALER_);

	if (error) {
		return false;
	}
	else
	{
		while ((mcp2515_read_register(CANSTAT) & 0xe0) != 0) {
			// Wait until mode switch to Normal
		}
	
		return true;
	}
}
/****************************END mcp2515**************************/
