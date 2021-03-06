##Protocole SimpleCAN pour bus à base d'Arduino
![Image of node](https://github.com/surpriserom/Protocole_SimpleCan_Arduino/blob/master/Document/image/5boxes.jpg)
###Description 
Le projet a pour objectif de définir une sur couche du protocole CAN, appelée SimpleCAN, pour faire communiquer entre-eux un ensemble de noeuds composés de cartes Arduino associées à une interface CAN.
L'approche devra être validée, au travers d'une application simple de visualisation et d'envoi de données via un PC, sur un matériel existant consistant en 5 noeuds : un permettant une connexion PC via USB, 
un destiné au décodage de données propriétaires SeaTalk (Raymarine), deux destinés à du traitement de données NMEA (issues d'un GPS et d'une centrale Tactick) et le dernier portant une centrale inertielle.

Les programmes pour les cartes testées sont disponible dans le dossier **Programe_Test**, pour le test du réseaux CAN avec 3 noeuds (interface USB, capteur UM6 et interface NMEA), 
les programmes sont dans les dossiers **receive_gps_accelero_ex** pour l'interface USB, **send_nmea_GPS_ex** pour l'interface NMEA et **UM6_CAN_ex** pour le capteur UM6. 

Le fichier **dump_communication_3noeuds.txt** est une copie de ce que donne la console quand les 3 noeuds sont connectés. 

La version du logiciel utilisé lors du développement est la 1.6.4.

Les driver pour le programmateur USBtinyISP est dans le dossier **Programme**, ce dossier contient aussi le logiciel pour calibrer le capteur **UM6**, 
pour l'utiliser il faut utiliser la carte Arduino comme passerelle port serie avec le programme **Programe_Test\Serial_read_write**

###Basée sur le projet de splashelec 
voir le [wiki](http://wiki.splashelec.com/) et [github](https://github.com/splashelec/splashelec) de splashelec

#### Lien vers les librairies CAN compatible MCP2515 trouver sur Github étudier lors du projet
[McNeight/CAN-Library](https://github.com/McNeight/CAN-Library) : Librairies CAN multiplatform pour Arduino supportant les controlleurs MCP2515, SAM3X et K2X 

[dergraaf/avr-can-lib](https://github.com/dergraaf/avr-can-lib) : Universelle CAN Blibiothek (avr-can-lib), bibliothèque créée pour le robot Club eV Aachen 

[Seeed-Studio/CAN_BUS_Shield](https://github.com/Seeed-Studio/CAN_BUS_Shield) Librairies CAN pour un shield Arduino développé par Seeed-Studio, [wiki](http://www.seeedstudio.com/wiki/CAN-BUS_Shield)

###Programme
Pour utiliser les librairies arduino realisé copier les dossiers dans le dossier libraries du logiciel arduino, les codes d'exemples seront disponibles dans le menu fichier->examples

####CAN_BUS_Shield
La librairie du shield can disponible à [Seeed-Studio/CAN_BUS_Shield](https://github.com/Seeed-Studio/CAN_BUS_Shield) mais avec un dossier mis en ordre pour êtres copier dans le dossier librairies du logiciel Arduino

####GpsParser
GpsParser permet de recuperer les  trames **GPRMC** et **GPGGA** du protocole NMEA 183 d'un gps

`GPRMC_frame` structure pour avoir les principales informations d'une trame **GPRMC**
```C
typedef struct {
  char valide; 
  //latitude data
  char latInd;     //indicateur de latitude N=nord, S=sud
  char latDeg[3] = "00";  //degree from 0 to 90
  char latMn[8] = "0000000";   //minute
  
  //longitude data
  char longInd;  //indicateur de longitude E=est, W=ouest
  char longDeg[4] = "000";  //degree from 0 to 180
  char longMn[8] = "0000000";   //minute
  
  //date
  char day[3] = "00";
  char month[3] = "00";
  char year[3] = "00"; //seule les 2 dernier chiffres de l'annee
  
  //time utc
  char hour[3] = "00";
  char minute[3] = "00";
  char second[3] = "00";
  
  char speed[6] = "00000"; //vitesse en noeud
  }GPRMC_frame;
```

`GPRMC_data` structure pour avoir les principales valeurs numérique d'une trame **GPRMC**
```C
typedef struct {
  bool valide; 
  //latitude data
  float latitude=0.0;
  
  //longitude data
  float longitude=0.0;
  
  //date
  unsigned char day = 0;
  unsigned char month = 0;
  unsigned char year = 0;
  
  //time utc
  unsigned char hour= 0;
  unsigned char minute = 0;
  unsigned char second= 0;
  
  float speed = 0.0; //vitesse en noeud
  }GPRMC_data;
```

`GPGGA_frame` structure pour avoir les principales valeurs d'une trame **GPGGA**
```C
  typedef struct {
  char valide; 
  //latitude data
  char latInd;     //indicateur de latitude N=nord, S=sud
  char latDeg[3] = "00";  //degree from 0 to 90
  char latMn[8] = "0000000";   //minute
  
  //longitude data
  char longInd;  //indicateur de longitude E=est, W=ouest
  char longDeg[4] = "000";  //degree from 0 to 180
  char longMn[8] = "0000000";   //minute
  
  //time utc
  char hour[3] = "00";
  char minute[3] = "00";
  char second[3] = "00";
  
  char nbSat[3] = "00"; //Satellites are in view
  char accuracy[4] = "000"; //Relative accuracy of horizontal position
  
  char altitude[6] = "00000"; // altitude above mean sea level
  char altitudeUnite; // altitude unite mesure (meter)
  
  }GPGGA_frame;
```

fonction pour recupérer d'une trame NMEA un champ spécifique
```C
void getNemaField(const char buffIn[], char field[], const unsigned char fieldNb); 
//buffIn la trame NMEA
//field le champ récupérer
//fieldNb la position dans la trame GPRMC du champ que l'on veut récupérer
```

fonction qui test si la trame est une trame **GPRMC**
```C
boolean isGPRMC(const char buffer[]);
//buffer la trame NMEA
```

fonction pour recupérer d'une trame NMEA une structure `GPRMC_frame`
```C
void parseGPRMC(const char buffer[], GPRMC_frame *data);
```

fonction pour converture une structure `GPRMC_frame` en structure `GPRMC_data`
```C
void convertGprmcFrame(GPRMC_frame *frame, GPRMC_data *data);
```

fonction qui test si la trame est une trame **GPGGA**
```C
boolean isGPGGA(const char buffer[]);
```

fonction pour recupérer d'une trame NMEA une structure `GPGGA_frame`
```C
void parseGPGGA(const char buffer[], GPGGA_frame *data);
```

####ParseCan
ParseCan contient plusieurs identifiants pour des message CAN et contient des fonctions pour convertir les `int` et les `float` en tableau de `unsigned char` et inversement pour envoyer ces données et les lires sur le bus CAN

liste des identifiants actuellement implémenter
```C
#define MSG_GPRMC_LAT_LONG		0x40 //identifiant pour une trame avec la latitude et la longitude
#define MSG_GPRMC_VIT_DATE		0x41 //identifiant pour une trame avec la vitesse et la date_order
#define MSG_GPGGA_ALT_PREC		0x42 //identifiant pour une trame avec l'altitude et la precision
#define MSG_IMU_PHI_THETA_PSI 	0x43 //identifiant pour une trame avec Roll, pitch and yaw
#define MSG_GYRO_X_Y_Z 			0x44 //identifiant avec angular rates relative to the axes X, Y and Z, respectively. 

#define MSG_test	0xFE	// un message de teste
```

fonction pour enregistrer un `int` dans un tableau de `unsigned char`
```C
int ucharToInt(unsigned char buff[], int offset);
//buff tableau de char
// offset position du msb
```

fonction pour enregistrer un `float` dans un tableau de `unsigned char`
```C
float ucharToFloat(unsigned char buff[], int offset);
//buff tableau de char
// offset position du msb
```

fonction pour récupérer un `int` d'un tableau de `unsigned char`
```C
void intToUChar(unsigned char buff[], int offset, int val);
//buff tableau de char
// offset position du msb
// val entier à convertir
```

fonction pour récupérer un `float` d'un tableau de `unsigned char`
```C
void floatToUChar(unsigned char buff[], int offset, float val);
//buff tableau de char
// offset position du msb
// val floatant à convertir
```