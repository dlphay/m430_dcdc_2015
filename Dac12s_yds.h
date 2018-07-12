#ifndef _DAC12
#define _DAC12

void  InitDac12();
void  Dac_Init(void);
void  GoDac12(unsigned char doit,unsigned char which);
void  Dac12Write(unsigned int dat,unsigned char which);

#endif
