
#include  "msp430x16x.h"
#include  "OLED_yds.h"
#include  "Key_yds.h"
#include  "Variable_yds.h"
#include  "ledtest_yds.h"
#include  "Dac12s_yds.h"

#define CPU_F ((double)8000000)   //外部高频晶振8MHZ
//#define CPU_F ((double)32768)   //外部低频晶振32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0)) 
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0)) 

uint    Mode_Count =0;
uint    BuJin_Count = 0;
void add(uint i)
{
  switch(i)
{
  case 0:       
{
  OLED_ShowCHinese(0,0,0);
  OLED_ShowCHinese(18,0,1);
  OLED_ShowCHinese(36,0,2);
  OLED_ShowString(52,0,":");  
  OLED_ShowCHinese(64,0,9);
  OLED_ShowCHinese(80,0,10);
  OLED_ShowCHinese(96,0,11);
  OLED_ShowCHinese(112,0,12);
  break ;
}
  case 1:       
{ 
  OLED_ShowCHinese(0,0,0);
  OLED_ShowCHinese(18,0,1);
  OLED_ShowCHinese(36,0,2);
  OLED_ShowString(52,0,":");
  OLED_ShowCHinese(64,0,13);
  OLED_ShowCHinese(80,0,10);
  OLED_ShowCHinese(96,0,11);
  OLED_ShowCHinese(112,0,12);
  break ;
}
  case 2:       
{ 
  OLED_ShowCHinese(0,0,0);
  OLED_ShowCHinese(18,0,1);
  OLED_ShowCHinese(36,0,2);
  OLED_ShowString(52,0,":");
  OLED_ShowCHinese(64,0,14);
  OLED_ShowCHinese(80,0,15);
  OLED_ShowCHinese(96,0,16);
  OLED_ShowCHinese(112,0,17);
  break ;
}
}
}
void add0(uint i)
{
  OLED_ShowCHinese(0,2,3);
  OLED_ShowCHinese(18,2,4);
  OLED_ShowCHinese(36,2,5);
  OLED_ShowString(52,2,":");
  switch(i)
  {
  case 0:       { OLED_ShowString(64,2,"1.0000A");break ;}
  case 1:       { OLED_ShowString(64,2,"1.1000A");break ;}
  case 2:       { OLED_ShowString(64,2,"1.2000A");break ;}
  case 3:       { OLED_ShowString(64,2,"1.3000A");break ;}
  case 4:       { OLED_ShowString(64,2,"1.4000A");break ;}
  case 5:       { OLED_ShowString(64,2,"1.5000A");break ;}
  case 6:       { OLED_ShowString(64,2,"1.6000A");break ;}
  case 7:       { OLED_ShowString(64,2,"1.7000A");break ;}
  case 8:       { OLED_ShowString(64,2,"1.8000A");break ;}
  case 9:       { OLED_ShowString(64,2,"1.9000A");break ;}
  case 10:      { OLED_ShowString(64,2,"2.0000A");break ;}

  }
}
void P14_key(void)
{
   Mode_Count ++ ;
   add(Mode_Count);
   if(Mode_Count == 3)  Mode_Count =0;
   if(Mode_Count == 1) 
   {
     OLED_Clear(); 
     add(Mode_Count);
     OLED_ShowCHinese(0,2,3);
     OLED_ShowCHinese(18,2,4);
     OLED_ShowCHinese(36,2,5);
     OLED_ShowString(52,2,":");
     OLED_ShowCHinese(0,4,6);
     OLED_ShowCHinese(18,4,7);
     OLED_ShowCHinese(36,4,8);
     OLED_ShowString(52,4,":");
     OLED_ShowString(64,2,"30.000V");
     Dac12Write(0xc10,1);
     P4OUT  |= BIT4;  //充电模式指示灯 关闭
     P4OUT  |= BIT2;  //放电模式指示灯 关闭
     P4OUT  |= BIT0;  //自由模式指示灯 关闭
     P4OUT  &= ~(BIT2);  //放电模式指示灯 打开
     P5OUT  |= BIT0; // BUCK的光耦控制   关闭
     P5OUT  |= BIT2; // BOOST的光耦控制  关闭
     P4OUT  |= BIT1;   //过放 指示灯 BUCK  关闭
     P4OUT  |= BIT3;   //过冲 指示灯 BOOST 关闭
     delay_ms(200);
     P4OUT  &= ~(BIT3);  //过冲 指示灯 BOOST 打开
     P5OUT  &= ~(BIT3); // BOOST的光耦控制  打开

   }
   if(Mode_Count == 2)
   {
      Free_ModeSetB =0;
      OLED_ShowCHinese(0,4,6);
      OLED_ShowCHinese(18,4,7);
      OLED_ShowCHinese(36,4,8);
      OLED_ShowString(52,4,":");
      P4OUT  |= BIT0;  //充电模式指示灯 关闭
      P4OUT  |= BIT2;  //放电模式指示灯 关闭
      P4OUT  |= BIT4;  //自由模式指示灯 关闭
      P4OUT  &= ~(BIT2);  //自由模式指示灯 打开
     //先开电池  光耦 ！！！泵两次  泵到19.7V
     
     
     //再开电源  光耦
     
     //升到30V ，，然后电池会自动的断开自保护！！！！！
     
     
     Dac12Write(0xc10,1); 
     P5OUT  |= BIT1; // BUCK的光耦控制   关闭
     P5OUT  |= BIT3; // BOOST的光耦控制  关闭    
     P4OUT  |= BIT1;   //过放 指示灯 BUCK  关闭
     P4OUT  |= BIT3;   //过冲 指示灯 BOOST 关闭
     delay_ms(200);
     P4OUT  &= ~(BIT3);  //过冲 指示灯 BOOST 打开
     P5OUT  &= ~(BIT3); // BOOST的光耦控制  打开
 
   //电池光耦再开启一次    
   }

}
void P15_key(void)
{
  BuJin_Count++;
  if(BuJin_Count == 11)  BuJin_Count==0;
  add0(BuJin_Count);
  Dac12Write(CURRENT_DADATA[BuJin_Count],0);
}
void P16_key(void)
{
     P4OUT  |= BIT0;  //充电模式指示灯 关闭
     P4OUT  |= BIT2;  //放电模式指示灯 关闭
     P4OUT  |= BIT4;  //自由模式指示灯 关闭
     P4OUT  &= ~(BIT0);  //自由模式指示灯 打开
     P5OUT  |= BIT1; // BUCK的光耦控制   关闭
     P5OUT  |= BIT3; // BOOST的光耦控制  关闭
     
     P4OUT  |= BIT1;   //过放 指示灯 BUCK  关闭
     P4OUT  |= BIT3;   //过冲 指示灯 BOOST 关闭
     OLED_ShowCHinese(64,0,18);
     OLED_ShowCHinese(80,0,19);
     OLED_ShowCHinese(96,0,20);
     OLED_ShowCHinese(112,0,21);
  // LedTest();
}
void P17_key(void)
{
  BuJin_Count++;
  if(BuJin_Count == 11)  BuJin_Count==0;
  add0(BuJin_Count);
  Dac12Write(CURRENT_DADATA[BuJin_Count],0);
  /*
  int  i =0;
   for(i=0;i<3072;i++)
   {
     delay_ms(2);
     Dac12Write(i,1);
   }  */
   /*
  
   Dac12Write(300,1);delay_ms(500);
   Dac12Write(600,1);delay_ms(500);
   Dac12Write(1000,1);delay_ms(500);
   Dac12Write(1400,1);delay_ms(500);
   Dac12Write(1800,1);delay_ms(500);
   Dac12Write(2200,1);delay_ms(500);
   Dac12Write(2600,1);delay_ms(500);
   Dac12Write(3072,1);delay_ms(500);
   */
}

