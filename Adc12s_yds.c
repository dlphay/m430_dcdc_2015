/********************************************************************************
Module function：Multi-channel signal AD sampling
Producer：yandashuai  Holy Snail丶Ｄsペ
Note：P6.0  P6.1  P6.2  P6.3

*********************************************************************************/
#include  "msp430x16x.h"
#include  "oled_yds.h"
#include  "Variable_yds.h"
#include  "Adc12s_yds.h"
#include  "Ta12_Pwm_yds.h"
#include   "Pid_yds.h"
#include   "stdlib.h"
#include   "key_yds.h"
#include  "CURRENTSP_YDS.H"
#include   "DAC12S_YDS.H"
#include  "math.h"

#define CPU_F ((double)8000000)   //外部高频晶振8MHZ
//#define CPU_F ((double)32768)   //外部低频晶振32.768KHZ
#define DelayUs(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0)) 
#define DelayMs(x) __delay_cycles((long)(CPU_F*(double)x/1000.0)) 

#define   Num_of_Results   128

uchar DigitalArray[] = {"0123456789."};


uint    TEMP=0;  
uint    SampleDataTemp;
uint    SampleDataA1,SampleDataA2,SampleDataA3,SampleDataA4;   //ad量 
uint    SampleDataA5,SampleDataA6,SampleDataA7,SampleDataA8;   //电压值
uint    SampleDataA9,SampleDataA10,SampleDataA11,SampleDataA12,SampleDataA13;              // 电流值

void Adc_Init(void)
{
  P6SEL |= 0x3F;                   
  ADC12CTL0 = REF2_5V + REFON+ADC12ON+SHT0_8+MSC;     // t=4*Tclk*8
  ADC12CTL1 = SHP+CONSEQ_3; 
  ADC12MCTL0 |= INCH_0; 
  ADC12MCTL1 |= INCH_1;                     
  ADC12MCTL2 |= INCH_2;   
  ADC12MCTL3 |= INCH_3; 
  ADC12MCTL4 |= INCH_4;
  ADC12MCTL5 |= INCH_5+EOS;
  ADC12IE = 0x3F;                           
  ADC12CTL0 |= ENC;                  //  enable convert       
  ADC12CTL0 |= ADC12SC;              //  start convert       
}

void LCD_DisplayVoltage2()   //u1
{
   OLED_ShowChar(0,6,Figure[SampleDataA5]);
   OLED_ShowChar(8,6,Figure[SampleDataA6]);
   OLED_ShowChar(16,6,'.');
   OLED_ShowChar(24,6,Figure[SampleDataA7]);
   OLED_ShowChar(32,6,Figure[SampleDataA8]);
   OLED_ShowChar(40,6,'V');
}
void LCD_DisplayVoltage3()   //u2
{
   OLED_ShowChar(64,4,Figure[SampleDataA5]);
   OLED_ShowChar(72,4,Figure[SampleDataA6]);
   OLED_ShowChar(80,4,'.');
   OLED_ShowChar(88,4,Figure[SampleDataA7]);
   OLED_ShowChar(96,4,Figure[SampleDataA8]);
   OLED_ShowChar(104,4,'V');
}
void LCD_DisplayVoltage4()   //u22
{
   OLED_ShowChar(64,6,Figure[SampleDataA5]);
   OLED_ShowChar(72,6,Figure[SampleDataA6]);
   OLED_ShowChar(80,6,'.');
   OLED_ShowChar(88,6,Figure[SampleDataA7]);
   OLED_ShowChar(96,6,Figure[SampleDataA8]);
   OLED_ShowChar(104,6,'V');
}
void LCD_DisplayCurrent0()
{
   OLED_ShowChar(64,4,Figure[SampleDataA9]);
   OLED_ShowChar(72,4,'.');
   OLED_ShowChar(80,4,Figure[SampleDataA10]);
   OLED_ShowChar(88,4,Figure[SampleDataA11]);
   OLED_ShowChar(96,4,Figure[SampleDataA12]);
   OLED_ShowChar(104,4,Figure[SampleDataA13]);
   OLED_ShowChar(112,4,'A');
} 
void LCD_DisplayCurrent1()
{
   OLED_ShowChar(64,6,Figure[SampleDataA9]);
   OLED_ShowChar(72,6,'.');
   OLED_ShowChar(80,6,Figure[SampleDataA10]);
   OLED_ShowChar(88,6,Figure[SampleDataA11]);
   OLED_ShowChar(96,6,Figure[SampleDataA12]);
   OLED_ShowChar(104,6,Figure[SampleDataA13]);
   OLED_ShowChar(112,6,'A');
} 

