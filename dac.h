#ifndef __DAC_H
#define __DAC_H

#include "stm32f4xx.h"
#include "stm32f4xx_dac.h"

void DACInit(uint32_t DAC_Channel,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
void DAC_SetValue(uint32_t DAC_Channel, uint16_t value);

#endif
