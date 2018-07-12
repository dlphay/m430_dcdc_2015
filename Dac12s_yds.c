#include   "msp430x16x.h"
#include   "DAC12s_YDS.H"

void InitDac12()
{
	ADC12CTL0 = REF2_5V + REFON; 	
	DAC12_0CTL= DAC12IR + DAC12AMP_5 + DAC12ENC+DAC12LSEL_1 ;	
	DAC12_0CTL |= DAC12CALON;	
	DAC12_1CTL= DAC12IR + DAC12AMP_5 + DAC12ENC+DAC12LSEL_1 ;	
	DAC12_1CTL |= DAC12CALON;	
	while(DAC12_0CTL & DAC12CALON == DAC12CALON);
	while(DAC12_1CTL & DAC12CALON == DAC12CALON);
}
void  Dac_Init(void)
{
     InitDac12();									
     GoDac12(100,0);                        
     GoDac12(100,1);
     Dac12Write(0xcB2,0);
     Dac12Write(0xcB2,1);
}

void GoDac12(unsigned char doit,unsigned char which)
{
	if(doit==0)
	{
		if(which==0)
			DAC12_0CTL &= ~DAC12ENC;
		else
			DAC12_1CTL &= ~DAC12ENC;
	}
	else if(doit==100)
	{
		if(which==0)
			DAC12_0CTL |= DAC12ENC;
		else
			DAC12_1CTL |= DAC12ENC;
	}
}

void  Dac12Write(unsigned int dat,unsigned char which)
{
	if(which==0)
		DAC12_0DAT = dat;
	else 
		DAC12_1DAT = dat;
}