//转化的电压值
void Voltage_do2_Mode0(uint temp_d)
{
  uint temp_1,temp_2,temp_3;
  ulong temp_4; 
  temp_4=(ulong)(temp_d)*165;            
  temp_d=temp_4/128; 
  //Voltage_One = (float)temp_d;

  if((temp_d>2430)&&(BuJin_Count ==10))  
  {
    P4OUT  |= BIT4;   //充电模式指示灯 关闭
    P4OUT  |= BIT2;   //放电模式指示灯 关闭
    P4OUT  |= BIT0;   //等待模式指示灯 关闭
    P4OUT  |= BIT1;   //过放 指示灯 BUCK  关闭
    P4OUT  |= BIT3;   //过冲 指示灯 BOOST 关闭
    P5OUT  |= BIT1;   // BUCK的光耦控制   关闭
    P5OUT  |= BIT3;   // BOOST的光耦控制  关闭
  }    
    //保护
  SampleDataA5=temp_d/1000;                        
  temp_1=temp_d%1000;
  SampleDataA6=temp_1/100;
  temp_2=temp_1%100;
  SampleDataA7=temp_2/10;
  temp_3=temp_1%10;
  SampleDataA8=temp_3;
}
void Voltage_do2_Mode1(uint temp_d)
{
  uint temp_1,temp_2,temp_3;
  ulong temp_4; 
  temp_4=(ulong)(temp_d)*165;            
  temp_d=temp_4/128; 
 // Voltage_One = (float)temp_d;
  if(temp_d >1800)   Free_ModeSetB =1;
  if( Free_ModeSetB ==1 )
  {
    if(temp_d < 1000) 
    {
    P4OUT  |= BIT4;   //充电模式指示灯 关闭
    P4OUT  |= BIT2;   //放电模式指示灯 关闭
    P4OUT  |= BIT0;   //等待模式指示灯 关闭
    P4OUT  |= BIT1;   //过放 指示灯 BUCK  关闭
    P4OUT  |= BIT3;   //过冲 指示灯 BOOST 关闭
    P5OUT  |= BIT1;   // BUCK的光耦控制   关闭
    P5OUT  |= BIT3;   // BOOST的光耦控制  关闭
    }
  }
  SampleDataA5=temp_d/1000;                        
  temp_1=temp_d%1000;
  SampleDataA6=temp_1/100;
  temp_2=temp_1%100;
  SampleDataA7=temp_2/10;
  temp_3=temp_1%10;
  SampleDataA8=temp_3;
}
void Voltage_do2_Mode2(uint temp_d)
{
  uint temp_1,temp_2,temp_3;
  ulong temp_4; 
  temp_4=(ulong)(temp_d)*165;            
  temp_d=temp_4/128; 
 // Voltage_One = (float)temp_d;
  if(temp_d >1700)   Free_ModeSetB =1;
  if( Free_ModeSetB ==1 )
  {
    if(temp_d < 1000) 
    {
    P4OUT  |= BIT4;   //充电模式指示灯 关闭
    P4OUT  |= BIT2;   //放电模式指示灯 关闭
    P4OUT  |= BIT0;   //等待模式指示灯 关闭
    P4OUT  |= BIT1;   //过放 指示灯 BUCK  关闭
    P4OUT  |= BIT3;   //过冲 指示灯 BOOST 关闭
    P5OUT  |= BIT1;   // BUCK的光耦控制   关闭
    P5OUT  |= BIT3;   // BOOST的光耦控制  关闭
    }
  }
  SampleDataA5=temp_d/1000;                        
  temp_1=temp_d%1000;
  SampleDataA6=temp_1/100;
  temp_2=temp_1%100;
  SampleDataA7=temp_2/10;
  temp_3=temp_1%10;
  SampleDataA8=temp_3;
}
void Voltage_do3_Mode0(uint temp_d)
{
  uint temp_1,temp_2,temp_3;
  ulong temp_4; 
  temp_4=(ulong)(temp_d)*165;            
  temp_d=temp_4/128;       
 // Voltage_Two = (float)temp_d;
  SampleDataA5=temp_d/1000;                        
  temp_1=temp_d%1000;
  SampleDataA6=temp_1/100;
  temp_2=temp_1%100;
  SampleDataA7=temp_2/10;
  temp_3=temp_1%10;
  SampleDataA8=temp_3;
}
void Voltage_do3_Mode1(uint temp_d)
{
  uint temp_1,temp_2,temp_3;
  ulong temp_4; 
  temp_4=(ulong)(temp_d)*165;            
  temp_d=temp_4/128;  
 // DDDD_Mode1((int)temp_d);
 // Voltage_Two = (float)temp_d;
  SampleDataA5=temp_d/1000;                        
  temp_1=temp_d%1000;
  SampleDataA6=temp_1/100;
  temp_2=temp_1%100;
  SampleDataA7=temp_2/10;
  temp_3=temp_1%10;
  SampleDataA8=temp_3;
}
void Voltage_do3_Mode2(uint temp_d)
{
  uint temp_1,temp_2,temp_3;
  ulong temp_4; 
  temp_4=(ulong)(temp_d)*165;            
  temp_d=temp_4/128;    
 // PidIncremental_Mode1_yds(temp_d,3000);
  DDDD_Mode2((int)temp_d);
 // Voltage_Two = (float)temp_d;
  SampleDataA5=temp_d/1000;                        
  temp_1=temp_d%1000;
  SampleDataA6=temp_1/100;
  temp_2=temp_1%100;
  SampleDataA7=temp_2/10;
  temp_3=temp_1%10;
  SampleDataA8=temp_3;
}
void DDDD_Mode0(int Actual_Value)
{
  uint DCDCDC = 0;
  if((abs(CURRENT[BuJin_Count] - Actual_Value) <  50) && (CURRENT[BuJin_Count] > Actual_Value)) DCDCDC = 1;
  else DCDCDC = 2;
  if((abs(CURRENT[BuJin_Count] - Actual_Value) > 50 ) && (CURRENT[BuJin_Count] > Actual_Value)) DCDCDC = 3;
  else DCDCDC = 4;
  
  switch(DCDCDC)
  {
  case 0:  break;
  case 1:  break;
  case 2:  break;
  case 3:          CURRENT_PIDZD[BuJin_Count] += 2;         break;
  case 4:          CURRENT_PIDZD[BuJin_Count] -= 2;         break;
  default: break;
  }
  Dac12Write(CURRENT_PIDZD[BuJin_Count],0);
}
/*
void DDDD_Mode1(int Actual_Value)
{
  uint DCDCDC = 0;
  if((abs(3000 - Actual_Value) <  3) && (3000 > Actual_Value)) DCDCDC = 1;
  if((abs(3000 - Actual_Value) <  3) && (3000 < Actual_Value)) DCDCDC = 2;
  if((abs(3000 - Actual_Value) >  3 ) && (3000 > Actual_Value)) DCDCDC = 3;
  if((abs(3000 - Actual_Value) >  3 ) && (3000 < Actual_Value)) DCDCDC = 4;
    switch(DCDCDC)
  {
  case 0:  break;
  case 1:  break;
  case 2:  break;
  case 3:          VOLTAGE_PIDZD += 3;         break;
  case 4:          VOLTAGE_PIDZD -= 3;         break;
  default: break;
  }
  Dac12Write(VOLTAGE_PIDZD,1);
}
*/
void DDDD_Mode2(int Actual_Value)
{
  if(Free_ModeSet ==0)   //32v---35V控制 BOOST 
  {
   
  uint DCDCDC = 0;
  if((abs(3000 - Actual_Value) <  10) && (3000 > Actual_Value)) DCDCDC = 1;
  else DCDCDC = 2;
  if((abs(3000 - Actual_Value) >  10) && (3000 > Actual_Value)) DCDCDC = 3;
  else DCDCDC = 4;
  switch(DCDCDC)
  {
  case 0:  break;
  case 1:  break;
  case 2:  break;
  case 3:          VOLTAGE_PIDZD += 4;         break;
  case 4:          VOLTAGE_PIDZD -= 4;         break;
  default: break;
  }
  Dac12Write(VOLTAGE_PIDZD,1);
  }
  else   
  { 
   uint DCDCDC = 0;
  if((abs(2950 - Actual_Value) <  5) && (2950 > Actual_Value))  DCDCDC = 1;
  if((abs(2950 - Actual_Value) <  5) && (2950 < Actual_Value))  DCDCDC = 2;
  if((abs(2950 - Actual_Value) >  5) && (2950 > Actual_Value))  DCDCDC = 3;
  if((abs(2950 - Actual_Value) >  5) && (2950 < Actual_Value))  DCDCDC = 4;
  if((abs(2950 - Actual_Value) > 15) && (2950 > Actual_Value))  DCDCDC = 5;
  if((abs(2950 - Actual_Value) > 15) && (2950 < Actual_Value))  DCDCDC = 6;
  if((abs(2950 - Actual_Value) > 30) && (2950 > Actual_Value))  DCDCDC = 7;
  if((abs(2950 - Actual_Value) > 30) && (2950 < Actual_Value))  DCDCDC = 8;
  if((abs(2950 - Actual_Value) > 80) && (2950 > Actual_Value))  DCDCDC = 9;
  if((abs(2950 - Actual_Value) > 80) && (2950 < Actual_Value))  DCDCDC = 10;
  switch(DCDCDC)
  {
  case 0:  break;
  case 1:  break;
  case 2:  break;
  case 3:          CURRENT_Mode2_PIDZD -= 2;          break;
  case 4:          CURRENT_Mode2_PIDZD += 2;          break;
  case 5:          CURRENT_Mode2_PIDZD -= 4;         break;
  case 6:          CURRENT_Mode2_PIDZD += 4;         break;
  case 7:          CURRENT_Mode2_PIDZD -= 10;         break;
  case 8:          CURRENT_Mode2_PIDZD += 10;         break;
  case 9:          CURRENT_Mode2_PIDZD -= 25;         break;
  case 10:         CURRENT_Mode2_PIDZD += 25;         break;
  default: break;
  }
  if(CURRENT_Mode2_PIDZD < 1)    CURRENT_Mode2_PIDZD = 1;
  Dac12Write(CURRENT_Mode2_PIDZD,0);
  }
}

