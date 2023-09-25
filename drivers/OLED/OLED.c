#include "OLED.h"
#include "font.h"

void OLED_Init(void)  //初�?�化SSD1306
{  	 
	Set_SPI_RST;
	delay_ms(100);
	Reset_SPI_RST;
	delay_ms(100);
	Set_SPI_RST; 
	SPI_Write_Command(0xae);   //关闭显示
	SPI_Write_Command(0x00);   
	SPI_Write_Command(0x10);
	SPI_Write_Command(0x40);
	SPI_Write_Command(0x81);
	SPI_Write_Command(0xcf);
	SPI_Write_Command(0xa1);
	SPI_Write_Command(0xc8);
	SPI_Write_Command(0xa6);
	SPI_Write_Command(0xa8);
	SPI_Write_Command(0x3f);
	
	SPI_Write_Command(0xD3);
	SPI_Write_Command(0x00);
	SPI_Write_Command(0xd5);
	SPI_Write_Command(0x80);
	SPI_Write_Command(0xd9);
	SPI_Write_Command(0xf1);
	SPI_Write_Command(0xda);
	SPI_Write_Command(0x12);
	SPI_Write_Command(0xdb);
	SPI_Write_Command(0x40);
	SPI_Write_Command(0x20);
	SPI_Write_Command(0x00);
	
	SPI_Write_Command(0x8d);
	SPI_Write_Command(0x14);
	
	SPI_Write_Command(0xa4);
	SPI_Write_Command(0xa6);


	SPI_Write_Command(0xaf);
} 


void OLED_DrawBMP_Full(const unsigned char BMP[])
{
	unsigned char x,y;
	const unsigned char *p;
	p=BMP;
	for(y=0;y<8;y++)
	{	
		for(x=0;x<128;x++)
		{
			SPI_Write_Data(*p);
			p++;
		}
	}
}

void OLED_DrawBMP_Full_Hor(const unsigned char BMP[])
{
	unsigned char x,y;
	const unsigned char *p;
	p=BMP;
	for(y=0;y<8;y++)
	{
	SPI_Write_Command(0xb0+y);
	SPI_Write_Command(0x10);
	SPI_Write_Command(0x00);
		
		for(x=0;x<128;x++)
		{
			SPI_Write_Data(*p);
			p++;
		}
	}
}

void OLED_Hor_mode_Start(void)
{
	SPI_Write_Command(0x20);
	SPI_Write_Command(0x00);
	SPI_Write_Command(0x21);
	SPI_Write_Command(0x00);
	SPI_Write_Command(0x7f);
	SPI_Write_Command(0x22);
	SPI_Write_Command(0x00);
	SPI_Write_Command(0x07);
}

void OLED_Fill_Screen(unsigned char dat)
{
	
	unsigned char x,y;
	for(y=0;y<8;y++)
	{
		for(x=0;x<128;x++)
		{
			SPI_Write_Data(dat);
		}
	}
}

void OLED_Fillscreen(unsigned char dat)
{
	
	unsigned char x,y;
	for(y=0;y<8;y++)
	{
			SPI_Write_Command(0xb0+y);
			SPI_Write_Command(0x10);
			SPI_Write_Command(0x00);
		for(x=0;x<128;x++)
		{
			SPI_Write_Data(dat);
		}
	}
}
void OLED_DrawBMP_FPS_Hor(unsigned int fps,const unsigned char BMP[])
{
	unsigned char x,y;
	unsigned char a,b,c;
	a=fps/100+16;
	b=fps/10%10+16;
	c=fps%10+16;
	const unsigned char *p;
	
	p=F6x8['F'-32];
		for(x=0;x<6;x++){
	SPI_Write_Data(*(p++));
	}
	p=F6x8['P'-32];
		for(x=0;x<6;x++){
	SPI_Write_Data(*(p++));

	}
	p=F6x8['S'-32];
	for(x=0;x<6;x++){
	SPI_Write_Data(*(p++));

		}
	p=F6x8[':'-32];
	p=F6x8[38];
	for(x=0;x<6;x++){
	SPI_Write_Data(*(p++));
	}
	
	p=F6x8[a];
	for(x=0;x<6;x++){
	SPI_Write_Data(*(p++));
	}
	
	p=F6x8[b];
	for(x=0;x<6;x++)
	{
	SPI_Write_Data(*(p++));
	}
	p=F6x8[c];
	for(x=0;x<6;x++){
	SPI_Write_Data(*(p++));
	}
	p=BMP;
	p+=42;
	for(x=42;x<128;x++){
	SPI_Write_Data(*(p++));
	}
	
	for(y=0;y<7;y++)
		for(x=0;x<128;x++)
		{
			SPI_Write_Data(*p);
			p++;
		}
}

