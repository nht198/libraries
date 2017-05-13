#ifndef __GPIOINOUTPWM_H
#define __GPIOINOUTPWM_H

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"

void GPIOInitOutput(uint32_t RCC_AHB1Periph,GPIO_TypeDef* GPIOx,uint16_t GPIOPin);
void GPIOInitInput(uint32_t RCC_AHB1Periph,GPIO_TypeDef* GPIOx,uint16_t GPIOPin);
/*for PWM*/
void TIM_config(uint32_t RCC_AHB1Periph,GPIO_TypeDef* GPIOx,uint16_t GPIO_PinSource,uint8_t GPIO_AF,uint16_t GPIO_Pin);
void PWM_config(uint32_t RCC_AHB1Periph,TIM_TypeDef* TIMx,uint8_t channel,uint16_t Prescale_value, uint16_t TIM_PeriodValue);
void PWM_SetDC(TIM_TypeDef* TIMx,uint8_t channel,uint16_t dutycycle);

#endif
