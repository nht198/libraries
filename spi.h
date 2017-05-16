#ifndef __SPI_H 
#define __SPI_H

#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"

void SPI_config(uint32_t RCC_APB_SPI,uint32_t RCC_AHB_SPI,GPIO_TypeDef* GPIOx_SPI,GPIO_TypeDef* GPIOx_CS,uint16_t GPIO_PinSPI,uint16_t GPIO_PinCS,
				uint16_t GPIO_PinSourceSCK,uint16_t GPIO_PinSourceMISO,uint16_t GPIO_PinSourceMOSI,uint8_t GPIO_AF,SPI_TypeDef* SPIx);
void SPI_send(SPI_TypeDef* SPIx,uint8_t address, uint8_t data);
uint8_t SPI_read(SPI_TypeDef* SPIx,uint8_t address);

#endif
