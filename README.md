##Protocole SimpleCAN pour bus à base d'Arduino
###Description 
Le projet a pour objectif de définir une sur couche du protocole CAN, appelée SimpleCAN, pour faire communiquer entre-eux un ensemble de noeuds composés de cartes Arduino associées à une interface CAN.
L'approche devra être validée, au travers d'une application simple de visualisation et d'envoi de données via un PC, sur un matériel existant consistant en 5 noeuds : un permettant une connexion PC via USB, 
un destiné au décodage de données propriétaires SeaTalk (Raymarine), deux destinés à du traitement de données NMEA (issues d'un GPS et d'une centrale Tactick) et le dernier portant une centrale inertielle.

###based on splashelec project 
see splashelec [wiki](http://wiki.splashelec.com/) or [github](https://github.com/splashelec/splashelec) 

#### github can source 
from [McNeight/CAN-Library](https://github.com/McNeight/CAN-Library) for Multiplatform CAN library for Arduino supporting the MCP2515, SAM3X, and K2X controllers 
and [dergraaf/avr-can-lib](https://github.com/dergraaf/avr-can-lib) for Universelle CAN Blibiothek (avr-can-lib)
