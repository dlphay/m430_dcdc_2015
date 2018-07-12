/*
xing hao :INA168
50mOhm   150KOhm  

U:  0--0.782V    I: 0--2.53A
Umax: 3.3V-----Imax:10.68A

*/

#include "MSP430X16X.H"
#include "CURRENTSP_YDS.H"

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

ulong  Current_Value;
ulong  Current_dispose;
uint   CCCCC;

ulong  CurrentSPina168(ulong Current_value) 
{
  Current_Value = Current_value;
  //chu li  hanshu 
  dispose();
  return  Current_dispose;
}
ulong  CurrentSPina282(ulong Current_value) 
{
  Current_Value =(ulong)(1.0895*Current_value);
  //chu li  hanshu 
  //dispose();
  return  Current_Value;
}
void dispose(void) 
{
if( Current_Value <= 467 )           CCCCC = 0;
if( 467 < Current_Value <= 1224 )    CCCCC = 1;
if( 1224 < Current_Value <= 1289 )   CCCCC = 2;
if( 1289 < Current_Value <= 1400 )   CCCCC = 3;
if( 1400 < Current_Value <= 1514 )   CCCCC = 4;
if( 1514 < Current_Value <= 1627 )   CCCCC = 5;
if( 1627 < Current_Value <= 1750 )   CCCCC = 6;
if( 1750 < Current_Value <= 1869 )   CCCCC = 7;
if( 1869 < Current_Value <= 1985 )   CCCCC = 8;
if( 1985 < Current_Value <= 2115 )   CCCCC = 9;
if( 2115 < Current_Value <= 2235 )   CCCCC = 10;
if( 2235 < Current_Value <= 2370 )   CCCCC = 11;
if( 2370 < Current_Value <= 2470 )   CCCCC = 12;
if( 2470 < Current_Value <= 2598 )   CCCCC = 13;
if( 2598 < Current_Value <= 2695 )   CCCCC = 14;
if( 2695 < Current_Value <= 2827 )   CCCCC = 15;
if( 2827 < Current_Value <= 2940 )   CCCCC = 16;
if( 2940 < Current_Value <= 3053 )   CCCCC = 17;
if( 3053 < Current_Value <= 3194 )   CCCCC = 18;
if( 3194 < Current_Value <= 3351 )   CCCCC = 19;
if( 3351 < Current_Value <= 3484 )   CCCCC = 20;
if( 3484 < Current_Value <= 3681 )   CCCCC = 21;
if( 3681 < Current_Value <= 4016 )   CCCCC = 22;
if( 4016 < Current_Value <= 4300 )   CCCCC = 23;
if( 4300 < Current_Value <= 4608 )   CCCCC = 24;
if( 4608 < Current_Value <= 4874 )   CCCCC = 25;
if( 4874 < Current_Value <= 5265 )   CCCCC = 26;
if( 5265 < Current_Value <= 5610 )   CCCCC = 27;
if( 5610 < Current_Value <= 5860 )   CCCCC = 28;
if( 5860 < Current_Value <= 6200 )   CCCCC = 29;
if( 6200 < Current_Value <= 7017 )   CCCCC = 30;
if( 7017 < Current_Value <= 7820 )   CCCCC = 31;
if( 7017 < Current_Value )           CCCCC = 32;

switch (CCCCC) 
{
case 0:    Current_dispose =(ulong)(2.000*Current_Value);   break; 
case 1:    Current_dispose =(ulong)(2.214*Current_Value);   break;
case 2:    Current_dispose =(ulong)(2.307*Current_Value);   break;
case 3:    Current_dispose =(ulong)(2.378*Current_Value);   break;
case 4:    Current_dispose =(ulong)(2.469*Current_Value);   break;
case 5:    Current_dispose =(ulong)(2.546*Current_Value);   break;
case 6:    Current_dispose =(ulong)(2.605*Current_Value);   break;
case 7:    Current_dispose =(ulong)(2.652*Current_Value);   break;
case 8:    Current_dispose =(ulong)(2.698*Current_Value);   break;
case 9:    Current_dispose =(ulong)(2.731*Current_Value);   break;
case 10:   Current_dispose =(ulong)(2.758*Current_Value);   break;
case 11:   Current_dispose =(ulong)(2.779*Current_Value);   break;
case 12:   Current_dispose =(ulong)(2.809*Current_Value);   break;
case 13:   Current_dispose =(ulong)(2.841*Current_Value);   break;
case 14:   Current_dispose =(ulong)(2.871*Current_Value);   break;
case 15:   Current_dispose =(ulong)(2.897*Current_Value);   break;
case 16:   Current_dispose =(ulong)(2.913*Current_Value);   break;
case 17:   Current_dispose =(ulong)(2.937*Current_Value);   break;
case 18:   Current_dispose =(ulong)(2.961*Current_Value);   break;
case 19:   Current_dispose =(ulong)(2.979*Current_Value);   break;
case 20:   Current_dispose =(ulong)(2.999*Current_Value);   break;
case 21:   Current_dispose =(ulong)(3.015*Current_Value);   break;
case 22:   Current_dispose =(ulong)(3.039*Current_Value);   break;
case 23:   Current_dispose =(ulong)(3.066*Current_Value);   break;
case 24:   Current_dispose =(ulong)(3.087*Current_Value);   break;
case 25:   Current_dispose =(ulong)(3.111*Current_Value);   break;
case 26:   Current_dispose =(ulong)(3.126*Current_Value);   break;
case 27:   Current_dispose =(ulong)(3.144*Current_Value);   break;
case 28:   Current_dispose =(ulong)(3.165*Current_Value);   break;
case 29:   Current_dispose =(ulong)(3.176*Current_Value);   break;
case 30:   Current_dispose =(ulong)(3.192*Current_Value);   break;
case 31:   Current_dispose =(ulong)(3.221*Current_Value);   break;
case 32:   Current_dispose =(ulong)(3.0*Current_Value);     break;
}
}