void Voltage_do4_Mode0(uint temp_d)
{
  uint temp_1,temp_2,temp_3;
  ulong temp_4; 
  temp_4=(ulong)(temp_d)*165;            
  temp_d=temp_4/128;       
  SampleDataA5=temp_d/1000;                        
  temp_1=temp_d%1000;
  SampleDataA6=temp_1/100;
  temp_2=temp_1%100;
  SampleDataA7=temp_2/10;
  temp_3=temp_1%10;
  SampleDataA8=temp_3;
}
//电流的转换值
//   V = 55/1024   i = 0.6667 U
void Current_do0_Mode0(uint temp_d)
{
  uint temp_2,temp_3,temp_5;
  ulong temp_4; 
  int temp_1;
  temp_4=(ulong)(temp_d)*4125; 
  temp_1=(int)(CurrentSPina282((temp_4/512))); 
 // Current_One = (float)temp_1;
 // DDDD((int)temp_1);
 // DDDD_Mode0(temp_1);
  PidIncremental_Mode0_yds(temp_1,CURRENT[BuJin_Count]);
  if((abs(temp_1 - CURRENT[BuJin_Count]) < 100) || (temp_1 <1000) )
  {
  SampleDataA9=temp_1/10000;
  temp_5=temp_1%10000;
  SampleDataA10=temp_5/1000;
  temp_1=temp_5%1000;
  SampleDataA11=temp_1/100;
  temp_2=temp_1%100;
  SampleDataA12=temp_2/10;
  temp_3=temp_1%10;
  SampleDataA13=temp_3;
  Current_Lvbo_Count = 0;
  }
  else
  {
    Current_Lvbo_Count++;
  }  
  if(Current_Lvbo_Count == 5)
  {
    SampleDataA9=temp_1/10000;
    temp_5=temp_1%10000;
    SampleDataA10=temp_5/1000;
    temp_1=temp_5%1000;
    SampleDataA11=temp_1/100;
    temp_2=temp_1%100;
    SampleDataA12=temp_2/10;
    temp_3=temp_1%10;
    SampleDataA13=temp_3;
    Current_Lvbo_Count--;  
  }
 
}
void Current_do1_Mode0(uint temp_d)
{
  uint temp_1,temp_2,temp_3,temp_5;
  ulong temp_4; 
  temp_4=(ulong)(temp_d)*4125; 
  temp_1=CurrentSPina282((temp_4/512)); 
 // Current_Two = (float)temp_1;
  SampleDataA9=temp_1/10000;
  temp_5=temp_1%10000;
  SampleDataA10=temp_5/1000;
  temp_1=temp_5%1000;
  SampleDataA11=temp_1/100;
  temp_2=temp_1%100;
  SampleDataA12=temp_2/10;
  temp_3=temp_1%10;
  SampleDataA13=temp_3;
}void Current_do0_Mode1(uint temp_d)
{
  uint temp_1,temp_2,temp_3,temp_5;
  ulong temp_4; 
  temp_4=(ulong)(temp_d)*4125; 
  temp_1=CurrentSPina282((temp_4/512)); 
//  Current_One = (float)temp_1;
  SampleDataA9=temp_1/10000;
  temp_5=temp_1%10000;
  SampleDataA10=temp_5/1000;
  temp_1=temp_5%1000;
  SampleDataA11=temp_1/100;
  temp_2=temp_1%100;
  SampleDataA12=temp_2/10;
  temp_3=temp_1%10;
  SampleDataA13=temp_3;
}
void Current_do1_Mode1(uint temp_d)
{
  uint temp_1,temp_2,temp_3,temp_5;
  ulong temp_4; 
  temp_4=(ulong)(temp_d)*4125; 
  temp_1=CurrentSPina282((temp_4/512)); 
 // Current_Two = (float)temp_1;
  SampleDataA9=temp_1/10000;
  temp_5=temp_1%10000;
  SampleDataA10=temp_5/1000;
  temp_1=temp_5%1000;
  SampleDataA11=temp_1/100;
  temp_2=temp_1%100;
  SampleDataA12=temp_2/10;
  temp_3=temp_1%10;
  SampleDataA13=temp_3;
}
void Current_do0_Mode2(uint temp_d)
{
  uint temp_1,temp_2,temp_3,temp_5;
  ulong temp_4; 
  temp_4=(ulong)(temp_d)*4125; 
  temp_1=CurrentSPina282((temp_4/512)); 
 // Current_One = (float)temp_1;
 // DDDD((int)temp_1);
 // PidIncremental_Mode0_yds(temp_1,CURRENT[BuJin_Count]);
  SampleDataA9=temp_1/10000;
  temp_5=temp_1%10000;
  SampleDataA10=temp_5/1000;
  temp_1=temp_5%1000;
  SampleDataA11=temp_1/100;
  temp_2=temp_1%100;
  SampleDataA12=temp_2/10;
  temp_3=temp_1%10;
  SampleDataA13=temp_3;
}
void Current_do1_Mode2(uint temp_d)
{
  uint temp_1,temp_2,temp_3,temp_5;
  ulong temp_4; 
  temp_4=(ulong)(temp_d)*4125; 
 // temp_1=CurrentSPina168((temp_4/512)); 
  temp_1=CurrentSPina282((temp_4/512)); 
  if(temp_1 > 5000)  Free_ModeSetA = 1;
  if(Free_ModeSetA == 1)
  {
  if((temp_1 <100) && (Free_ModeSet ==0)) 
  {
    Free_ModeSet =1;
    P4OUT  |= BIT4;   //充电模式指示灯 关闭
    P4OUT  |= BIT2;   //放电模式指示灯 关闭
    P4OUT  |= BIT0;   //等待模式指示灯 关闭
    P4OUT  |= BIT1;   //过放 指示灯 BUCK  关闭
    P4OUT  |= BIT3;   //过冲 指示灯 BOOST 关闭
    P5OUT  |= BIT1;   // BUCK的光耦控制   关闭
    P5OUT  |= BIT3;   // BOOST的光耦控制  关闭
    P4OUT  &= ~(BIT4);  //充电模式指示灯 打开
    P4OUT  &= ~(BIT1);  //过放 指示灯 BUCK  打开
    delay_ms(200);
    Dac12Write(1,0); 
    delay_ms(20);
    P5OUT  &= ~(BIT1); // BUCK的光耦控制   打开
    
  }
  }  
 // Current_Two = (float)temp_1;
  SampleDataA9=temp_1/10000;
  temp_5=temp_1%10000;
  SampleDataA10=temp_5/1000;
  temp_1=temp_5%1000;
  SampleDataA11=temp_1/100;
  temp_2=temp_1%100;
  SampleDataA12=temp_2/10;
  temp_3=temp_1%10;
  SampleDataA13=temp_3;
}
/*
void Efficiency_yds(void)
{
  uint temp_1,temp_2,temp_3;
  uint temp_4;
  ulong temp_5 =0;
  float  Efficiency;
  if(Mode_Count)  Efficiency = (Voltage_One * Current_One)/(Voltage_Two * Current_Two);
  else  Efficiency = (Voltage_Two * Current_Two)/(Voltage_One * Current_One);
  Efficiency *=10000;
  temp_4 = (uint)Efficiency;
  if((temp_4 <10000) && (temp_4 >6000)) 
    Efficiency_SHUZU[Effi++] = temp_4;
  if(Effi ==5)
  {
    uchar aaaaa;
    Effi =0;
    for(aaaaa=0;aaaaa<5;aaaaa++)
    {
     temp_5 += Efficiency_SHUZU[aaaaa];
    }
     temp_4 = (uint)(temp_5/5);   
  SampleDataA1=temp_4/1000;                        
  temp_1=temp_4%1000;
  SampleDataA2=temp_1/100;
  temp_2=temp_1%100;
  SampleDataA3=temp_2/10;
  temp_3=temp_1%10;
  SampleDataA4=temp_3;
  OLED_ShowChar(64,2,Figure[SampleDataA1]);
  OLED_ShowChar(72,2,Figure[SampleDataA2]);
  OLED_ShowChar(80,2,'.');
  OLED_ShowChar(88,2,Figure[SampleDataA3]);
  OLED_ShowChar(96,2,Figure[SampleDataA4]);
  OLED_ShowChar(104,2,'%');
  } 
}
*/  
  
