//#include <Servo.h>

#define STATE_ZERO 0 
#define STATE_S 1 
#define STATE_SN 2 
#define STATE_SNP 3 
#define STATE_PT 4 
#define STATE_READ_DATA 5 
#define STATE_CHK1 6 
#define STATE_CHK0 7 
#define PT_HAS_DATA 0b10000000 
#define PT_IS_BATCH 0b01000000 
#define PT_COMM_FAIL 0b00000001 

#define UM6_EULER_PHI_THETA 0x62 // Data register for angles 
#define UM6_GYRO_PROC_XY 0x5c // Data register for angular rates 
#define GYRO_SCALE_FACTOR 0.0610352 // Scale factor to convert register data to Degrees per Second 
#define EULER_SCALE_FACTOR 0.0109863 // Scale factor to convert register data to Degrees 

#define DATA_BUFF_LEN 16 

#define BAUD 115200 

byte aPacketData[DATA_BUFF_LEN]; 

byte c = 0; 

int nState = 0; 
int n = 0; 
int nDataByteCount = 0; 

struct IMU{ 
	int in; 
}phi, theta, psi; //Roll, pitch and yaw, respectively. 

struct GYRO{ 
 int in; 
}girX, girY, girZ; // angular rates relative to the axes X, Y and Z, respectively. 

typedef struct { 
 boolean HasData; 
 boolean IsBatch; 
 byte BatchLength; 
 boolean CommFail; 
 byte Address; 
 byte Checksum1; 
 byte Checksum0; 
 byte DataLength; 
} UM6_PacketStruct ; 

UM6_PacketStruct UM6_Packet; 

//Servo myservo; // create servo object to control a servo motor 

int pin = 18; // arduino pin 
int pos = 80; // servo position : 80Â° corresponds to the central axis of sand yacht 

 // (the wheel turns between 0Â° and 160Â°) 

int pos_new; 
int desired_angle = 40; // between 0Â° and 180Â° 
int error_angle = 0; 
int mutex = 0; // priority management 
int WaitCounter; // wait counter for stable data 
float P = 2.5; // proportional controller 
float D = 0.1; // derivative controller 

void setup(){ 

 //myservo.attach(pin); // attaches the servo on pin 18 to the servo object 
 //myservo.write(pos); // center the wheel at the axis 

 Serial.begin(BAUD); // initialize serial port 0 
 
    while (!Serial) {
        ; // wait for Serial1 port to connect. Needed for Leonardo only
    }
 Serial1.begin(BAUD); // initialize serial port 1
 
    while (!Serial1) {
        ; // wait for Serial1 port to connect. Needed for Leonardo only
    }
 WaitCounter = 0; 
} 

void loop(){ 
 n = Serial1.available(); 
 if (n > 0){ 
	 c = Serial1.read(); 
	 switch(nState){ 
		case STATE_ZERO : // Begin. Look for 's'. 
			Reset(); 
			if (c == 's'){ //0x73 = 's' 
				nState = STATE_S; 
			} else { 
				nState = STATE_ZERO; 
			} 
		break; 

		case STATE_S : // Have 's'. Look for 'n'. 

			if (c == 'n'){ //0x6E = 'n' 
				nState = STATE_SN; 
			} else { 
				nState = STATE_ZERO; 

			} 
			break; 
		 case STATE_SN : // Have 'sn'. Look for 'p'. 
			if (c == 'p'){ //0x70 = 'p' 
				nState = STATE_SNP; 
			} else { 
				nState = STATE_ZERO; 
			} 
		break; 
		case STATE_SNP : // Have 'snp'. Read PacketType and calculate DataLength. 
			UM6_Packet.HasData = 1 && (c & PT_HAS_DATA); 
			UM6_Packet.IsBatch = 1 && (c & PT_IS_BATCH); 
			UM6_Packet.BatchLength = ((c >> 2) & 0b00001111); 
			UM6_Packet.CommFail = 1 && (c & PT_COMM_FAIL); 
			nState = STATE_PT; 

			if (UM6_Packet.IsBatch){ 
				UM6_Packet.DataLength = UM6_Packet.BatchLength * 4; 
			} else { 
				UM6_Packet.DataLength = 4; 
			} 
		break; 
		case STATE_PT : // Have PacketType. Read Address. 
			UM6_Packet.Address = c; 
			nDataByteCount = 0;
			nState = STATE_READ_DATA;
		break;
		case STATE_READ_DATA : // Read Data. (UM6_PT.BatchLength * 4) bytes. 
			aPacketData[nDataByteCount] = c;
			nDataByteCount++;
			if (nDataByteCount >= UM6_Packet.DataLength){ 
				nState = STATE_CHK1; 
			} 
		break;
		case STATE_CHK1 : // Read Checksum 1 
			UM6_Packet.Checksum1 = c; 
			nState = STATE_CHK0;
		break;
		case STATE_CHK0 : // Read Checksum 0
			UM6_Packet.Checksum0 = c; 
			nState = STATE_ZERO; 
			ProcessPacket(); // Entire packet consumed. Process packet 
		break; 
		}
	}
} 

