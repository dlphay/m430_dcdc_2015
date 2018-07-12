#ifndef __TA12_PWM_YDS_H__
#define __TA12_PWM_YDS_H__
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long
void TA12PWM_One0(uint TA0,uint TA1)  ;
void TA12PWM_One1(uint TA0,uint TA2) ;
void TA12PWM_Two(uint TA0,uint TA1,uint TA2)  ;
void TB12PWM_One(uint TB0,uint TB1)  ;
void TB12PWM_Two(uint TB0,uint TB1,uint TB2);  
void TB12PWM_Three(uint TB0,uint TB1,uint TB2,uint TB3)  ;
void TB12PWM_Four(uint TB0,uint TB1,uint TB2,uint TB3,uint TB4);  
void TB12PWM_Five(uint TB0,uint TB1,uint TB2,uint TB3,uint TB4,uint TB5) ; 
void TB12PWM_Six(uint TB0,uint TB1,uint TB2,uint TB3,uint TB4,uint TB5,uint TB6);  
#endif