void OLED_Show_String(unsigned char x,unsigned char y,unsigned char *cha)
{
	unsigned char j= 0;
	unsigned char i;
	const unsigned char *p;
	SPI_Write_Command(0xb0+y);
	SPI_Write_Command(0x10+(x >> 4));
	SPI_Write_Command(0x00+x&0x0f);
	while(cha[j]!='\0'){
		p = F6x8[cha[j]-32];
		for(i=0;i<6;i++)
		{
		SPI_Write_Data(*p);
			p++;
		}
		j++;
	}
}

void OLED_Show_4Bytes_Hex_SetPos(unsigned char posx,unsigned char posy,unsigned int num)
{
	unsigned char *a;
	const unsigned char *p;
	SPI_Write_Command(0xb0+posy);
	SPI_Write_Command(0x10+(posx >> 4));
	SPI_Write_Command(0x00+posx&0x0f);
	a = ( unsigned char * )( &num ) + 3;
	
	p=Hex6x8[ ( *a ) >> 4 ];
		for(posx=0;posx<6;posx++){
	SPI_Write_Data(*(p++));
	}
	p=Hex6x8[( *a & 0x0F ) ];
	for(posx=0;posx<6;posx++){
	SPI_Write_Data(*(p++));
	}
	a--;
	p=Hex6x8[*a >> 4 ];
	for(posx=0;posx<6;posx++){
	SPI_Write_Data(*(p++));
	}

		p=Hex6x8[*a & 0x0F ];
	for(posx=0;posx<6;posx++){
	SPI_Write_Data(*(p++));
	}
a--;
		p=Hex6x8[*a >> 4];
	for(posx=0;posx<6;posx++){
	SPI_Write_Data(*(p++));
	}
		p=Hex6x8[*a & 0x0F];
	for(posx=0;posx<6;posx++){
	SPI_Write_Data(*(p++));
	}
	a--;
		p=Hex6x8[*a >> 4];
	for(posx=0;posx<6;posx++){
	SPI_Write_Data(*(p++));
	}
		p=Hex6x8[*a & 0x0F];
	for(posx=0;posx<6;posx++){
	SPI_Write_Data(*(p++));
	}
}

/*void OLED_DrawBMP_Full_Hor(const unsigned char BMP[])
{
	unsigned char x,y;
	const unsigned char *p;
	p=BMP;
		
	SPI_Write_Command(0x20);
	SPI_Write_Command(0x00);
	SPI_Write_Command(0x21);
	SPI_Write_Command(0x00);
	SPI_Write_Command(0x7f);
	SPI_Write_Command(0x22);
	SPI_Write_Command(0x00);
	SPI_Write_Command(0x07);
	
	SPI_Start();
  SPI_Write_Byte(0x78);			// D/C#=0; R/W#=0
	SPI_Ack();	
  SPI_Write_Byte(0x40);			// write data
	SPI_Ack();
	for(y=0;y<8;y++)
		for(x=0;x<128;x++)
		{
			SPI_Write_Byte(*p);
			p++;
		Set_SPI_SCL;
		//delay_us(2);
		Reset_SPI_SCL;
		//delay_us(2);
		}
	SPI_Stop();
}*/


