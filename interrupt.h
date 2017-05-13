#ifndef __INTERRUPT_H
#define __INTERRUPT_H

#include "stm32f4xx.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"


void EXT_config(uint32_t RCC_AHB1Periph,GPIO_TypeDef* GPIOx,uint16_t GPIOPin,uint8_t EXTI_PortSourceGPIOx,
								uint8_t EXTI_PinSourcex,uint32_t EXTI_LineNumber,uint8_t NVIC_IRQChannel);

#endif
