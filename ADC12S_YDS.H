 #ifndef __ADC12_YDS_H__
#define __ADC12_YDS_H__
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long
extern void Data_do(uint temp_d);
extern void Voltage_do2_Mode0(uint temp_d);
extern void Voltage_do2_Mode1(uint temp_d);
extern void Voltage_do2_Mode2(uint temp_d);
extern void Voltage_do3_Mode0(uint temp_d);
extern void Voltage_do3_Mode1(uint temp_d);
extern void Voltage_do3_Mode2(uint temp_d);
extern void Voltage_do4_Mode0(uint temp_d);
extern void Current_do0_Mode0(uint temp_d);
extern void Current_do0_Mode1(uint temp_d);
extern void Current_do0_Mode2(uint temp_d);
extern void Current_do1_Mode0(uint temp_d);
extern void Current_do1_Mode1(uint temp_d);
extern void Current_do1_Mode2(uint temp_d);
extern void Adc_Delay(void);
extern void LCD_DisplayADC0();
extern void LCD_DisplayADC1();
extern void LCD_DisplayVoltage2();
extern void LCD_DisplayVoltage3();
extern void Adc_Init(void);
extern void DDDD_Mode0(int Actual_Value);
extern void DDDD_Mode1(int Actual_Value);
extern void DDDD_Mode2(int Actual_Value);
#endif