void delay(void)
{
    uint tmp;
    
    for(tmp = 12000;tmp > 0;tmp--);
}


#pragma vector=PORT1_VECTOR
__interrupt void  PORT1_ISR(void)
{
    if(P1IFG & 0xf0)
    {
        switch(P1IFG)
        {
        case 0x10:
                    if(keyin == 0xe0)   
                    {
                        delay();
                        if(keyin == 0xe0)
                        {
                            while(keyin != 0xf0);       
                            P14_key();
                            P1IFG = 0;
                            return;
                        }
                    }
        case 0x20:
                    if(keyin == 0xd0)   
                    {
                        delay();
                        if(keyin == 0xd0)
                        {
                            while(keyin != 0xf0);       
                            P15_key();
                            P1IFG = 0;
                            return;
                        }
                    }
        case 0x40:
                    if(keyin == 0xb0)   
                    {
                        delay();
                        if(keyin == 0xb0)
                        {
                            while(keyin != 0xf0);       
                            P16_key();
                            P1IFG = 0;
                            return;
                        }
                    }
        case 0x80:
                    if(keyin == 0x70)   
                    {
                        delay();
                        if(keyin == 0x70)
                        {
                            while(keyin != 0xf0);       
                            P17_key();
                            P1IFG = 0;
                            return;
                        }
                    }
        default:
                    while(keyin != 0xf0);       
                    P1IFG = 0;
                    return;
        }
    }
}
