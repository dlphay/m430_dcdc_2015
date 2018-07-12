#ifndef __KEY_YDS_H__
#define __KEY_YDS_H__
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long
#define   keyin   (P1IN & 0xf0)


extern  uint    Mode_Count;
extern  uint    BuJin_Count;
void add(unsigned int i);
void P14_key(void);
void P15_key(void);
void P16_key(void);
void P17_key(void);
void delay(void);
#endif


