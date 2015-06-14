/**
	Romain Le Forestier
 parser pour nema gps data
*/

#include <stdlib.h>
#include "gps_parser.h"

GPS_PARSER::GPS_PARSER(boolean init)
{
  init = init;
  return;
}

//parse a gprmc sentence
	void GPS_PARSER::parseGPRMC(const char buffer[], GPRMC_frame *gprmc)
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
		
		while (sentencePos < NMEALenght && buffer[sentencePos] != '\n')
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
	void GPS_PARSER::parseGPGGA(const char buffer[], GPGGA_frame *gpgga)
	{
		unsigned char sentencePos = 0;
		unsigned char fieldPos = 0;
		unsigned char commaCount = 0;
		
		//on teste si on recois une trame correct pour eviter de boucler sur une tram qui ne 
		//correspond pas a celle du gpgga
		if(!isGPGGA(buffer))
		{
			return;
		}
		
		while (sentencePos < NMEALenght && buffer[sentencePos] != '\n')
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
	void GPS_PARSER::getNemaField(const char buffIn[], char field[], const unsigned char fieldNb)
	{
		unsigned char sentencePos = 0;
		unsigned char fieldPos = 0;
		unsigned char commaCount = 0;
		while (sentencePos < NMEALenght && commaCount > fieldNb && buffIn[sentencePos] != '\n')
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
	boolean GPS_PARSER::isGPRMC(const char buffer[])
	{
              char temp[7];
              for(int i =0; i < 6; i++)
              {
                temp[i] = buffer[i];
              }
              temp[6] = '\0';
		return (strcmp(temp,"$GPRMC")==0);
	}
		
//test if data buffer is nmea gprmc
	boolean GPS_PARSER::isGPGGA(const char buffer[])
	{
              char temp[7];
              for(int i =0; i < 6; i++)
              {
                temp[i] = buffer[i];
              }
              temp[6] = '\0';
		return (strcmp(temp,"$GPGGA")==0);
	}

void convertGprmcFrame(GPRMC_frame *frame, GPRMC_data *data)
{
	float degree;
	float minute;
	//si les donnees ne sont pas valide on quite la fonction, les valeur par defaut de data étant a 0
	if(! (data->valide = (frame->valide == 'A')))
		return;
	
	degree = atof (frame->latDeg);
	minute = atof (frame->latMn);
	data->latitude = (frame->latInd == 'N' ? degree + minute/60.0 : 0 - (degree + minute/60));
	
	degree = atof (frame->longDeg);
	minute = atof (frame->longMn);
	data->latitude = (frame->longInd == 'E' ? degree + minute/60.0 : 0 - (degree + minute/60)); 
	//date
	data->day = atoi(frame->day);
	data->month = atoi(frame->month);
	data->year = atoi(frame->year);
  
  //time utc
	data->hour = atoi(frame->hour);
	data->minute = atoi(frame->minute);
	data->second = atoi(frame->second);
  //vittesse en noeud
	data->speed = atof(frame->speed);
	
	return;
}