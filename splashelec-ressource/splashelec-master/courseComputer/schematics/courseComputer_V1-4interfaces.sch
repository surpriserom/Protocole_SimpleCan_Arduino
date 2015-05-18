v 20110115 2
T 43500 36000 9 10 1 0 0 0 1
course computer: 4. interfaces
T 47600 35400 9 10 1 0 0 0 1
bernt.weber@splashelec.com
T 48500 35700 9 10 1 0 0 0 1
2010-09-16
C 27400 35100 0 0 0 title-bordered-A2.sym
T 47600 35700 9 10 1 0 0 0 1
V1
T 31300 23500 8 10 0 1 0 0 1
device=HEADER6
T 43600 35400 9 10 1 0 0 0 1
4
T 45100 35400 9 10 1 0 0 0 1
5
T 43500 36400 9 10 1 0 0 0 1
Splashelec
N 33300 39800 32500 39800 4
N 32500 39000 32500 39800 4
N 32500 39000 34700 39000 4
N 34700 39000 34700 40000 4
N 34300 40000 35800 40000 4
{
T 35400 39800 5 10 1 1 0 0 1
netname=pot1
}
C 35100 41200 1 0 0 5V-plus-1.sym
C 35400 40200 1 90 0 resistor-2.sym
{
T 35100 40200 5 10 1 1 90 0 1
refdes=R416
T 35100 40800 5 10 1 1 90 0 1
value=10k
T 35400 40200 5 10 0 0 90 0 1
footprint=0603
}
N 35300 41200 35300 41100 4
N 35300 40200 35300 40000 4
C 33700 39200 1 0 0 gnd-1.sym
N 33800 39500 33800 39600 4
N 30900 40200 33300 40200 4
N 31700 40100 31700 40200 4
C 33200 41300 1 180 0 BAT721S-1.sym
{
T 32878 39328 5 10 0 0 180 0 1
device=DIODE SCHOTTKY DOUBLE
T 32400 41600 5 10 1 1 180 0 1
refdes=D407
T 32859 39168 5 10 0 1 180 0 1
footprint=SOT23
T 32833 39485 5 10 0 0 180 0 1
value=BAT721S
}
C 33100 40700 1 0 0 gnd-1.sym
N 33200 41000 33200 41100 4
N 32400 40800 32400 40200 4
N 33300 37000 32500 37000 4
N 32500 36200 32500 37000 4
N 32500 36200 34700 36200 4
N 34700 36200 34700 37200 4
N 34300 37200 35800 37200 4
{
T 35400 37000 5 10 1 1 0 0 1
netname=pot2
}
C 35100 38400 1 0 0 5V-plus-1.sym
C 35400 37400 1 90 0 resistor-2.sym
{
T 35100 37400 5 10 1 1 90 0 1
refdes=R420
T 35100 38000 5 10 1 1 90 0 1
value=10k
T 35400 37400 5 10 0 0 90 0 1
footprint=0603
}
N 35300 38400 35300 38300 4
N 35300 37400 35300 37200 4
C 33700 36400 1 0 0 gnd-1.sym
N 33800 36700 33800 36800 4
N 30900 37400 33300 37400 4
N 31700 37300 31700 37400 4
C 33100 37700 1 0 0 gnd-1.sym
N 33200 38000 33200 38100 4
N 32400 37800 32400 37400 4
C 31400 41200 1 0 0 5V-plus-1.sym
N 31600 41200 31600 41100 4
C 33600 40500 1 0 0 5V-plus-1.sym
N 33800 40500 33800 40400 4
C 33600 37700 1 0 0 5V-plus-1.sym
N 33800 37700 33800 37600 4
C 31600 38800 1 0 0 gnd-1.sym
N 31700 39100 31700 39200 4
C 31600 36000 1 0 0 gnd-1.sym
N 31700 36300 31700 36400 4
C 33200 38300 1 180 0 BAT721S-1.sym
{
T 32878 36328 5 10 0 0 180 0 1
device=DIODE SCHOTTKY DOUBLE
T 32400 38600 5 10 1 1 180 0 1
refdes=D409
T 32859 36168 5 10 0 1 180 0 1
footprint=SOT23
T 32833 36485 5 10 0 0 180 0 1
value=BAT721S
}
T 42500 50200 9 10 1 0 0 0 4
Switch usage examples:
- limit switches
- buttons
- speed in
C 46400 49900 1 0 0 resistor-2.sym
{
T 46900 49600 5 10 1 1 0 0 1
refdes=R401
T 46400 49600 5 10 1 1 0 0 1
value=100k
T 46400 49900 5 10 0 0 0 0 1
footprint=0603_SE
}
N 47700 49900 47700 50000 4
N 48400 50400 48400 50000 4
C 47600 48600 1 0 0 gnd-1.sym
N 47700 48900 47700 49000 4
N 47300 50000 49300 50000 4
{
T 49200 49800 5 10 1 1 0 0 1
comment=switch1
T 48700 49800 5 10 1 1 0 0 1
netname=MOSI
}
N 46400 50000 45500 50000 4
N 31600 38200 31600 38100 4
C 31400 38200 1 0 0 5V-plus-1.sym
C 49100 50300 1 0 0 gnd-1.sym
N 49200 50600 49200 50700 4
C 49200 50900 1 180 0 BAT721S-1.sym
{
T 48878 48928 5 10 0 0 180 0 1
device=DIODE SCHOTTKY DOUBLE
T 47900 51200 5 10 1 1 0 0 1
refdes=D401
T 48859 48768 5 10 0 1 180 0 1
footprint=SOT23
T 47902 51000 5 10 1 1 0 0 1
value=BAT721S
}
N 47600 50800 47600 50700 4
C 47400 50800 1 0 0 5V-plus-1.sym
C 46200 49000 1 90 0 resistor-2.sym
{
T 45900 49000 5 10 1 1 90 0 1
refdes=R402
T 45900 49600 5 10 1 1 90 0 1
value=10k
T 46200 49000 5 10 0 0 90 0 1
footprint=0603_SE
}
C 31900 39200 1 90 0 capacitor-1.sym
{
T 31500 39200 5 10 1 1 90 0 1
refdes=C408
T 31200 39400 5 10 0 0 90 0 1
device=CAPACITOR
T 31000 39400 5 10 0 0 90 0 1
symversion=0.1
T 32100 39200 5 10 1 1 90 0 1
value=100nF X5R
T 31900 39200 5 10 0 0 0 0 1
footprint=0603_SE
T 31900 39200 5 10 0 0 0 0 1
comment=multilayer ceramic Y5V/X5R/X7R
}
C 36000 43600 1 90 0 resistor-2.sym
{
T 35700 43600 5 10 1 1 90 0 1
refdes=R412
T 35700 44100 5 10 1 1 90 0 1
value=10R
T 36000 43600 5 10 0 0 90 0 1
footprint=0603
}
N 35900 44700 35900 44500 4
N 35900 44600 35700 44600 4
C 35700 44100 1 0 1 BC847C.sym
{
T 34800 44600 5 10 0 0 0 6 1
device=NPN_TRANSISTOR
T 34900 45000 5 10 1 1 90 6 1
refdes=Q402
T 34800 44400 5 10 0 0 0 6 1
footprint=SOT23
T 34900 44400 5 10 1 1 90 6 1
value=BC847C
}
N 34800 45200 35300 45200 4
N 35100 45200 35100 45100 4
N 35100 43400 35100 44100 4
N 35100 43500 35900 43500 4
N 35900 43600 35900 43500 4
C 36000 48000 1 90 0 resistor-2.sym
{
T 35700 48100 5 10 1 1 90 0 1
refdes=R403
T 35700 48600 5 10 1 1 90 0 1
value=10k
T 36000 48000 5 10 0 0 90 0 1
footprint=0603
}
T 36100 43800 9 10 1 0 0 0 2
limit to 
60 mA
N 29100 47000 31200 47000 4
T 36500 44700 9 10 1 0 0 0 5
min 0.5 W
(for case of 
marine_bus
@ 15 V 
@ 50 % duty cycle)
C 36100 47800 1 90 1 BAT721S-1.sym
{
T 34128 47478 5 10 0 0 270 2 1
device=DIODE SCHOTTKY DOUBLE
T 36400 47000 5 10 1 1 270 2 1
refdes=D404
T 33968 47459 5 10 0 1 270 2 1
footprint=SOT23
T 34285 47433 5 10 0 0 270 2 1
value=BAT721S
}
N 35900 45700 35900 46200 4
N 28700 49100 31200 49100 4
N 35900 48900 35900 49100 4
C 35000 43100 1 0 0 gnd-1.sym
N 28700 43500 31200 43500 4
{
T 29100 43600 5 10 1 1 0 0 1
netname=GND_in
}
C 33900 45100 1 0 0 resistor-2.sym
{
T 34400 45400 5 10 1 1 0 0 1
refdes=R409
T 34000 45400 5 10 1 1 0 0 1
value=10k
T 33900 45100 5 10 0 0 0 0 1
footprint=0603_SE
}
C 39900 46200 1 0 0 LM397-1.sym
{
T 40800 45600 5 10 1 1 90 0 1
value=LM397MF
T 40600 46800 5 10 1 1 0 0 1
refdes=U401
T 40600 47600 5 10 0 0 0 0 1
symversion=0.1
T 39900 46200 5 10 0 1 0 0 1
footprint=SOT235_SE
T 40600 47000 5 10 0 0 0 0 1
device=LM397
}
N 37700 46800 39900 46800 4
C 40300 45800 1 0 0 gnd-1.sym
N 40400 46100 40400 46200 4
C 40200 47100 1 0 0 5V-plus-1.sym
N 40400 47100 40400 47000 4
C 41200 47900 1 0 0 5V-plus-1.sym
C 41500 46900 1 90 0 resistor-2.sym
{
T 41200 46900 5 10 1 1 90 0 1
refdes=R405
T 41200 47500 5 10 1 1 90 0 1
value=4.7k
T 41500 46900 5 10 0 0 90 0 1
footprint=0603
}
N 41400 47900 41400 47800 4
N 41400 46900 41400 46600 4
N 40900 46600 42300 46600 4
{
T 41200 46300 5 10 1 1 0 0 1
netname=comBus_rx
}
C 39400 45100 1 90 0 resistor-2.sym
{
T 39100 45100 5 10 1 1 90 0 1
refdes=R410
T 39100 45600 5 10 1 1 90 0 1
value=100k
T 39400 45100 5 10 0 0 90 0 1
footprint=0603
}
N 39300 44900 39300 45100 4
N 39300 43900 39300 44000 4
N 39300 46000 39300 46200 4
C 39100 46200 1 0 0 5V-plus-1.sym
C 39200 43600 1 0 0 gnd-1.sym
T 38800 44200 9 10 1 0 90 0 1
threshhold = 2.5 V
N 39300 45000 39900 45000 4
N 39900 45000 39900 46400 4
C 39400 44000 1 90 0 resistor-2.sym
{
T 39100 44000 5 10 1 1 90 0 1
refdes=R411
T 39100 44500 5 10 1 1 90 0 1
value=100k
T 39400 44000 5 10 0 0 90 0 1
footprint=0603
}
N 38200 48100 38200 46800 4
C 38900 48000 1 0 0 gnd-1.sym
N 39000 48300 39000 48400 4
C 39000 48600 1 180 0 BAT721S-1.sym
{
T 38200 48900 5 10 1 1 180 0 1
refdes=D402
T 38678 46628 5 10 0 0 180 0 1
device=DIODE SCHOTTKY DOUBLE
T 38659 46468 5 10 0 1 180 0 1
footprint=SOT23
T 38633 46785 5 10 0 0 180 0 1
value=BAT721S
}
N 37400 48500 37400 48400 4
C 37200 48500 1 0 0 5V-plus-1.sym
N 37700 45700 37700 45800 4
C 37600 45400 1 0 0 gnd-1.sym
C 37800 45800 1 90 0 resistor-2.sym
{
T 37500 46000 5 10 1 1 90 0 1
refdes=R407
T 38000 46000 5 10 1 1 90 0 1
value=62k
T 37800 45800 5 10 0 0 90 0 1
footprint=0603
}
C 37800 46900 1 90 0 resistor-2.sym
{
T 37500 47100 5 10 1 1 90 0 1
refdes=R404
T 38000 47100 5 10 1 1 90 0 1
value=100k
T 37800 46900 5 10 0 0 90 0 1
footprint=0603_SE
}
N 37700 46900 37700 46700 4
N 39700 46800 39700 47100 4
N 39700 47100 38600 47100 4
{
T 38400 47200 5 10 1 1 0 0 1
netname=programming_rx
}
N 35900 47800 35900 48000 4
N 35900 47900 37700 47900 4
N 37700 47900 37700 47800 4
N 32100 49100 35900 49100 4
N 35600 47000 32100 47000 4
N 32100 43500 35100 43500 4
T 31200 46400 9 10 1 0 0 0 2
about 5 Ohms 
@ 50 kHz (9800 baud)
C 31300 44800 1 90 0 capacitor-1.sym
{
T 30600 45000 5 10 0 0 90 0 1
device=CAPACITOR
T 31000 45400 5 10 1 1 90 0 1
refdes=C404
T 30400 45000 5 10 0 0 90 0 1
symversion=0.1
T 31000 44100 5 10 1 1 90 0 1
value=100pF 100V
T 31300 44800 5 10 0 0 0 0 1
footprint=0603_SE
T 31300 44800 5 10 0 0 0 0 1
comment=multilayer ceramic X5R/X7R
}
C 31200 46900 1 0 0 inductor-1.sym
{
T 31400 47400 5 10 0 0 0 0 1
device=INDUCTOR
T 31400 47200 5 10 1 1 0 0 1
refdes=L402
T 31400 47600 5 10 0 0 0 0 1
symversion=0.1
T 31200 46800 5 10 1 1 0 0 1
value=10u/120mA
T 31200 46900 5 10 0 1 0 0 1
ref=LB2012T100KR
T 31200 46900 5 10 0 1 0 0 1
order-code=F-1463501
T 31200 46900 5 10 0 0 0 0 1
footprint=0805_SE
}
C 31200 43400 1 0 0 inductor-1.sym
{
T 31400 43900 5 10 0 0 0 0 1
device=INDUCTOR
T 31400 43700 5 10 1 1 0 0 1
refdes=L403
T 31400 44100 5 10 0 0 0 0 1
symversion=0.1
T 31200 43300 5 10 1 1 0 0 1
value=10u/120mA
T 31200 43400 5 10 0 1 0 0 1
ref=LB2012T100KR
T 31200 43400 5 10 0 1 0 0 1
order-code=F-1463501
T 31200 43400 5 10 0 0 0 0 1
footprint=0805_SE
}
N 31100 44800 31100 43500 4
N 31100 45700 31100 47000 4
C 30500 44800 1 90 0 capacitor-1.sym
{
T 29800 45000 5 10 0 0 90 0 1
device=CAPACITOR
T 30200 45400 5 10 1 1 90 0 1
refdes=C403
T 29600 45000 5 10 0 0 90 0 1
symversion=0.1
T 30200 44400 5 10 1 1 90 0 1
value=1u 100V
T 30500 44800 5 10 0 0 0 0 1
footprint=0603_SE
T 30500 44800 5 10 0 0 0 0 1
comment=multilayer ceramic X5R/X7R
}
N 30300 44800 30300 43500 4
N 30300 45700 30300 49100 4
C 33300 39600 1 0 0 FAN4174-1.sym
{
T 34200 40200 5 10 1 1 90 0 1
value=FAN4174IS5X
T 33600 40500 5 10 1 1 90 0 1
refdes=U403
T 34000 41000 5 10 0 0 0 0 1
symversion=0.1
T 33300 39600 5 10 0 0 0 0 1
footprint=SOT235_SE
}
C 33300 36800 1 0 0 FAN4174-1.sym
{
T 34200 37400 5 10 1 1 90 0 1
value=FAN4174IS5X
T 33600 37700 5 10 1 1 90 0 1
refdes=U404
T 34000 38200 5 10 0 0 0 0 1
symversion=0.1
T 33300 36800 5 10 0 0 0 0 1
footprint=SOT235_SE
}
T 38300 33300 8 10 0 0 0 0 1
device=OPAMP
T 38300 33900 8 10 0 0 0 0 1
value=LMV841MG
T 38300 34100 8 10 0 0 0 0 1
footprint=SC70_SE
N 30700 49800 30700 49100 4
N 46100 49900 46100 50000 4
N 46100 48900 46100 49000 4
C 31900 36400 1 90 0 capacitor-1.sym
{
T 31500 36400 5 10 1 1 90 0 1
refdes=C410
T 31200 36600 5 10 0 0 90 0 1
device=CAPACITOR
T 31000 36600 5 10 0 0 90 0 1
symversion=0.1
T 32100 36400 5 10 1 1 90 0 1
value=100nF X5R
T 31900 36400 5 10 0 0 0 0 1
footprint=0603_SE
T 31900 36400 5 10 0 0 0 0 1
comment=multilayer ceramic Y5V/X5R/X7R
}
C 47900 49000 1 90 0 capacitor-1.sym
{
T 47500 49000 5 10 1 1 90 0 1
refdes=C401
T 47200 49200 5 10 0 0 90 0 1
device=CAPACITOR
T 47000 49200 5 10 0 0 90 0 1
symversion=0.1
T 48100 49000 5 10 1 1 90 0 1
value=100nF X5R
T 47900 49000 5 10 0 0 0 0 1
footprint=0603_SE
T 47900 49000 5 10 0 0 0 0 1
comment=multilayer ceramic Y5V/X5R/X7R
}
N 30700 49800 32100 49800 4
{
T 30800 49900 5 10 1 1 0 0 1
netname=12V_external
}
N 45500 50400 46900 50400 4
{
T 45600 50500 5 10 1 1 0 0 1
netname=12V_external
}
N 47700 46900 47700 47000 4
N 48400 47400 48400 47000 4
C 47600 45600 1 0 0 gnd-1.sym
N 47700 45900 47700 46000 4
N 46400 47000 45500 47000 4
C 49100 47300 1 0 0 gnd-1.sym
N 49200 47600 49200 47700 4
C 49200 47900 1 180 0 BAT721S-1.sym
{
T 48878 45928 5 10 0 0 180 0 1
device=DIODE SCHOTTKY DOUBLE
T 47900 48200 5 10 1 1 0 0 1
refdes=D403
T 48859 45768 5 10 0 1 180 0 1
footprint=SOT23
T 47902 48000 5 10 1 1 0 0 1
value=BAT721S
}
N 47600 47800 47600 47700 4
C 47400 47800 1 0 0 5V-plus-1.sym
C 46200 46000 1 90 0 resistor-2.sym
{
T 45900 46000 5 10 1 1 90 0 1
refdes=R408
T 45900 46600 5 10 1 1 90 0 1
value=10k
T 46200 46000 5 10 0 0 90 0 1
footprint=0603_SE
}
N 46100 46900 46100 47000 4
N 46100 45900 46100 46000 4
C 47900 46000 1 90 0 capacitor-1.sym
{
T 47500 46000 5 10 1 1 90 0 1
refdes=C402
T 47200 46200 5 10 0 0 90 0 1
device=CAPACITOR
T 47000 46200 5 10 0 0 90 0 1
symversion=0.1
T 48100 46000 5 10 1 1 90 0 1
value=100nF X5R
T 47900 46000 5 10 0 0 0 0 1
footprint=0603_SE
T 47900 46000 5 10 0 0 0 0 1
comment=multilayer ceramic Y5V/X5R/X7R
}
N 47700 43900 47700 44000 4
N 48400 44400 48400 44000 4
C 47600 42600 1 0 0 gnd-1.sym
N 47700 42900 47700 43000 4
N 46400 44000 45500 44000 4
C 49100 44300 1 0 0 gnd-1.sym
N 49200 44600 49200 44700 4
C 49200 44900 1 180 0 BAT721S-1.sym
{
T 48878 42928 5 10 0 0 180 0 1
device=DIODE SCHOTTKY DOUBLE
T 47900 45200 5 10 1 1 0 0 1
refdes=D405
T 48859 42768 5 10 0 1 180 0 1
footprint=SOT23
T 47902 45000 5 10 1 1 0 0 1
value=BAT721S
}
N 47600 44800 47600 44700 4
C 47400 44800 1 0 0 5V-plus-1.sym
C 46200 43000 1 90 0 resistor-2.sym
{
T 45900 43000 5 10 1 1 90 0 1
refdes=R414
T 45900 43600 5 10 1 1 90 0 1
value=10k
T 46200 43000 5 10 0 0 90 0 1
footprint=0603_SE
}
N 46100 43900 46100 44000 4
N 46100 42900 46100 43000 4
C 47900 43000 1 90 0 capacitor-1.sym
{
T 47500 43000 5 10 1 1 90 0 1
refdes=C405
T 47200 43200 5 10 0 0 90 0 1
device=CAPACITOR
T 47000 43200 5 10 0 0 90 0 1
symversion=0.1
T 48100 43000 5 10 1 1 90 0 1
value=100nF X5R
T 47900 43000 5 10 0 0 0 0 1
footprint=0603_SE
T 47900 43000 5 10 0 0 0 0 1
comment=multilayer ceramic Y5V/X5R/X7R
}
N 47700 41000 47700 41100 4
N 48400 41500 48400 41100 4
C 47600 39700 1 0 0 gnd-1.sym
N 47700 40000 47700 40100 4
N 47300 41100 49300 41100 4
{
T 48700 40800 5 10 1 1 0 0 1
netname=switch4
}
N 46400 41100 45500 41100 4
C 49100 41400 1 0 0 gnd-1.sym
N 49200 41700 49200 41800 4
C 49200 42000 1 180 0 BAT721S-1.sym
{
T 48878 40028 5 10 0 0 180 0 1
device=DIODE SCHOTTKY DOUBLE
T 47900 42300 5 10 1 1 0 0 1
refdes=D406
T 48859 39868 5 10 0 1 180 0 1
footprint=SOT23
T 47902 42100 5 10 1 1 0 0 1
value=BAT721S
}
N 47600 41900 47600 41800 4
C 47400 41900 1 0 0 5V-plus-1.sym
C 46200 40100 1 90 0 resistor-2.sym
{
T 45900 40100 5 10 1 1 90 0 1
refdes=R417
T 45900 40700 5 10 1 1 90 0 1
value=10k
T 46200 40100 5 10 0 0 90 0 1
footprint=0603_SE
}
N 46100 41000 46100 41100 4
N 46100 40000 46100 40100 4
C 47900 40100 1 90 0 capacitor-1.sym
{
T 47500 40100 5 10 1 1 90 0 1
refdes=C407
T 47200 40300 5 10 0 0 90 0 1
device=CAPACITOR
T 47000 40300 5 10 0 0 90 0 1
symversion=0.1
T 48100 40100 5 10 1 1 90 0 1
value=100nF X5R
T 47900 40100 5 10 0 0 0 0 1
footprint=0603_SE
T 47900 40100 5 10 0 0 0 0 1
comment=multilayer ceramic Y5V/X5R/X7R
}
N 47700 38100 47700 38200 4
N 48400 38600 48400 38200 4
C 47600 36800 1 0 0 gnd-1.sym
N 47700 37100 47700 37200 4
N 47300 38200 49300 38200 4
{
T 48700 37900 5 10 1 1 0 0 1
netname=switch5
}
N 46400 38200 45500 38200 4
C 49100 38500 1 0 0 gnd-1.sym
N 49200 38800 49200 38900 4
C 49200 39100 1 180 0 BAT721S-1.sym
{
T 48878 37128 5 10 0 0 180 0 1
device=DIODE SCHOTTKY DOUBLE
T 47900 39400 5 10 1 1 0 0 1
refdes=D408
T 48859 36968 5 10 0 1 180 0 1
footprint=SOT23
T 47902 39200 5 10 1 1 0 0 1
value=BAT721S
}
N 47600 39000 47600 38900 4
C 47400 39000 1 0 0 5V-plus-1.sym
C 46200 37200 1 90 0 resistor-2.sym
{
T 45900 37200 5 10 1 1 90 0 1
refdes=R421
T 45900 37800 5 10 1 1 90 0 1
value=10k
T 46200 37200 5 10 0 0 90 0 1
footprint=0603_SE
}
N 46100 38100 46100 38200 4
N 46100 37100 46100 37200 4
C 47900 37200 1 90 0 capacitor-1.sym
{
T 47500 37200 5 10 1 1 90 0 1
refdes=C409
T 47200 37400 5 10 0 0 90 0 1
device=CAPACITOR
T 47000 37400 5 10 0 0 90 0 1
symversion=0.1
T 48100 37200 5 10 1 1 90 0 1
value=100nF X5R
T 47900 37200 5 10 0 0 0 0 1
footprint=0603_SE
T 47900 37200 5 10 0 0 0 0 1
comment=multilayer ceramic Y5V/X5R/X7R
}
C 46400 46900 1 0 0 resistor-2.sym
{
T 46900 46600 5 10 1 1 0 0 1
refdes=R406
T 46400 46600 5 10 1 1 0 0 1
value=100k
T 46400 46900 5 10 0 0 0 0 1
footprint=0603_SE
}
C 46400 43900 1 0 0 resistor-2.sym
{
T 46900 43600 5 10 1 1 0 0 1
refdes=R413
T 46400 43600 5 10 1 1 0 0 1
value=100k
T 46400 43900 5 10 0 0 0 0 1
footprint=0603_SE
}
C 46400 41000 1 0 0 resistor-2.sym
{
T 46900 40700 5 10 1 1 0 0 1
refdes=R415
T 46400 40700 5 10 1 1 0 0 1
value=100k
T 46400 41000 5 10 0 0 0 0 1
footprint=0603_SE
}
C 46400 38100 1 0 0 resistor-2.sym
{
T 46900 37800 5 10 1 1 0 0 1
refdes=R419
T 46400 37800 5 10 1 1 0 0 1
value=100k
T 46400 38100 5 10 0 0 0 0 1
footprint=0603_SE
}
C 30000 40100 1 0 0 resistor-2.sym
{
T 30500 39800 5 10 1 1 0 0 1
refdes=R418
T 30000 39800 5 10 1 1 0 0 1
value=100k
T 30000 40100 5 10 0 0 0 0 1
footprint=0603_SE
}
N 29500 40200 30000 40200 4
C 30000 37300 1 0 0 resistor-2.sym
{
T 30500 37000 5 10 1 1 0 0 1
refdes=R422
T 30000 37000 5 10 1 1 0 0 1
value=100k
T 30000 37300 5 10 0 0 0 0 1
footprint=0603_SE
}
N 29500 37400 30000 37400 4
T 28300 50300 9 10 1 0 0 0 3
comBus usage examples:
- internal communication between system components
- proprietary 3 wire busses used in marine electronics
T 27800 41700 9 10 1 0 0 0 4
Potentiometer input usage examples:
- actuator postition
- rudder reference
- joystick in
C 31200 49000 1 0 0 inductor-1.sym
{
T 31400 49500 5 10 0 0 0 0 1
device=INDUCTOR
T 31400 49300 5 10 1 1 0 0 1
refdes=L401
T 31400 49700 5 10 0 0 0 0 1
symversion=0.1
T 31200 48900 5 10 1 1 0 0 1
value=10u/120mA
T 31200 49000 5 10 0 1 0 0 1
ref=LB2012T100KR
T 31200 49000 5 10 0 1 0 0 1
order-code=F-1463501
T 31200 49000 5 10 0 0 0 0 1
footprint=0805_SE
}
C 35300 44700 1 0 0 2N7002K-1.sym
{
T 35400 46000 5 10 0 0 0 0 1
device=NPN_TRANSISTOR
T 35700 45600 5 10 1 1 90 0 1
refdes=Q401
T 35400 45800 5 10 0 0 0 0 1
footprint=SOT23_SE
T 35400 45300 5 10 1 1 90 0 1
value=2N7002K
T 35300 44700 5 10 0 0 0 0 1
order-code=F-1758065
}
N 32100 45200 32600 45200 4
{
T 32150 45250 5 10 1 1 0 0 1
netname=TXD
}
N 33700 45200 33900 45200 4
C 32600 44800 1 0 0 inverter_SE-1.sym
{
T 32900 45800 5 10 0 0 0 0 1
device=inverter
T 33400 45400 5 10 1 1 90 0 1
refdes=U402
T 33600 45400 5 10 1 1 90 0 1
value=74LVC1G14GW
T 32900 46000 5 10 0 0 0 0 1
footprint=SOT353_SE
}
C 33000 44400 1 0 0 gnd-1.sym
N 33100 44700 33100 44800 4
C 32900 45700 1 0 0 5V-plus-1.sym
N 33100 45700 33100 45600 4
C 36700 41200 1 0 0 gnd-1.sym
N 36800 41600 36800 41500 4
C 36600 41600 1 270 1 capacitor-1.sym
{
T 36400 42100 5 10 1 1 90 2 1
refdes=C406
T 36400 41600 5 10 1 1 90 2 1
value=100n
T 37300 41800 5 10 0 0 90 2 1
device=CAPACITOR
T 37500 41800 5 10 0 0 90 2 1
symversion=0.1
T 36600 41600 5 10 0 0 0 6 1
footprint=0603_SE
T 36600 41600 5 10 0 0 0 6 1
comment=multilayer ceramic X5R/X7R
}
N 36800 42500 36800 42700 4
C 36600 42700 1 0 0 5V-plus-1.sym
C 35700 40300 1 270 0 testpt_SE-1.sym
{
T 36100 40100 5 10 1 1 0 0 1
refdes=TP403
T 36600 39900 5 10 0 0 270 0 1
device=TESTPOINT
T 36400 39900 5 10 0 0 270 0 1
footprint=TP_SE
}
N 35600 40200 35700 40200 4
N 35600 40200 35600 40000 4
C 35700 37500 1 270 0 testpt_SE-1.sym
{
T 36100 37300 5 10 1 1 0 0 1
refdes=TP404
T 36600 37100 5 10 0 0 270 0 1
device=TESTPOINT
T 36400 37100 5 10 0 0 270 0 1
footprint=TP_SE
}
N 35600 37400 35700 37400 4
N 35600 37400 35600 37200 4
C 34900 45300 1 0 0 testpt_SE-1.sym
{
T 35100 45700 5 10 1 1 90 0 1
refdes=TP401
T 35300 46200 5 10 0 0 0 0 1
device=TESTPOINT
T 35300 46000 5 10 0 0 0 0 1
footprint=TP_SE
}
N 35000 45200 35000 45300 4
C 39600 45100 1 0 0 testpt_SE-1.sym
{
T 39800 45500 5 10 1 1 90 0 1
refdes=TP402
T 40000 46000 5 10 0 0 0 0 1
device=TESTPOINT
T 40000 45800 5 10 0 0 0 0 1
footprint=TP_SE
}
N 39700 45000 39700 45100 4
N 45500 47400 46900 47400 4
{
T 45600 47500 5 10 1 1 0 0 1
netname=12V_external
}
N 45500 44400 46900 44400 4
{
T 45600 44500 5 10 1 1 0 0 1
netname=12V_external
}
N 45500 41500 46900 41500 4
{
T 45600 41600 5 10 1 1 0 0 1
netname=12V_external
}
N 45500 38600 46900 38600 4
{
T 45600 38700 5 10 1 1 0 0 1
netname=12V_external
}
C 29500 41400 1 180 0 connector4-2.sym
{
T 29000 40100 5 10 1 1 90 0 1
refdes=pod401
T 29200 39350 5 10 0 0 180 0 1
device=CONNECTOR_4
T 29200 39150 5 10 0 0 180 0 1
footprint=universalPcbConnection4_SE
}
N 29500 41000 30900 41000 4
{
T 29600 41100 5 10 1 1 0 0 1
netname=5V_external
}
N 29500 40600 30900 40600 4
{
T 29600 40700 5 10 1 1 0 0 1
netname=12V_external
}
C 29500 38600 1 180 0 connector4-2.sym
{
T 29000 37300 5 10 1 1 90 0 1
refdes=pot401
T 29200 36550 5 10 0 0 180 0 1
device=CONNECTOR_4
T 29200 36350 5 10 0 0 180 0 1
footprint=universalPcbConnection4_SE
}
N 29500 38200 30900 38200 4
{
T 29600 38300 5 10 1 1 0 0 1
netname=5V_external
}
N 29500 37800 30900 37800 4
{
T 29600 37900 5 10 1 1 0 0 1
netname=12V_external
}
N 28700 48700 29100 48700 4
N 29100 48700 29100 47000 4
N 28700 48300 28700 43500 4
N 29600 39500 30900 39500 4
{
T 29900 39550 5 10 1 1 0 0 1
netname=GND_in
}
N 29600 39500 29600 39800 4
N 29600 39800 29500 39800 4
N 29600 36700 30900 36700 4
{
T 29900 36750 5 10 1 1 0 0 1
netname=GND_in
}
N 29600 36700 29600 37000 4
N 29600 37000 29500 37000 4
N 45500 37000 45500 37800 4
{
T 45450 37000 5 10 1 1 90 0 1
netname=GND_in
}
N 45500 39900 45500 40700 4
{
T 45450 39900 5 10 1 1 90 0 1
netname=GND_in
}
N 45500 42800 45500 43600 4
{
T 45450 42800 5 10 1 1 90 0 1
netname=GND_in
}
N 45500 45800 45500 46600 4
{
T 45450 45800 5 10 1 1 90 0 1
netname=GND_in
}
N 45500 48800 45500 49600 4
{
T 45450 48800 5 10 1 1 90 0 1
netname=GND_in
}
C 45500 50800 1 180 0 connector3-2.sym
{
T 44700 50300 5 10 1 1 90 6 1
refdes=switch401
T 45200 49150 5 10 0 0 180 0 1
device=CONNECTOR_3
T 45500 50800 5 10 0 0 0 0 1
footprint=universalPcbConnection3_SE
}
C 45500 47800 1 180 0 connector3-2.sym
{
T 44700 47300 5 10 1 1 90 6 1
refdes=switch402
T 45200 46150 5 10 0 0 180 0 1
device=CONNECTOR_3
T 45500 47800 5 10 0 0 0 0 1
footprint=universalPcbConnection3_SE
}
C 45500 44800 1 180 0 connector3-2.sym
{
T 44700 44300 5 10 1 1 90 6 1
refdes=switch403
T 45200 43150 5 10 0 0 180 0 1
device=CONNECTOR_3
T 45500 44800 5 10 0 0 0 0 1
footprint=universalPcbConnection3_SE
}
C 45500 41900 1 180 0 connector3-2.sym
{
T 44700 41400 5 10 1 1 90 6 1
refdes=switch404
T 45200 40250 5 10 0 0 180 0 1
device=CONNECTOR_3
T 45500 41900 5 10 0 0 0 0 1
footprint=universalPcbConnection3_SE
}
C 45500 39000 1 180 0 connector3-2.sym
{
T 44700 38500 5 10 1 1 90 6 1
refdes=switch405
T 45200 37350 5 10 0 0 180 0 1
device=CONNECTOR_3
T 45500 39000 5 10 0 0 0 0 1
footprint=universalPcbConnection3_SE
}
C 28700 49500 1 180 0 connector3-2.sym
{
T 27900 49000 5 10 1 1 90 6 1
refdes=comBus401
T 28400 47850 5 10 0 0 180 0 1
device=CONNECTOR_3
T 28700 49500 5 10 0 0 0 0 1
footprint=universalPcbConnection3_SE
}
N 49300 47000 47300 47000 4
{
T 49300 46800 5 10 1 1 0 1 1
comment=switch2
T 48800 46800 5 10 1 1 0 1 1
netname=MISO
}
N 49300 44000 47300 44000 4
{
T 49300 43800 5 10 1 1 0 1 1
comment=switch3
T 48800 43800 5 10 1 1 0 1 1
netname=SCK
}
N 46100 48900 45500 48900 4
N 46100 45900 45500 45900 4
N 46100 42900 45500 42900 4
N 46100 40000 45500 40000 4
N 46100 37100 45500 37100 4