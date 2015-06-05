/**
	Romain Le Forestier
 parser pour nema gps data
*/

#include "gps_data_parser.h"

//parse a gprmc sentence
	void GPS_PARSER::parseGPRMC(const unsigned char buffer[], GPRMC_frame *gprmc)
	{
		unsigned char sentencePos = 0;
		unsigned char fieldPos = 0;
		unsigned char commaCount = 0;
		
		//on teste si on recois une trame correct pour eviter de boucler sur une tram qui ne 
		//correspond pas a celle du gprmc
		if(!isGPRMC(buffer))
		{
			return;
		}
		
		while (sentencePos < NMEALenght)
		{
			if (buffer[sentencePos] == ',')
			{
			  commaCount ++;
			  sentencePos ++;
			  fieldPos = 0;
			}
			
			switch(commaCount)
			{
				case 1: //heure fixe
					if(fieldPos < 2)
					{
						gprmc->hour[fieldPos]= buffer[sentencePos];
					}
					else
					{
						if(fieldPos < 4)
						{
							gprmc->minute[fieldPos]= buffer[sentencePos];
						}
						else
						{
							if(fieldPos < 6)
							{
								gprmc->second[fieldPos]= buffer[sentencePos];
							}
						}
					}
				break;
				case 2: //validite signal
					if(fieldPos < 1)
					{
						gprmc->valide= buffer[sentencePos];
					}
				break;
				case 3: //latitude
					if(fieldPos < 2)
					{
						gprmc->latDeg[fieldPos]= buffer[sentencePos];
					}
					else
					{
						if(fieldPos < 9)
						{
							gprmc->latMn[fieldPos]= buffer[sentencePos];
						}
					}
				break;
				case 4: //indicateur latitude
					if(fieldPos < 1)
					{
						gprmc->latInd = buffer[sentencePos];
					}
				break;
				case 5: //latitude
					if(fieldPos < 3)
					{
						gprmc->longDeg[fieldPos]= buffer[sentencePos];
					}
					else
					{
						if(fieldPos < 10)
						{
							gprmc->longMn[fieldPos]= buffer[sentencePos];
						}
					}
				break;
				case 6: //indicateur longitude
					if(fieldPos < 1)
					{
						gprmc->longInd = buffer[sentencePos];
					}
				break;
				case 7: //vitesse en noeud
					if(fieldPos < 5)
					{
						gprmc->speed[fieldPos] = buffer[sentencePos];
					}
				break;
				case 9: //Date du fix
					if(fieldPos < 2)
					{
						gprmc->day[fieldPos]= buffer[sentencePos];
					}
					else
					{
						if(fieldPos < 4)
						{
							gprmc->month[fieldPos]= buffer[sentencePos];
						}
						else
						{
							if(fieldPos < 6)
							{
								gprmc->year[fieldPos]= buffer[sentencePos];
							}
						}
					}
				break;
				default:break;
			}
			fieldPos ++;
			sentencePos ++;
			//si l'on a récuperer toute les donners qui nous intéresse, on sort de la boucle
			if(commaCount > 9)
			{
				break;
			}
		}
	}

//parse a gpgga sentence
	void GPS_PARSER::parseGPGGA(const unsigned char buffer[], GPGGA_frame *gpgga)
	{
		unsigned char sentencePos = 0;
		unsigned char fieldPos = 0;
		unsigned char commaCount = 0;
                unsigned char field[20];
		
		//on teste si on recois une trame correct pour eviter de boucler sur une tram qui ne 
		//correspond pas a celle du gpgga
		if(!isGPGGA(buffer))
		{
			return;
		}
		
		while (sentencePos < NMEALenght)
		{
			if (buffer[sentencePos] == ',')
			{
			  commaCount ++;
			  sentencePos ++;
			  fieldPos = 0;
			}
			
			switch(commaCount)
			{
				case 1: //heure fixe
					if(fieldPos < 2)
					{
						gpgga->hour[fieldPos]= buffer[sentencePos];
					}
					else
					{
						if(fieldPos < 4)
						{
							gpgga->minute[fieldPos]= buffer[sentencePos];
						}
						else
						{
							if(fieldPos < 6)
							{
								gpgga->second[fieldPos]= buffer[sentencePos];
							}
						}
					}
				break;
				case 2: //latitude
					if(fieldPos < 2)
					{
						gpgga->latDeg[fieldPos]= buffer[sentencePos];
					}
					else
					{
						if(fieldPos < 9)
						{
							gpgga->latMn[fieldPos]= buffer[sentencePos];
						}
					}
				break;
				case 3: //indicateur latitude
					if(fieldPos < 1)
					{
						gpgga->latInd = buffer[sentencePos];
					}
				break;
				case 4: //latitude
					if(fieldPos < 3)
					{
						gpgga->longDeg[fieldPos]= buffer[sentencePos];
					}
					else
					{
						if(fieldPos < 10)
						{
							gpgga->longMn[fieldPos]= buffer[sentencePos];
						}
					}
				break;
				case 5: //indicateur longitude
					if(fieldPos < 1)
					{
						gpgga->longInd = buffer[sentencePos];
					}
				break;
				case 7: //Nombre de satellites
					if(fieldPos < 2)
					{
						gpgga->nbSat[fieldPos] = buffer[sentencePos];
					}
				break;
				case 8: //Précision horizontale
					if(fieldPos < 3)
					{
						gpgga->accuracy[fieldPos] = buffer[sentencePos];
					}
				break;
				case 9: //Altitude
					if(fieldPos < 5)
					{
						gpgga->altitude[fieldPos]  = buffer[sentencePos];
					}
				break;
				case 10: //altitude unite mesure
					if(fieldPos < 1)
					{
						gpgga->altitudeUnite = buffer[sentencePos];
					}
				break;
				default:break;
			}
			fieldPos ++;
			sentencePos ++;
			//si l'on a récuperer toute les donners qui nous intéresse, on sort de la boucle
			if(commaCount > 9)
			{
				break;
			}
		}
	}
		
// get the field number from NMEA sentence
	void GPS_PARSER::getNemaField(const unsigned char buffIn[], unsigned char field[], const unsigned char fieldNb)
	{
		unsigned char sentencePos = 0;
		unsigned char fieldPos = 0;
		unsigned char commaCount = 0;
		while (sentencePos < NMEALenght && commaCount > fieldNb)
		{
			if (buffIn[sentencePos] == ',')
			{
			  commaCount ++;
			  sentencePos ++;
			}
			if (commaCount == fieldNb)
			{
			  field[fieldPos] = buffIn[sentencePos];
			  fieldPos ++;
			}
			sentencePos ++;
		}
		field[fieldPos] = '\0';
	}

//test if data buffer is nmea gprmc
	boolean GPS_PARSER::isGPRMC(const unsigned char buffer[])
	{
		unsigned char field[10];
                unsigned char str[] = "$GPRMC";
                unsigned char i = 0;
                boolean test = true;
		getNemaField(buffer,field, 0);
                while(i < 6)
                {
                  if(field[i] != str[i])
                   {
                     test = false;
                     break;  
                   }
                  i++;  
                }
		return test;
	}
		
//test if data buffer is nmea gprmc
	boolean GPS_PARSER::isGPGGA(const unsigned char buffer[])
	{
		unsigned char field[10];
                unsigned char str[] = "$GPGGA";
                unsigned char i = 0;
                boolean test = true;
		getNemaField(buffer,field, 0);
                while(i < 6)
                {
                  if(field[i] != str[i])
                   {
                     test = false;
                     break;  
                   }
                  i++;  
                }
		return test;
	}
