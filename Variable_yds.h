#ifndef __VARIABLE_YDS_H__
#define __VARIABLE_YDS_H__
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long
#define  Pid_DeadBand    18
#define  Addata_Margin    18
extern  int    PID_ZD[7] ;
extern  int    BUJIN_pwm[7];
extern  int    BUJIN_addata[7];
extern  int    BUJIN[8];
extern  uint    Count ;
extern  uint    SampleResults0[128] ;
extern  uint    SampleResults1[128] ;
extern  uint    SampleResults2[128] ;
extern  uint    SampleResults3[128] ;
extern  uint    SampleResults4[128] ;
extern  uint    SampleResults5[128];
extern  ulong   Average_SampleResults2;
extern  ulong   Average_SampleResults3;
extern  ulong   Average_SampleResults4;
extern  ulong   Average_SampleResults0;
extern  uint    Average_Count2;
extern  uint    Average_Count3;
extern  uint    Average_Count4;
extern  uint    Average_Count0;
extern  uint    Current_Lvbo_Count;
extern  uint    RobustResults[16];
extern  uint    DisposeDataA0;
extern  uint    DisposeDataA1;
extern  uint    DisposeDataA2;
extern  uint    DisposeDataA3;
extern  int    DisposeDataB0;
extern  int    DisposeDataB1;
extern  int    DisposeDataB2; 
extern  uint   AAAAA;
extern  int    Effi;
extern  uint   Efficiency_SHUZU[5];
extern int    BUJIN_addata1;
extern uint    PID_ZD1;
extern uint    BUJIN_pwm1;
extern uint    PID_ZD0;
extern uint    BUJIN_pwm0;
extern int   CurrentSharingA0;
extern int   CurrentSharingA1;
extern uint   CURRENT_DADATA[11];
extern uint   CURRENT_PIDZD[11];
extern int    CURRENT[11];
extern uint   VOLTAGE_DADATA;
extern uint   VOLTAGE_PIDZD;
extern uint   CURRENT_Mode2;
extern int   CURRENT_Mode2_PIDZD;
extern uint   Free_ModeSet;
extern uint   Free_ModeSetA;
extern uint   Free_ModeSetB;
//extern float    Current_One,Current_Two,Voltage_One,Voltage_Two;
//extern  float  RatioYds0,RatioYds1,RatioYds2,RatioYds3;
extern uchar  Figure[10]  ;
#endif

