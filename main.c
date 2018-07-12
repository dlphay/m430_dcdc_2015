

/*
  2015年双向DC-DC变换器（A题）
  时间： 2015.08.12
  成员：郝凯旋、闫达帅、韦添元

*/



/*
p40  charging    
p42  discharging
p44  waiting    

P4OUT  &= ~(BIT4);  //充电模式指示灯 打开
P4OUT  &= ~(BIT2);  //放电模式指示灯 打开
P4OUT  &= ~(BIT0);  //等待模式指示灯 打开

P4OUT  |= BIT4;  //充电模式指示灯 关闭
P4OUT  |= BIT2;  //放电模式指示灯 关闭
P4OUT  |= BIT0;  //等待模式指示灯 关闭

#
p41  guochong   
p43  guofang    

P4OUT  &= ~(BIT1);  //过放 指示灯 BUCK  打开
P4OUT  &= ~(BIT3);  //过冲 指示灯 BOOST 打开

P4OUT  |= BIT1;   //过放 指示灯 BUCK  关闭
P4OUT  |= BIT3;   //过冲 指示灯 BOOST 关闭
p51  Buck guangou
p53  Boost guangou
 
P5OUT  &= ~(BIT1); // BUCK的光耦控制   打开
P5OUT  &= ~(BIT3); // BOOST的光耦控制  打开

P5OUT  |= BIT1; // BUCK的光耦控制   关闭
P5OUT  |= BIT3; // BOOST的光耦控制  关闭



*/
#include "MSP430X16X.h"
#include "ADC12S_YDS.H"
#include "CONFIG_YDS.H"
#include "TA12_PWM_YDS.H"
#include "DAC12S_YDS.H"
#include  "key_yds.h"
#include  "Variable_yds.h"
#include  "oled_yds.h"
#include  "pid_YDS.H"
//ACLK  -> Auxiliary Clock
//MCLK  -> Master    Clock
//SMCLK -> Sub-Main  Clock

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  Close_IO();
  Clock_Init();                       
  Port_Init();  
  PIDIncremental_Mode0_init();
  PIDIncremental_Mode1_init();
  OLED_Init();		
  OLED_Clear(); 
  OLED_ShowCHinese(0,0,0);
  OLED_ShowCHinese(18,0,1);
  OLED_ShowCHinese(36,0,2);
  OLED_ShowString(52,0,":");
  OLED_ShowCHinese(64,0,9);
  OLED_ShowCHinese(80,0,10);
  OLED_ShowCHinese(96,0,11);
  OLED_ShowCHinese(112,0,12);
  
  OLED_ShowString(64,2,"1.0000A");
  OLED_ShowCHinese(0,2,3);
  OLED_ShowCHinese(18,2,4);
  OLED_ShowCHinese(36,2,5);
  OLED_ShowString(52,2,":");
  
  OLED_ShowCHinese(0,4,6);
  OLED_ShowCHinese(18,4,7);
  OLED_ShowCHinese(36,4,8);
  OLED_ShowString(52,4,":");
  
  Dac_Init();
  Adc_Init();
  Dac12Write(CURRENT_DADATA[BuJin_Count],0);
  _EINT();
  LPM0;
}
