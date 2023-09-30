#ifndef _OLED_H
#define _OLED_H
#include "SPI.h"

//#define SCL PBout(6) //����ʱ��
//#define SDA PBout(7) //��������
#define	OLED_CMD	0
#define	OLED_DATA	1
#define	Brightness	0xCF 
#define X_WIDTH 	128
#define Y_WIDTH 	64
//void OLED_GPIO_Init(void);
//void IIC_Start(void);// -- ����I2C����
//void IIC_Stop(void);// -- �ر�I2C����
// ͨ��I2C����дһ��byte������void OLED_WrDat(unsigned char dat);// -- ��OLED��д����
void OLED_Init(void);// -- OLED����ʼ�����򣬴˺���Ӧ�ڲ�����Ļ֮ǰ���ȵ���
void OLED_Init_Ver(void);  //��ʼ��SSD1306
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);// -- 6x8������������ʾASCII�����С���У���̫����
void OLED_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[]);// -- 8x16������������ʾASCII�룬�ǳ�����
void OLED_P16x16Ch(unsigned char x,unsigned char y,unsigned int N);// -- 16x16������������ʾ���ֵ���С���У������ø������塢�Ӵ֡���б���»��ߵ�
void Draw_BMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);// -- ��128x64���ص�BMPλͼ��ȡ������������ֱ���Ȼ���Ƶ�codetab�У��˺������ü���
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
void OLED_Show_String(unsigned char x,unsigned char y,char *cha);
void OLED_Show_4Bytes_Hex_SetPos(unsigned char posx,unsigned char posy,unsigned int num);

void Oled_Fill_Page(unsigned char Page, unsigned char dat);

#endif
