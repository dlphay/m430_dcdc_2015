#include   "stdlib.h"
#include   "Variable_yds.h"
#include   "Pid_yds.h"
#include   "key_yds.H"


typedef struct PID
{
   //int Voltage;
   
   float Proportion;
   float Integral;
   float Derivation;
   
   int   Last_Error;
   int   Error;
   int   Next_Error;
   int   I_Error;
   int   Sum_Error;
   int   D_Error;
   
   int   Set_Voltage;
   int   Actual_Voltage;
   int   Voltage;
   
    
}PID;
PID pid; 
void PIDLocation_init()
{
    pid.Voltage=0;
    pid.Set_Voltage=0;
    pid.Actual_Voltage=0;
    
    pid.I_Error     =0;
    pid.D_Error     =0;
    pid.Sum_Error   =0;
    
    pid.Last_Error  =0;
   // pid.Next_Error  =0;
    
     
    pid.Proportion  =0.027;    //0.067
    pid.Integral    = 0.00;     //0.001357
    pid.Derivation  =0.030;      //0.00245
    pid.Sum_Error   =0;
}
void PIDIncremental_Mode0_init()
{
    pid.Voltage=0;
    pid.Set_Voltage=0;
    pid.Actual_Voltage=0;
    
    pid.Error       =0;
    pid.Last_Error  =0;
    pid.Next_Error  =0;
    
     
    pid.Proportion  =0.020;
    pid.Integral    =0.027;  
    pid.Derivation  =0.025;
   
}
void PIDIncremental_Mode1_init()
{
    pid.Voltage=0;
    pid.Set_Voltage=0;
    pid.Actual_Voltage=0;
    
    pid.Error       =0;
    pid.Last_Error  =0;
    pid.Next_Error  =0;
    
     
    pid.Proportion  =0.020;
    pid.Integral    =0.027;  
    pid.Derivation  =0.025;
   
}
/*位置式pid*/
 void  PidLocation_yds(int Actual_Voltage,int Set_Voltage )

{
   pid.Actual_Voltage  =   Actual_Voltage ;
   pid.Set_Voltage     =   Set_Voltage ;
                   
   //pid.I_Error = pid.Set_Voltage - pid.Actual_Voltage; 
   pid.I_Error = pid.Actual_Voltage - pid.Set_Voltage ; 
   if( pid.I_Error < 0)  pid.I_Error += Pid_DeadBand;
   if( pid.I_Error > 0)  pid.I_Error -= Pid_DeadBand;
  
   pid.Sum_Error += pid.I_Error;
   pid.D_Error   =  pid.I_Error - pid.Last_Error;
   pid.Last_Error  =  pid.I_Error; 
   
   PID_ZD1 = (int)(PID_ZD1 + pid.Proportion * pid.I_Error 
                                 + pid.Integral * pid.Sum_Error 
                                 + pid.Derivation * pid.D_Error);
} 
/*增量式pid*/
void  PidIncremental_Mode0_yds(int Actual_Voltage,int Set_Voltage )
{
  
   pid.Actual_Voltage  =   Actual_Voltage ;
   pid.Set_Voltage     =   Set_Voltage ;
                   
   pid.Error = pid.Set_Voltage - pid.Actual_Voltage; 
  // if( pid.Error < 0)  pid.Error += Pid_DeadBand;   //死区的部分不需要考虑，不用除掉 ！
//   if( pid.Error > 0)  pid.Error -= Pid_DeadBand;
   CURRENT_PIDZD[BuJin_Count] = (uint)(CURRENT_PIDZD[BuJin_Count] + pid.Proportion *( pid.Error-pid.Next_Error) 
                                        + pid.Integral * pid.Error 
                                        + pid.Derivation * (pid.Error-2*pid.Next_Error+pid.Last_Error));
   pid.Last_Error = pid.Next_Error;
   pid.Next_Error = pid.Error;
} 
void  PidIncremental_Mode1_yds(int Actual_Voltage,int Set_Voltage )
{
  
   pid.Actual_Voltage  =   Actual_Voltage ;
   pid.Set_Voltage     =   Set_Voltage ;
                   
   pid.Error = pid.Set_Voltage - pid.Actual_Voltage; 
  // if( pid.Error < 0)  pid.Error += Pid_DeadBand;   //死区的部分不需要考虑，不用除掉 ！
//   if( pid.Error > 0)  pid.Error -= Pid_DeadBand;
   VOLTAGE_PIDZD = (uint)(VOLTAGE_PIDZD + pid.Proportion *( pid.Error-pid.Next_Error) 
                                        + pid.Integral * pid.Error 
                                        + pid.Derivation * (pid.Error-2*pid.Next_Error+pid.Last_Error));
   pid.Last_Error = pid.Next_Error;
   pid.Next_Error = pid.Error;
} 
/*位置式pid*/
 void  PidLocationA_yds(int Actual_Voltage,int Set_Voltage )

{
  
   pid.Actual_Voltage  =   Actual_Voltage ;
   pid.Set_Voltage     =   Set_Voltage ;
                   
 //  pid.I_Error = pid.Set_Voltage - pid.Actual_Voltage; 
   pid.I_Error =pid.Actual_Voltage - pid.Set_Voltage; 
   if( pid.I_Error < 0)  pid.I_Error += Pid_DeadBand;
   if( pid.I_Error > 0)  pid.I_Error -= Pid_DeadBand;
   if( pid.I_Error < 0)  PID_ZD1 --;
   if( pid.I_Error > 0)  PID_ZD1 ++;
  
   
   //占空比可调区域： 50%--100%
   if(PID_ZD1 < 200)   PID_ZD1 = 200;
   if(PID_ZD1 > 399)   PID_ZD1 = 400;
} 


