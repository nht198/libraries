#ifndef __I2C_H 
#define __I2C_H
#include "stm32f4xx.h"
#include "stm32f4xx_i2c.h"

void I2C_config(uint32_t RCC_APB1Periph, uint32_t RCC_AHB1Periph,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,uint16_t GPIO_PinSourceSCL,
								uint16_t GPIO_PinSourceSDA,uint8_t GPIO_AF, I2C_TypeDef* I2Cx);
void I2C_start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction);
void I2C_write(I2C_TypeDef* I2Cx, uint8_t data);
uint8_t I2C_read_ack(I2C_TypeDef* I2Cx);
uint8_t I2C_read_nack(I2C_TypeDef* I2Cx);
void I2C_stop(I2C_TypeDef* I2Cx);

#endif
