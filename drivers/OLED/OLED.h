#ifndef _OLED_H
#define _OLED_H
#include "sys.h"
#include "SPI.h"

//#define SCL PBout(6) //串行时钟
//#define SDA PBout(7) //串行数据
#define	OLED_CMD	0
#define	OLED_DATA	1
#define	Brightness	0xCF 
#define X_WIDTH 	128
#define Y_WIDTH 	64
//void OLED_GPIO_Init(void);
//void IIC_Start(void);// -- 开启I2C总线
//void IIC_Stop(void);// -- 关闭I2C总线
// 通过I2C总线写一个byte的数据void OLED_WrDat(unsigned char dat);// -- 向OLED屏写数据
void OLED_Init(void);// -- OLED屏初始化程序，此函数应在操作屏幕之前最先调用
void OLED_Init_Ver(void);  //初始化SSD1306
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);// -- 6x8点整，用于显示ASCII码的最小阵列，不太清晰
void OLED_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[]);// -- 8x16点整，用于显示ASCII码，非常清晰
void OLED_P16x16Ch(unsigned char x,unsigned char y,unsigned int N);// -- 16x16点整，用于显示汉字的最小阵列，可设置各种字体、加粗、倾斜、下划线等
void Draw_BMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);// -- 将128x64像素的BMP位图在取字软件中算出字表，然后复制到codetab中，此函数调用即可
void OLED_DrawBMP_Full(const unsigned char BMP[]);
void OLED_DrawBMP_Full_Hor(const unsigned char BMP[]);
void OLED_DrawBMP_Full_Ver(const unsigned char BMP[]);
void OLED_DrawBMP_Full_Ver_Start(void);
void OLED_DrawBMP_Full_Ver_Con(const unsigned char BMP[]);
void OLED_Fillscreen(unsigned char);
void OLED_Show_Num(unsigned char);
void OLED_Show_3Nums(unsigned char);
void OLED_DrawBMP_FPS_Hor(unsigned int fps,const unsigned char BMP[]);
void OLED_DrawBMP_FPS_Hor_Start(void);
void OLED_Fill_Screen(unsigned char dat);
void OLED_Hor_mode_Start(void);
void OLED_Init1(void) ;
void OLED_Show_String(unsigned char x,unsigned char y,unsigned char *cha);
void OLED_Show_4Bytes_Hex_SetPos(unsigned char posx,unsigned char posy,unsigned int num);



#endif
