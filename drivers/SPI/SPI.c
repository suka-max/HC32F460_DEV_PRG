#include<SPI.h>

void My_SPI_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//GPIOB初始化时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//GPIOB初始化时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//GPIOB初始化时钟
  GPIO_InitStructure.GPIO_Pin = SPI_SDA | SPI_RST;  //PB3,5,7，9
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化PB
	
	GPIO_InitStructure.GPIO_Pin = SPI_SCL;  //PB3,5,7，9
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化PB
	
	GPIO_InitStructure.GPIO_Pin = SPI_DC;  //PB3,5,7，9
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化PB
}


void SPI_Write_Data(unsigned char SPI_Data)
{                        
	unsigned char i;
	Set_SPI_DC;
	for(i=0; i<8; i++)		
	{
		Reset_SPI_SCL;
		if(SPI_Data & 0x80)
			Set_SPI_SDA;
		else
			Reset_SPI_SDA;
			Set_SPI_SCL;
			SPI_Data <<=1;
	}
	Set_SPI_DC;
}

void SPI_Write_Command(unsigned char SPI_Command)
{
  unsigned char i;
	Reset_SPI_DC;
	for(i=0; i<8; i++)		
	{	Reset_SPI_SCL;
		
		if(SPI_Command & 0x80)
		{
			Set_SPI_SDA;
		}
		else
	   Reset_SPI_SDA;
		Set_SPI_SCL;
		SPI_Command <<= 1;
	}
		Set_SPI_DC;
}
