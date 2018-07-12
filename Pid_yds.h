#ifndef __PID_YDS_H__
#define __PID_YDS_H__
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long
extern struct PID pid;
void  PidLocation_yds(int Actual_Voltage,int Set_Voltage );
void  PidIncremental_Mode0_yds(int Actual_Voltage,int Set_Voltage );
void  PidIncremental_Mode1_yds(int Actual_Voltage,int Set_Voltage );
void  PidLocationA_yds(int Actual_Voltage,int Set_Voltage );
void PIDLocation_init();
void PIDIncremental_Mode0_init();
void PIDIncremental_Mode1_init();
#endif

