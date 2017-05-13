#ifndef __UART_H
#define __UART_H

#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"


void UART_Init(USART_TypeDef* USARTx,uint32_t RCC_APBUART,uint32_t RCC_AHB1GPIO,uint32_t baudrate,GPIO_TypeDef* GPIOx,
					uint16_t GPIO_PinSourceTx,uint16_t GPIO_PinSourceRx,uint8_t GPIO_AF,
					uint16_t GPIO_Pin,uint8_t NVIC_IRQChannel);
void USART_puts(USART_TypeDef* USARTx, volatile char *s);

#endif