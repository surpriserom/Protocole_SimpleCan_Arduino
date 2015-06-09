/*
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 51
 ** MISO - pin 50
 ** CLK - pin 52
 ** CS - pin 8
*/


//#include <SdFat.h>

  //Type declarations to handle the SD
 //const uint8_t chipSelect = 8; // CS pin on pin 8 in my board, TBD for the payload
 //SdFat sd;
 //const char* file = "imulog.txt";
  char buffer[80];
  
  
  
  //Type declarations to handle DATA
  char temp;
  char temp2;
    
  
  signed int GYROX, GYROY, GYROZ;
  signed int ACCELX, ACCELY, ACCELZ;
  signed int MAGX, MAGY, MAGZ;
  signed int YAW, PITCH, ROLL;
  
  String gyroString="";
  String accelString="";
  String magString="";
  String angString="";
   
  String dataString = "";
  
  
  
  //Functions declarations
  
  void waitInc(void);     //Waits for incoming serial data


  int waitG(void);      //waits for Gyro data
  int waitA(void);      //waits for Gyro data
  int waitM(void);      //waits for Gyro data
  int waitE(void);      //waits for Gyro data

  
  void recG(void); //Records Gyro data
  void recA(void); //Records Accel data
  void recM(void); //Records Magneto data
  void recE(void); //Records Euler data
  
  
  
  
  void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
   
   /*
  //Serial.print("Initializing SD card..."); 
   
  //REQUIRED
  pinMode(10, OUTPUT);
  //for debug
  pinMode(31,OUTPUT);
  
  
  // Initialize the card
  sd.init(SPI_FULL_SPEED, chipSelect);
  sd.remove(file);
 

  Serial.println("card initialized."); 
  */
    
  //Empties incoming buffer
  for(int i=0; i<63; i++)
  {
   temp=Serial1.read();
   delay(1);
  }
  
}




void loop()
{
   
  //Waits for a start sequence
    while (temp!='p')
  {
   waitInc();
   temp=Serial1.read();

   waitInc();
   Serial1.read();
  }
  
  
  //Reads address
  //5C (Gyro processed), 5E(accel processed), 60(magneto processed), 62(euler angles)
  waitInc();
  temp = Serial1.read();
    
//Record data starting from gyro  
  if(temp == 0x5C)
  {
    recG();
    waitA();
    recA();
    waitM();
    recM(); 
    waitE();
    recE(); 
  }
  
//Record data starting from accel   
    if(temp == 0x5E)
  {
    recA();
    waitM();
    recM();
    waitE();
    recE();
    waitG();
    recG();
  }

//Record data starting from magn   
    if(temp == 0x5E)
  {
    recG();
    waitA();
    recA();
    waitM();
    recM();
    waitE();
    recE();
  }  
  
  
//Record data starting from angles   
    if(temp == 0x5E)
  {
    recE();
    waitG(); 
    recG();
    waitA();
    recA();
    waitM();
    recM();
  }  
  
  
  
  
 //Assemble the whole dataset
 dataString = gyroString + accelString + magString + angString;
  
  
  if(dataString.equals("")==false)
  {
    /*
  //Logs the data on the SDcard
  ofstream dataLog(file, ios::out|ios::app);
  dataString.toCharArray(buffer,80);
  //Serial.println("sending string");
  dataLog << buffer << endl;
  dataLog.close();
  */
  //debugging
  //digitalWrite(31,HIGH);
  Serial.println(dataString);  
  }
  
  //reinitialize variables
  gyroString="";
  accelString="";
  magString="";
  angString="";
  dataString ="";
          
  //digitalWrite(31,LOW);
    
}



















