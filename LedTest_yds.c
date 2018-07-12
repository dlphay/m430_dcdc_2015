
#include  "msp430x16x.h" 
#include  "LedTest_yds.h"


#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

#define CPU_F ((double)8000000)   
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0)) 

void LedTest(void)
{
  uint  i;
  for(i=0;i<10;i++)
  {
    P1OUT &= 0xfe;
    delay_ms(30);
    P1OUT |= 0x01;
    delay_ms(30);
  }
}
