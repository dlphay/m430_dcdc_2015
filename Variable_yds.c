


#include  "msp430x16x.h"
#include  "Variable_yds.h"

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long



uint   SampleResults0[128];  
uint   SampleResults1[128];
uint   SampleResults2[128];
uint   SampleResults3[128];
uint   SampleResults4[128];
uint   SampleResults5[128];

ulong   Average_SampleResults2=0;
ulong   Average_SampleResults3=0;
ulong   Average_SampleResults4=0;
ulong   Average_SampleResults0=0;
uint    Average_Count2 = 0;
uint    Average_Count3 = 0;
uint    Average_Count4 = 0;
uint    Average_Count0 = 0;
uint    Current_Lvbo_Count = 0;

uint   RobustResults[16];  
  
uint   DisposeDataA0 = 0;
uint   DisposeDataA1 = 0;
uint   DisposeDataA2 = 0;
uint   DisposeDataA3 = 0;
int    DisposeDataB0 = 0;
int    DisposeDataB1 = 0;
int    DisposeDataB2 = 0; 
uint  AAAAA =1;
int  Effi =0;
uint  Efficiency_SHUZU[5];
extern float   RatioYds0 = 0,RatioYds1 = 0,RatioYds2 = 0,RatioYds3 = 0;
uchar Figure[10] ={'0','1','2','3','4','5','6','7','8','9'};
int  CURRENT[11] = {10000,11000,12000,13000,14000,15000,16000,17000,18000,19000,20000};
uint CURRENT_DADATA[11] ={0x5DC,0X674,0x709,0x7a2,0x835,0X8CB,0x961,0x9f5,0xa8B,0xb1E,0Xbb2};
uint CURRENT_PIDZD[11]  ={0x5DC,0X674,0x709,0x7a2,0x835,0X8CB,0x961,0x9f5,0xa8B,0xb1E,0Xbb2};
uint VOLTAGE_DADATA = 0xc10;
uint VOLTAGE_PIDZD = 0xc10;
uint CURRENT_Mode2 = 0;
int CURRENT_Mode2_PIDZD = 1;
uint Free_ModeSet = 0;
uint Free_ModeSetA = 0;
uint Free_ModeSetB = 0;
//float Current_One = 0,Current_Two = 0,Voltage_One =0,Voltage_Two =0;