// FUNCTIONS

  void waitInc(void)
  {
   int nbr=0;
   while(nbr==0)
   {     nbr=Serial1.available();   } 
  }


  void skip(void)
  {
    for (int i=0; i<7; i++)
    {
      waitInc();
      Serial1.read();
    }
  }



  int waitG(void)      //waits for Gyro data
  {
    int i=1;
    //Waits for a start sequence
    while (temp!='p')
    { waitInc();     temp=Serial1.read(); }
    
    //Skips packet type
    waitInc();
    Serial1.read();
    //Reads address
    waitInc();
    temp = Serial1.read();
    //Check address
    if(temp !=0x5C)
    {i=0;}
    return i;
  }
  
  
  
  int waitA(void)      //waits for Gyro data
  {
    int i=1;
    //Waits for a start sequence
    while (temp!='p')
    { waitInc();     temp=Serial1.read(); }
    
    //Skips packet type
    waitInc();
    Serial1.read();
    //Reads address
    waitInc();
    temp = Serial1.read();
    //Check address
    if(temp !=0x5E)
    {i=0;}
    return i;  
  }
  
  
  
  int waitM(void)      //waits for Gyro data
  {
    int i=1;
    //Waits for a start sequence
    while (temp!='p')
    { waitInc();     temp=Serial1.read();}
    
    //Skips packet type
    waitInc();
    Serial1.read();
    //Reads address
    waitInc();
    temp = Serial1.read();
    //Check address
    if(temp !=0x60)
    {i=0;}
    return i;   
  }
  
  
  
  int waitE(void)      //waits for Gyro data
  {
    int i=1;
    //Waits for a start sequence
    while (temp!='p')
    { waitInc();     temp=Serial1.read(); }
    
    //Skips packet type
    waitInc();
    Serial1.read();
    //Reads address
    waitInc();
    temp = Serial1.read();
    //Check address
    if(temp !=0x62)
    {i=0;}
    return i;  
  }











  void recG(void) //Records Gyro data
  {
    waitInc();
    temp= Serial1.read();
    waitInc();
    temp2= Serial1.read();
    GYROX =  (temp <<8) + (temp2);
  
    waitInc();
    temp= Serial1.read();
    waitInc();
    temp2= Serial1.read();     
    GYROY =  (temp <<8) + (temp2);
    
    waitInc();        
    temp= Serial1.read();
    waitInc();
    temp2= Serial1.read();        
    GYROZ =  (temp <<8) + (temp2);  
             
             
    gyroString += GYROX;
    gyroString += "\t";
    gyroString += GYROY;
    gyroString += "\t";
    gyroString += GYROZ;
    gyroString += "\t";
    
      //Serial.print(GYROX); Serial.print(","); Serial.print(GYROY); Serial.print(","); Serial.println(GYROZ);
  }
  
  
  void recA(void) //Records Accel data
  {
    waitInc();
    temp= Serial1.read();
    waitInc();
    temp2= Serial1.read();
    ACCELX =  (temp <<8) + (temp2);
            
    waitInc();        
    temp= Serial1.read();
    waitInc();
    temp2= Serial1.read();
    ACCELY =  (temp <<8) + (temp2);
    
    waitInc();      
    temp= Serial1.read();
    waitInc();
    temp2= Serial1.read();
    ACCELZ =  (temp <<8) + (temp2);
             
             
    accelString += ACCELX;
    accelString += "\t";
    accelString += ACCELY;
    accelString += "\t";
    accelString += ACCELZ;
    accelString += "\t";
  
      //Serial.print(ACCELX); Serial.print(","); Serial.print(ACCELY); Serial.print(","); Serial.println(ACCELZ);
  
  } 
 
 
  void recM(void) //Records Magneto data
  {
    waitInc();
    temp= Serial1.read();
    waitInc();
    temp2= Serial1.read();
    MAGX =  (temp <<8) + (temp2);
            
    waitInc();
    temp= Serial1.read();
    waitInc();
    temp2= Serial1.read();
    MAGY =  (temp <<8) + (temp2);
            
    waitInc();
    temp= Serial1.read();
    waitInc();
    temp2= Serial1.read();
    MAGZ =  (temp <<8) + (temp2); 
            
            
   magString += MAGX;
   magString += "\t";
   magString += MAGY;
   magString += "\t";
   magString += MAGZ;
   magString += "\t";   
  
      //Serial.print(MAGX); Serial.print(","); Serial.print(MAGY); Serial.print(","); Serial.println(MAGZ);
    
    
  }
  
  
  void recE(void) //Records Euler data
  {
    waitInc();
    temp= Serial1.read();
    waitInc();
    temp2= Serial1.read();
    YAW =  (temp <<8) + (temp2);
    
    waitInc();
    temp= Serial1.read();
    waitInc();
    temp2= Serial1.read();
    PITCH =  (temp <<8) + (temp2);
    
    waitInc();
    temp= Serial1.read();
    waitInc();
    temp2= Serial1.read();
    ROLL =  (temp <<8) + (temp2);  
    
                
    angString += YAW;
    angString += "\t";
    angString += PITCH;
    angString += "\t";
    angString += ROLL;  
    
    
      //Serial.print(YAW); Serial.print(","); Serial.print(PITCH); Serial.print(","); Serial.println(ROLL);
  }







