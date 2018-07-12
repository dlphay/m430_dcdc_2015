

/*
  2015��˫��DC-DC�任����A�⣩
  ʱ�䣺 2015.08.12
  ��Ա���¿������ƴ�˧��Τ��Ԫ

*/



/*
p40  charging    
p42  discharging
p44  waiting    

P4OUT  &= ~(BIT4);  //���ģʽָʾ�� ��
P4OUT  &= ~(BIT2);  //�ŵ�ģʽָʾ�� ��
P4OUT  &= ~(BIT0);  //�ȴ�ģʽָʾ�� ��

P4OUT  |= BIT4;  //���ģʽָʾ�� �ر�
P4OUT  |= BIT2;  //�ŵ�ģʽָʾ�� �ر�
P4OUT  |= BIT0;  //�ȴ�ģʽָʾ�� �ر�

#
p41  guochong   
p43  guofang    

P4OUT  &= ~(BIT1);  //���� ָʾ�� BUCK  ��
P4OUT  &= ~(BIT3);  //���� ָʾ�� BOOST ��

P4OUT  |= BIT1;   //���� ָʾ�� BUCK  �ر�
P4OUT  |= BIT3;   //���� ָʾ�� BOOST �ر�
p51  Buck guangou
p53  Boost guangou
 
P5OUT  &= ~(BIT1); // BUCK�Ĺ������   ��
P5OUT  &= ~(BIT3); // BOOST�Ĺ������  ��

P5OUT  |= BIT1; // BUCK�Ĺ������   �ر�
P5OUT  |= BIT3; // BOOST�Ĺ������  �ر�



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
