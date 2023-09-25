#ifndef __SPI_H
#define __SPI_H
#include<delay.h>
#include<stm32f4xx_gpio.h>


#define SPI_SCL GPIO_Pin_15  //SCL接PB3
#define SPI_SDA GPIO_Pin_10  //SDA接PB5
#define SPI_RST GPIO_Pin_8  //RST接PB7
#define SPI_DC GPIO_Pin_14  //DC接PB9

#define Reset_SPI_SCL GPIO_ResetBits(GPIOB,GPIO_Pin_15)
#define Set_SPI_SCL GPIO_SetBits(GPIOB,GPIO_Pin_15)

#define Reset_SPI_SDA GPIO_ResetBits(GPIOD,GPIO_Pin_10)
#define Set_SPI_SDA GPIO_SetBits(GPIOD,GPIO_Pin_10)

#define Reset_SPI_RST GPIO_ResetBits(GPIOD,GPIO_Pin_8)
#define Set_SPI_RST GPIO_SetBits(GPIOD,GPIO_Pin_8)

#define Reset_SPI_DC GPIO_ResetBits(GPIOE,GPIO_Pin_14)
#define Set_SPI_DC GPIO_SetBits(GPIOE,GPIO_Pin_14)


void My_SPI_Init(void);
void SPI_Write_Data(unsigned char);
void SPI_Write_Command(unsigned char);

#endif
