#ifndef __ADC_H
#define __ADC_H

#include "stm32f4xx.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

void ADCInit(uint32_t RCC_APB2Periph,uint32_t RCC_AHB1Periph,ADC_TypeDef* ADCx, uint8_t ADC_Channel,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t ADC_Read(ADC_TypeDef* ADCx, uint8_t ADC_Channel);
	
#endif

