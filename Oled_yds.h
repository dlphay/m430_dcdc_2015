//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//  文 件 名   : oled.h
//  版 本 号   : v2.0
//  作    者   : 
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : OLED 接口演示例程(MSP430F149系列)
//              说明: 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   P13（SCL）
//              D1   P14（SDA）
//              RES  接P12
//              DC   接P11
//              CS   接P10 ----本模块已经帮用户接地，无需再接              
//              ----------------------------------------------------------------
//******************************************************************************/
#ifndef __OLED_YDS_H
#define __OLED_YDS_H			  	 
#include	<msp430x16x.h>
//#include	<in430.h>
#include	<intrinsics.h> 
#define  u8 unsigned char 
#define  u32 unsigned int 
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据



#define		Set_Bit(val, bitn)		(val |= (/*1 <<*/(bitn)))		//竚琘 1
#define		Clr_Bit(val, bitn)		(val &= ~(/*1<<*/(bitn)))		//竚琘 0
#define		Get_Bit(val, bitn)		(val & (1<<(bitn)) )		//眔琘
//----------------------------------------------------------------------------------
//OLED SSD1306 SPI  时钟D0
//#define		OLED_SSD1306_SCLK_DIR			(P3DIR)
//#define		OLED_SSD1306_SCLK_OUT			(P3OUT)
#define		        OLED_SSD1306_SCLK_PIN_NUM		(BIT3)

#define		OLED_SSD1306_SCLK_IO_INIT		(Set_Bit(P3DIR,OLED_SSD1306_SCLK_PIN_NUM))
#define		OLED_SCLK_Set()			        (Set_Bit(P3OUT,OLED_SSD1306_SCLK_PIN_NUM))
#define		OLED_SCLK_Clr()				(Clr_Bit(P3OUT,OLED_SSD1306_SCLK_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 SPI 数据D1
//#define		OLED_SSD1306_SDIN_DIR			(P3DIR)
//#define		OLED_SSD1306_SDIN_OUT			(P3OUT)
#define		OLED_SSD1306_SDIN_PIN_NUM		(BIT0)

#define		OLED_SSD1306_SDIN_IO_INIT		(Set_Bit(P3DIR,OLED_SSD1306_SDIN_PIN_NUM))
#define		OLED_SDIN_Set()				(Set_Bit(P3OUT,OLED_SSD1306_SDIN_PIN_NUM))
#define		OLED_SDIN_Clr()			        (Clr_Bit(P3OUT,OLED_SSD1306_SDIN_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 数据/命令DC
//#define		OLED_SSD1306_DC_DIR				(P3DIR)
//#define		OLED_SSD1306_DC_OUT				(P3OUT)
#define		OLED_SSD1306_DC_PIN_NUM			(BIT2)

#define		OLED_SSD1306_DC_IO_INIT			(Set_Bit(P3DIR,OLED_SSD1306_DC_PIN_NUM))
#define		OLED_DC_Set()				(Set_Bit(P3OUT,OLED_SSD1306_DC_PIN_NUM))
#define		OLED_DC_Clr() 				(Clr_Bit(P3OUT,OLED_SSD1306_DC_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 片选CS
//#define		OLED_SSD1306_CE_DIR				(P3DIR)
//#define		OLED_SSD1306_CE_OUT				(P3OUT)
#define		OLED_SSD1306_CE_PIN_NUM			(BIT0)

#define		OLED_SSD1306_CE_IO_INIT			(Set_Bit(P3DIR,OLED_SSD1306_CE_PIN_NUM))
#define		OLED_CS_Set()				(Set_Bit(P3OUT,OLED_SSD1306_CE_PIN_NUM))
#define		OLED_CS_Clr()				(Clr_Bit(P3OUT,OLED_SSD1306_CE_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 复位/RES
//#define		OLED_SSD1306_RST_DIR			(P3DIR)
//#define		OLED_SSD1306_RST_OUT			(P3OUT)
#define		OLED_SSD1306_RST_PIN_NUM		(BIT1)

#define		OLED_SSD1306_RST_IO_INIT		(Set_Bit(P3DIR,OLED_SSD1306_RST_PIN_NUM))
#define		OLED_RST_Set()				(Set_Bit(P3OUT,OLED_SSD1306_RST_PIN_NUM))
#define		OLED_RST_Clr()				(Clr_Bit(P3OUT,OLED_SSD1306_RST_PIN_NUM))

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED端口定义----------------  					   

//void delay_ms(unsigned int ms);


//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2);
void OLED_ShowString(u8 x,u8 y, u8 *p);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
#endif  
	 