/*void OLED_DrawBMP_Full_Ver(const unsigned char BMP[])
{
	unsigned char x,y;
	const unsigned char *p;
	p=BMP;
	for(y=0;y<8;y++)
		for(x=0;x<128;x++)
		{
			SPI_Write_Data(*p);
			p++;
		//delay_us(2);
		Reset_SPI_SCL;
		//delay_us(2);
		}
}*/

void OLED_DrawBMP_Full_Ver_Start(void)
{
	SPI_Write_Command(0x20);
	SPI_Write_Command(0x01);
	SPI_Write_Command(0x21);
	SPI_Write_Command(0x00);
	SPI_Write_Command(0x7f);
	SPI_Write_Command(0x22);
	SPI_Write_Command(0x00);
	SPI_Write_Command(0x07);
}

void OLED_DrawBMP_Full_Ver_Con(const unsigned char BMP[]) //连续写图片，不发送SPI_Stop
{
	unsigned char x,y;
	const unsigned char *p;
	p=BMP;
	for(y=0;y<8;y++)
		for(x=0;x<128;x++)
		{
			SPI_Write_Data(*p);
			p++;
		}
}

/*void OLED_Show_3Nums(unsigned char num)
{

	unsigned char x,y;
	unsigned char a,b,c;
	a=num/100+16;
	b=num/10%10+16;
	c=num%10+16;
	const unsigned char *p2=F6x8[a],*p1=F6x8[b],*p0=F6x8[c];
	
	SPI_Write_Command(0x21);
	SPI_Write_Command(0x6e);
	SPI_Write_Command(0x7f);
	SPI_Write_Command(0x22);
	SPI_Write_Command(0x00);
	SPI_Write_Command(0x00);
		
	
	SPI_Start();
  SPI_Write_Byte(0x78);			// D/C#=0; R/W#=0
	SPI_Ack();	
  SPI_Write_Byte(0x40);			// write data
	SPI_Ack();	
		for(x=0;x<6;x++)
		{
			SPI_Write_Byte(*p2);
			p2++;
		Set_SPI_SCL;
		//delay_us(2);
		Reset_SPI_SCL;
		//delay_us(2);
	  }
		//p=num8x6+b*6;
				for(x=0;x<6;x++)
		{
			SPI_Write_Byte(*p1);
			p1++;
					Set_SPI_SCL;
		//delay_us(2);
		Reset_SPI_SCL;
		//delay_us(2);
	  }
		//p=num8x6+c*6;
				for(x=0;x<6;x++)
		{
			SPI_Write_Byte(*p0);
			p0++;
					Set_SPI_SCL;
		//delay_us(2);
		Reset_SPI_SCL;
		//delay_us(2);
	  }
	SPI_Stop();
}

void OLED_Show_Num(unsigned char num)
{
	unsigned char x;
	SPI_Write_Command(0x20);
	SPI_Write_Command(0x01);
	SPI_Write_Command(0x21);
	SPI_Write_Command(0x6e);
	SPI_Write_Command(0x7f);
	SPI_Write_Command(0x22);
	SPI_Write_Command(0x04);
	SPI_Write_Command(0x04);
	const unsigned char *p;
	num=num+16;
	p=F6x8[num];
	SPI_Start();
  SPI_Write_Byte(0x78);			// D/C#=0; R/W#=0
	SPI_Ack();
  SPI_Write_Byte(0x40);			// write data
	SPI_Ack();
		for(x=0;x<6;x++)
	{
		SPI_Write_Byte(*p);
			p++;
		Set_SPI_SCL;
		//delay_us(2);
		Reset_SPI_SCL;
		//delay_us(2);
	}
	SPI_Stop();
}
*/
void OLED_DrawBMP_FPS_Hor_Start(void)
{
	SPI_Write_Command(0x20);
	SPI_Write_Command(0x00);
	SPI_Write_Command(0x21);
	SPI_Write_Command(0x00);
	SPI_Write_Command(0x7f);
	SPI_Write_Command(0x22);
	SPI_Write_Command(0x00);
	SPI_Write_Command(0x07);
}
