#include "msp430x16x.h"
#include  "Ta12_Pwm_yds.h"


void TA12PWM_One0(uint TA0,uint TA1)  {
    TACTL   |= MC_1 + TASSEL_2;
    TACCTL1  = OUTMOD_7;
    TACCTL2  = OUTMOD_7;
    TACCR0 = TA0; 
    TACCR1 = TA1; 
}
void TA12PWM_One1(uint TA0,uint TA2)  {
    TACTL   |= MC_1 + TASSEL_2;
    TACCTL1  = OUTMOD_7;
    TACCTL2  = OUTMOD_7;
    TACCR0 = TA0; 
    TACCR2 = TA2; 
}
void TA12PWM_Two(uint TA0,uint TA1,uint TA2)  {
    TACTL   |= MC_1 + TASSEL_2;
    TACCTL1  = OUTMOD_7;
    TACCTL2  = OUTMOD_7;
    TACCR0 = TA0; 
    TACCR1 = TA1; 
    TACCR2 = TA2;
}
void TB12PWM_One(uint TB0,uint TB1)  {
    TBCTL   |= MC_1 + TBSSEL_2;
    TBCCTL1  = OUTMOD_7;
    TBCCTL2  = OUTMOD_7;
    TBCCR0 = TB0; 
    TBCCR1 = TB1; 
}
void TB12PWM_Two(uint TB0,uint TB1,uint TB2)  {
    TBCTL   |= MC_1 + TBSSEL_2;
    TBCCTL1  = OUTMOD_7;
    TBCCTL2  = OUTMOD_7;
    TBCCR0 = TB0; 
    TBCCR1 = TB1; 
    TBCCR2 = TB2;
}
void TB12PWM_Three(uint TB0,uint TB1,uint TB2,uint TB3)  {
    TBCTL   |= MC_1 + TBSSEL_2;
    TBCCTL1  = OUTMOD_7;
    TBCCTL2  = OUTMOD_7;
    TBCCR0 = TB0; 
    TBCCR1 = TB1; 
    TBCCR2 = TB2;
    TBCCR3 = TB3; 
}
void TB12PWM_Four(uint TB0,uint TB1,uint TB2,uint TB3,uint TB4)  {
    TBCTL   |= MC_1 + TBSSEL_2;
    TBCCTL1  = OUTMOD_7;
    TBCCTL2  = OUTMOD_7;
    TBCCR0 = TB0; 
    TBCCR1 = TB1; 
    TBCCR2 = TB2;
    TBCCR3 = TB3; 
    TBCCR4 = TB4; 
}
void TB12PWM_Five(uint TB0,uint TB1,uint TB2,uint TB3,uint TB4,uint TB5) {
    TBCTL   |= MC_1 + TBSSEL_2;
    TBCCTL1  = OUTMOD_7;
    TBCCTL2  = OUTMOD_7;
    TBCCR0 = TB0; 
    TBCCR1 = TB1; 
    TBCCR2 = TB2;
    TBCCR3 = TB3; 
    TBCCR4 = TB4; 
    TBCCR5 = TB5;
}
void TB12PWM_Six(uint TB0,uint TB1,uint TB2,uint TB3,uint TB4,uint TB5,uint TB6) {
    TBCTL   |= MC_1 + TBSSEL_2;
    TBCCTL1  = OUTMOD_7;
    TBCCTL2  = OUTMOD_7;
    TBCCR0 = TB0; 
    TBCCR1 = TB1; 
    TBCCR2 = TB2;
    TBCCR3 = TB3; 
    TBCCR4 = TB4; 
    TBCCR5 = TB5;
    TBCCR6 = TB6;
}