void ProcessPacket(){ 
	switch(UM6_Packet.Address){ // Get the angles values (phi, theta and psi)
		case UM6_EULER_PHI_THETA :
			phi.in = ((aPacketData[0] << 8) | aPacketData[1]) * EULER_SCALE_FACTOR;
			theta.in = ((aPacketData[2] << 8) | aPacketData[3]) * EULER_SCALE_FACTOR;
			psi.in = ((aPacketData[4] << 8) | aPacketData[5]) * EULER_SCALE_FACTOR;
			//ManageServo();
		break;
		case UM6_GYRO_PROC_XY : // Get the angular rates
			if (UM6_Packet.HasData && !UM6_Packet.CommFail){
				girX.in = ((aPacketData[0] << 8) | aPacketData[1]) * GYRO_SCALE_FACTOR;
				girY.in = ((aPacketData[2] << 8) | aPacketData[3]) * GYRO_SCALE_FACTOR;
				if (UM6_Packet.DataLength > 4){
					girZ.in = ((aPacketData[4] << 8) | aPacketData[5]) * GYRO_SCALE_FACTOR;
				}
			}
		break; 
	}
	PrintDebug(); 
} 

void ManageServo(){
	if (WaitCounter < 800){ // wait to obtain stable values of data 
		WaitCounter++; 
	return; 
	}
	// Manage the servo motor to prevent the fall of sand yacht 
	if (theta.in > 0){ // Turn to left
		mutex = 1;
	//myservo.write(myservo.read() - 45);
	} else if (theta.in < -20){ // Turn to right
		mutex = 1; 
		// myservo.write(myservo.read() + 45); 
	} else {
		mutex = 0;
	} 
	// Manage servo motor to obtain desired angle 
	error_angle = psi.in - desired_angle;
	if (error_angle < - 180){
		error_angle = error_angle + 360;
	}
	if (error_angle > 0){ // Turn to left 
		if (girZ.in > 0){
			pos_new = pos - P * error_angle + D * girZ.in;
		} else{
			pos_new = pos - P * error_angle - D * girZ.in;
		}
	} else{ // Turn to right 
		if (girZ.in > 0){
			pos_new = pos - P * error_angle + D * girZ.in;
		} else{
			pos_new = pos - P * error_angle - D * girZ.in;
		}
	}
	if (mutex == 0){
		//myservo.write(pos_new); 
	}
} 

void Reset(){ 
 UM6_Packet.HasData = false; 
 UM6_Packet.IsBatch = false; 
 UM6_Packet.BatchLength = 0; 
 UM6_Packet.CommFail = false; 
 UM6_Packet.Address = 0; 
 UM6_Packet.Checksum1 = 0; 
 UM6_Packet.Checksum0 = 0; 
 UM6_Packet.DataLength = 0; 
} 

void PrintDebug(){ 
 Serial.print("PHI = "); 
 Serial.print(phi.in); 
 Serial.print(" THETA = "); 
 Serial.print(theta.in); 
 Serial.print(" PSI = "); 
 Serial.print(psi.in); 
 Serial.print(" girX = "); 
 Serial.print(girX.in); 
 Serial.print(" girY = "); 
 Serial.print(girY.in); 
 Serial.print(" girZ = "); 
 Serial.print(girZ.in); 
 Serial.print(" ERROR_ANGLE = "); 
 Serial.print(error_angle); 
 Serial.print(" POS_NEW = "); 
 Serial.print(pos_new); 
 Serial.println("."); 
}