#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR (void) {
  
  static uint SampleCount0 = 0;
  static uint SampleCount1 = 0;
  static uint SampleCount2 = 0;
  static uint SampleCount3 = 0;
  static uint SampleCount4 = 0;
  static uint SampleCount5 = 0;
   // static uint RobustCount = 0;

  SampleResults5[SampleCount5++] = ADC12MEM0;    //  已经坏掉
  SampleResults1[SampleCount1++] = ADC12MEM1;    //  I2 Boost
  
  
  /*
  SampleResults2[SampleCount2++] = ADC12MEM2;    //  U1 Boost/Buck
  SampleResults3[SampleCount3++] = ADC12MEM3;    //  U2 Boost/Buck
  SampleResults4[SampleCount4++] = ADC12MEM4;    //  I2 boost
  SampleResults0[SampleCount0++] = ADC12MEM5;    //  I1 BUCK
  */
  SampleResults4[SampleCount4++] = ADC12MEM2;    //  I2 boost
  SampleResults3[SampleCount3++] = ADC12MEM3;    //  U2 Boost/Buck
  SampleResults0[SampleCount0++] = ADC12MEM4;    //  I1 BUCK
  SampleResults2[SampleCount2++] = ADC12MEM5;    //  U1 Boost/Buck



  switch(Mode_Count)
  {
  case 0:{
   if(SampleCount0 == Num_of_Results)
   {
      uchar i;
      unsigned long sum0 = 0;
      uint SUM0 = 0;
      SampleCount0 = 0;
      SampleCount5 = 0;
      for(i = 0; i < Num_of_Results; i++)
      {
            sum0 += SampleResults0[i];
      }
      sum0 >>= 7;
      Average_SampleResults0 += sum0;
      Average_Count0++;
      SUM0 = (uint)(sum0);
     // Current_do0_Mode0(SUM0);
      if(Average_Count0 ==16)
      {
         SUM0 =(uint)(Average_SampleResults0>>=4);
         Current_do0_Mode0(SUM0);
         LCD_DisplayCurrent0();
         Average_Count0 =0;
         Average_SampleResults0 =0;
      }
   }
   /*
   if(SampleCount1 == Num_of_Results)
   {
        uchar i;
        unsigned long sum1 = 0;
        uint SUM1 = 1;
        SampleCount1 = 0;
        for(i = 0; i < Num_of_Results; i++)
        {
            sum1 += SampleResults1[i];
        }
        sum1 >>= 7;
        SUM1 = (uint)(sum1);
        DelayMs(100);
        Current_do1_Mode0(SUM1);
        LCD_DisplayCurrent1();
}
   */
  if(SampleCount2 == Num_of_Results)
  {
        uchar i;
        unsigned long sum = 0;

        SampleCount2 = 0;
        for(i = 0; i < Num_of_Results; i++)
        {
            sum +=  SampleResults2[i];
        }
        sum >>= 7;
        Average_SampleResults2 += sum;
        Average_Count2++;
      //  Voltage_do2_Mode0(sum);
      if(Average_Count2 ==16)
      {
         sum =(ulong)(Average_SampleResults2>>=4);
         Voltage_do2_Mode0(sum);
         LCD_DisplayVoltage2();
         Average_Count2 =0;
         Average_SampleResults2 =0;
      }
  }
  if(SampleCount3 == Num_of_Results)
  {
        uchar i;
        unsigned long sum = 0;

          SampleCount0 = 0;
          SampleCount1 = 0;
          SampleCount2 = 0;
          SampleCount3 = 0;
          SampleCount4 = 0;
          SampleCount5 = 0;
        for(i = 0; i < Num_of_Results; i++)
        {
            sum +=  SampleResults3[i];
        }
        sum >>= 7;
        Average_SampleResults3 += sum;
        Average_Count3++;
      //  Voltage_do3_Mode0(sum);
      if(Average_Count3 ==16)
      {
         sum =(ulong)(Average_SampleResults3>>=4);
         Voltage_do3_Mode0(sum);
         LCD_DisplayVoltage4();
         Average_Count3 =0;
         Average_SampleResults3 =0;
      }
  }

  break;
  }
  case 1:{
  if(SampleCount2 == Num_of_Results)
  {
        uchar i;
        unsigned long sum = 0;

        SampleCount2 = 0;
        for(i = 0; i < Num_of_Results; i++)
        {
            sum +=  SampleResults2[i];
        }
        sum >>= 7;
        Average_SampleResults2 += sum;
        Average_Count2++;
       // Voltage_do2_Mode1(sum);
      if(Average_Count2 ==16)
      {
         sum =(ulong)(Average_SampleResults2>>=4);
         Voltage_do2_Mode1(sum);
         LCD_DisplayVoltage2();
         Average_Count2 =0;
         Average_SampleResults2 =0;
      }

  }
  if(SampleCount3 == Num_of_Results)
  {
        uchar i;
        unsigned long sum = 0;

        SampleCount3 = 0;
        for(i = 0; i < Num_of_Results; i++)
        {
            sum +=  SampleResults3[i];
        }
        sum >>= 7;
        Average_SampleResults3 += sum;
        Average_Count3++;
       // Voltage_do3_Mode1(sum);
       if(Average_Count3 ==16)
      {
         sum =(ulong)(Average_SampleResults3>>=4);
         Voltage_do3_Mode1(sum);
         LCD_DisplayVoltage3();
         Average_Count3 =0;
         Average_SampleResults3 =0;
      }

  }
   if(SampleCount4 == Num_of_Results)
  {
        uchar i ;
        unsigned long sum = 0;
        uint SUM1;
        SampleCount0 = 0;
        SampleCount1 = 0;
        SampleCount2 = 0;
        SampleCount3 = 0;
        SampleCount4 = 0;
        SampleCount5 = 0;
        for(i = 0; i < Num_of_Results; i++)
        {
            sum +=  SampleResults4[i];
        }
        sum >>= 7;
        Average_SampleResults4 += sum;
        Average_Count4++;
        SUM1 = (uint)(sum);
      //  Current_do1_Mode1(SUM1);
      if(Average_Count4 ==16)
      {
         SUM1 =(uint)(Average_SampleResults4>>=4);
         Current_do1_Mode1(SUM1);
         LCD_DisplayCurrent1();
         Average_Count4 =0;
         Average_SampleResults4 =0;
      }

       // Efficiency_yds();
  }
  break;
  }
  case 2:{
  if(SampleCount2 == Num_of_Results)
  {
        uchar i;
        unsigned long sum = 0;

        SampleCount2 = 0;
        for(i = 0; i < Num_of_Results; i++)
        {
            sum +=  SampleResults2[i];
        }
        sum >>= 7;
        Average_SampleResults2 += sum;
        Average_Count2++;
      //  Voltage_do2_Mode2(sum);
      if(Average_Count2 ==16)
      {
         sum =(ulong)(Average_SampleResults2>>=4);
         Voltage_do2_Mode2(sum);
         LCD_DisplayVoltage2();
         Average_Count2 =0;
         Average_SampleResults2 =0;
      }

  }
  if(SampleCount3 == Num_of_Results)
  {
        uchar i;
        unsigned long sum = 0;

        SampleCount3 = 0;
        for(i = 0; i < Num_of_Results; i++)
        {
            sum +=  SampleResults3[i];
        }
        sum >>= 7;
        Average_SampleResults3 += sum;
        Average_Count3++;
      //  Voltage_do3_Mode2(sum);
      if(Average_Count3 ==16)
      {
         sum =(ulong)(Average_SampleResults3>>=4);
         Voltage_do3_Mode2(sum);
         LCD_DisplayVoltage3();
         Average_Count3 =0;
         Average_SampleResults3 =0;
      }

  }
 if(SampleCount4 == Num_of_Results)
  {
        uchar i ;
        uint  SUM1;
        unsigned long sum = 0;

        SampleCount0 = 0;
        SampleCount1 = 0;
        SampleCount2 = 0;
        SampleCount3 = 0;
        SampleCount4 = 0;
        SampleCount5 = 0;
        for(i = 0; i < Num_of_Results; i++)
        {
            sum +=  SampleResults4[i];
        }
        sum >>= 7;
        Average_SampleResults4 += sum;
        Average_Count4++;
        SUM1 = (uint)(sum);
     //   Current_do1_Mode2(SUM1);
      if(Average_Count4 ==16)
      {
         SUM1 =(uint)(Average_SampleResults4>>=4);
         Current_do1_Mode2(SUM1);
         LCD_DisplayCurrent1();
         Average_Count4 =0;
         Average_SampleResults4 =0;
      }
       // Efficiency_yds();
  }
  break;  
  }
  default: break;
  }
}