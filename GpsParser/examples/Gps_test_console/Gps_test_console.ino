/*------------------------------------------------------+
|            Code for testing GPS receiver              |
|  Receiver type Cirus CN-06                            |
| Gps module  ublox Neo-6m-0-001                        |
+-------------------------------------------------------*/
#include <GpsParser.h>

char sentence[NMEALenght];

//led pour voir si le programme tourne
const int led = 13;
boolean test = false;

GPS_PARSER parserGPS(true);

void setup()
{
	//port serie usb
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for Serial port to connect. Needed for Leonardo only
   }
   
  Serial1.begin(9600);//tx0 et rx0 connecteur d0 et d1
  while (!Serial1) {
        ; // wait for Serial1 port to connect. Needed for Leonardo only
  }
  
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  
  Serial.println("Gps Test started\n");
}

void loop()
{
  static int i = 0;
  static unsigned int time1 = 0;
  volatile unsigned int time2 = millis();
  
  if(time1 < time2)
  {
    time1 += (test ? 250 : 500);
    digitalWrite(led, (test ? HIGH : LOW));
    test = !test;
  }
  
  if (Serial1.available()>0)
  {
    char ch = Serial1.read();
    if (ch != '\n' && i < NMEALenght)
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

void displayGPS()
{
  if(parserGPS.isGPRMC(sentence))
  {
	GPRMC_frame gpsFrame;
	GPRMC_data gpsData;
	parserGPS.parseGPRMC(sentence,&gpsFrame);
	parserGPS.convertGprmcFrame( &gpsFrame, &gpsData);
    Serial.print("Nav:");
    Serial.print( (gpsFrame.valide == 'A'? "Valide" : "Erronne"));
    Serial.print(" | Lat: ");
	Serial.print(gpsFrame.latDeg);
	Serial.print("deg ");
	Serial.print(gpsFrame.latMn);
	Serial.print("mn ");
	Serial.print(gpsFrame.latInd);
	Serial.print(" : ");
    Serial.print(gpsData.latitude,6);
    
    Serial.print(" | Long: ");
	Serial.print(gpsFrame.longDeg);
	Serial.print("deg ");
	Serial.print(gpsFrame.longMn);
	Serial.print("mn ");
	Serial.print(gpsFrame.longInd);
	Serial.print(" : ");
    Serial.println(gpsData.longitude,6);
  }
  else
  {
    if (parserGPS.isGPGGA(sentence))
    {
		GPGGA_frame ggaFrame;
		parserGPS.parseGPGGA(sentence, &ggaFrame);
		Serial.print(ggaFrame.hour);
		Serial.print(":");
		Serial.print(ggaFrame.minute);
		Serial.print(":");
		Serial.print(ggaFrame.second);
		Serial.print(" | nbSat ");
		Serial.print(ggaFrame.nbSat);
		Serial.print(" | prec ");
		Serial.print(ggaFrame.accuracy);
		Serial.print(" | alt ");
		Serial.print(ggaFrame.altitude);
		Serial.println(ggaFrame.altitudeUnite);
    }
  }
}