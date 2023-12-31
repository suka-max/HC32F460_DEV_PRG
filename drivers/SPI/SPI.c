#include "SPI.h"

#define SOFTWARE_SPI 0

#define HARDWARE_SPI 1


#if SOFTWARE_SPI
void My_SPI_Init(void)
{
	stc_gpio_init_t stcGpioInit;

	GPIO_StructInit( &stcGpioInit );
	stcGpioInit.u16PinState = PIN_STAT_RST;
	stcGpioInit.u16PinDir = PIN_DIR_OUT;
  	stcGpioInit.u16PinAttr = PIN_ATTR_DIGITAL;
	GPIO_Init( SPI_SCL_PORT, SPI_SCL, &stcGpioInit );
	GPIO_Init( SPI_SDA_PORT, SPI_SDA, &stcGpioInit );
	GPIO_Init( SPI_RST_PORT, SPI_RST, &stcGpioInit );
	GPIO_Init( SPI_DC_PORT, SPI_DC, &stcGpioInit );
}
#elif HARDWARE_SPI
void My_SPI_Init(void)
{
	stc_spi_init_t stcSpiInit;
	stc_gpio_init_t stcGpioInit;

	GPIO_StructInit( &stcGpioInit );

	stcGpioInit.u16PinState = PIN_STAT_RST;
	stcGpioInit.u16PinDir = PIN_DIR_OUT;
	stcGpioInit.u16PinAttr = PIN_ATTR_DIGITAL;

	GPIO_Init( SPI_RST_PORT, SPI_RST, &stcGpioInit );
	GPIO_Init( SPI_DC_PORT, SPI_DC, &stcGpioInit );


	GPIO_SetFunc(SPI_SCL_PORT,  SPI_SCL,  GPIO_FUNC_43);
    GPIO_SetFunc(SPI_SDA_PORT, SPI_SDA, GPIO_FUNC_40);

	FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_SPI3, ENABLE);

	SPI_StructInit(&stcSpiInit);

	stcSpiInit.u32WireMode          = SPI_3_WIRE;
	stcSpiInit.u32TransMode         = SPI_SEND_ONLY;
	stcSpiInit.u32MasterSlave       = SPI_MASTER;
	stcSpiInit.u32Parity            = SPI_PARITY_INVD;
	stcSpiInit.u32SpiMode           = SPI_MD_3;
	stcSpiInit.u32BaudRatePrescaler = SPI_BR_CLK_DIV2;
	stcSpiInit.u32DataBits          = SPI_DATA_SIZE_8BIT;
    stcSpiInit.u32FirstBit          = SPI_FIRST_MSB;
    stcSpiInit.u32FrameLevel        = SPI_1_FRAME;

	SPI_Init(CM_SPI3, &stcSpiInit);

    SPI_Cmd(CM_SPI3, ENABLE);
}
#endif

void OLED_SPI_Write_Data( unsigned char SPI_Data )
{                        
	unsigned char i;

	Set_SPI_DC;

	#if SOFTWARE_SPI
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
	#else
	while ( RESET == SPI_GetStatus( CM_SPI3, SPI_FLAG_TX_BUF_EMPTY ) ) 
	{
		;
	}

	SPI_WriteData( CM_SPI3, ( uint32_t )SPI_Data );

	while ( RESET == SPI_GetStatus( CM_SPI3, SPI_FLAG_IDLE ) ) 
	{
		;
	}
	#endif

	Set_SPI_DC;
}

void OLED_SPI_Write_Command( unsigned char SPI_Command )
{
  	unsigned char i;

	Reset_SPI_DC;

	#if SOFTWARE_SPI
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
	#else   
	while (RESET == SPI_GetStatus(CM_SPI3, SPI_FLAG_TX_BUF_EMPTY)) 
	{
		;
    }

	SPI_WriteData(CM_SPI3, ( uint32_t )SPI_Command);

	while (RESET == SPI_GetStatus(CM_SPI3, SPI_FLAG_IDLE)) 
	{
		;
	}
	#endif
}
