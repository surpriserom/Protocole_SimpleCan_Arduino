
String inputString0 = ""; 
boolean stringComplete0 = false;
String inputString1 = ""; 
boolean stringComplete1 = false;

void setup() {
   Serial.begin(9600);
   Serial1.begin(9600);
   
    Serial.println("hi, computeur");
    Serial1.println("hi, port1");
    
    inputString1.reserve(50);
    inputString0.reserve(50);

}

void loop() {
  if (stringComplete0){
    Serial.println(inputString0);
    inputString0="";
    stringComplete0=false;
  }
  
  if (stringComplete1){
    Serial.println(inputString1);
    inputString1="";
    stringComplete1=false;
  }
  
}



void serialEvent() {
   while (Serial.available()) {
     static int sizeOfString=0;
     char inChr = (char)Serial.read();
     inputString0+=inChr;
     sizeOfString++;
     if(inChr == '\n' || sizeOfString>=16){
       stringComplete0=true;
       sizeOfString=0;
     }
   }
   while (Serial1.available()) {
     static int sizeOfString1=0;
     char inChr = (char)Serial1.read();
     inputString1+=inChr;
     sizeOfString1++;
     if(inChr == '\n'|| sizeOfString1){
       stringComplete1=true;
       sizeOfString1=0;
     }
   }
}
