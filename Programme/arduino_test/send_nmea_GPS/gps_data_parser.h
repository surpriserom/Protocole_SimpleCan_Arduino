/**
	Romain Le Forestier
 parser pour nema gps data
*/

#ifndef _GPS_PARSER_
#define _GPS_PARSER_

#include <Arduino.h>

#define NMEALenght 80 //nmea by design is 80 char max per line

/*
* $GPRMC,225446,A,4916.45,N,12311.12,W,000.5,054.7,191194,020.3,E*68
field Name -> 0 -> $GPRMC
field Heure Fixe -> 1 -> 225446 -> 22H 54mn 46s
field gps signal valide -> 2 -> A -> A = ok | V = Warning
field Latitude -> 3 -> 4916.45 -> 49 deg. 16.45 min
field -> 4 -> N -> N = north
field lognitude -> 5 -> 12311.12 -> 123 deg. 11.12 min
field -> 6 -> W -> W = west
field vitesse -> 7 -> 000.5 -> 000.5 = vitesse sol, Knots
field cap -> 8 -> 054.7 -> cap (vrai)
field date fixe -> 9 -> 191194 -> Date du fix 19 Novembre 1994
field -> 10 -> 020.3 -> Déclinaison Magnetique 20.3 deg Est
field cheksum -> 11 -> E*68 -> cheksum 68
*/
typedef struct {
  unsigned char valide; 
  //latitude data
  unsigned char latInd;     //indicateur de latitude N=nord, S=sud
  unsigned char latDeg[3] = "00";  //degree from 0 to 90
  unsigned char latMn[8] = "0000000";   //minute
  
  //longitude data
  unsigned char longInd;  //indicateur de longitude E=est, W=ouest
  unsigned char longDeg[4] = "000";  //degree from 0 to 180
  unsigned char longMn[8] = "0000000";   //minute
  
  //date
  unsigned char day[3] = "00";
  unsigned char month[3] = "00";
  unsigned char year[3] = "00"; //seule les 2 dernier chiffres de l'annee
  
  //time utc
  unsigned char hour[3] = "00";
  unsigned char minute[3] = "00";
  unsigned char second[3] = "00";
  
  unsigned char speed[6] = "00000"; //vitesse en noeud
  }GPRMC_frame;
  
/*
*  $GPGGA,123519,4807.038,N,01131.324,E,1,08,0.9,545.4,M,46.9,M, , *42
*
* 01 -> 123519 = Acquisition du FIX à 12:35:19 UTC
* 02 -> 4807.038 = Latitude 48 deg 07.038'
* 03 -> N = north
* 04 -> 01131.324 = Longitude 11 deg 31.324'
* 05 -> E = East
* 06 -> 1 = Fix qualification : (0 = non valide, 1 = Fix GPS, 2 = Fix DGPS)
* 07 -> 08 = Nombre de satellites en pousuite.
* 08 -> 0.9 = Précision horizontale ou DOP (Horizontal dilution of position) Dilution horizontale.
* 09 -> 545.4= Altitude, au dessus du MSL (mean see level) niveau moyen des Océans.
* 10 -> M = en metre
* 11 -> 46.9 = Correction de la hauteur de la géoïde en Metres par raport à l'ellipsoîde WGS84 (MSL).
* 12 -> M = en metre
* 13 -> (Champ vide) = nombre de secondes écoulées depuis la dernière mise à jour DGPS.
* 14 -> (Champ vide) = Identification de la station DGPS.
* 15 -> 42 = Checksum
*  Non représentés CR et LF.
*/
  typedef struct {
  unsigned char valide; 
  //latitude data
  unsigned char latInd;     //indicateur de latitude N=nord, S=sud
  unsigned char latDeg[3] = "00";  //degree from 0 to 90
  unsigned char latMn[8] = "0000000";   //minute
  
  //longitude data
  unsigned char longInd;  //indicateur de longitude E=est, W=ouest
  unsigned char longDeg[4] = "000";  //degree from 0 to 180
  unsigned char longMn[8] = "0000000";   //minute
  
  //time utc
  unsigned char hour[3] = "00";
  unsigned char minute[3] = "00";
  unsigned char second[3] = "00";
  
  unsigned char nbSat[3] = "00"; //Satellites are in view
  unsigned char accuracy[4] = "000"; //Relative accuracy of horizontal position
  
  unsigned char altitude[6] = "00000"; // altitude above mean sea level
  unsigned char altitudeUnite; // altitude unite mesure (meter)
  
  }GPGGA_frame;


class GPS_PARSER
{
	public:
		void parseGPRMC(const unsigned char buffer[], GPRMC_frame *data); //parse a gprmc sentence
		void parseGPGGA(const unsigned char buffer[], GPGGA_frame *data);	//parse a gpgga sentence
		void getNemaField(const unsigned char buffIn[], unsigned char field[], const unsigned char fieldNb); // get the field number from NMEA sentence
		boolean isGPRMC(const unsigned char buffer[]);
		boolean isGPGGA(const unsigned char buffer[]);
};

#endif
