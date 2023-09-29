#ifndef __SPI_H
#define __SPI_H

#include "hc32_ll.h"

#define SPI_SCL_PORT GPIO_PORT_C  //SCL接PB3
#define SPI_SDA_PORT GPIO_PORT_H  //SDA接PB5
#define SPI_RST_PORT GPIO_PORT_B  //RST接PB7
#define SPI_DC_PORT GPIO_PORT_B  //DC接PB9


#define SPI_SCL GPIO_PIN_13  //SCL接PB3
#define SPI_SDA GPIO_PIN_02  //SDA接PB5
#define SPI_RST GPIO_PIN_09  //RST接PB7
#define SPI_DC GPIO_PIN_08  //DC接PB9

#define Reset_SPI_SCL GPIO_ResetPins(SPI_SCL_PORT,SPI_SCL)
#define Set_SPI_SCL GPIO_SetPins(SPI_SCL_PORT,SPI_SCL)

#define Reset_SPI_SDA GPIO_ResetPins(SPI_SDA_PORT,SPI_SDA)
#define Set_SPI_SDA GPIO_SetPins(SPI_SDA_PORT,SPI_SDA)

#define Reset_SPI_RST GPIO_ResetPins(SPI_RST_PORT,SPI_RST)
#define Set_SPI_RST GPIO_SetPins(SPI_RST_PORT,SPI_RST)

#define Reset_SPI_DC GPIO_ResetPins(SPI_DC_PORT,SPI_DC)
#define Set_SPI_DC GPIO_SetPins(SPI_DC_PORT,SPI_DC)


void My_SPI_Init(void);
void OLED_SPI_Write_Data(unsigned char);
void OLED_SPI_Write_Command(unsigned char);

#endif
