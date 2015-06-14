int baudRate = 9600;
void setup() { 

 // initialize both serial ports: 

 Serial.begin(baudRate); 

    while (!Serial) {
        ; // wait for Serial1 port to connect. Needed for Leonardo only
    }
 Serial1.begin(baudRate); 

    while (!Serial1) {
        ; // wait for Serial1 port to connect. Needed for Leonardo only
    }
} 

void loop() { 

 // read from port 1, send to port 0: 

 if (Serial1.available()) { 

 int inByte = Serial1.read(); 

 Serial.write(inByte); 

 } 

 

 // read from port 0, send to port 1: 

 if (Serial.available()) { 

 int inByte = Serial.read(); 

 Serial1.write(inByte); 

 } 

}
