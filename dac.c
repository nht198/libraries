#include "dac.h"

void DACInit(uint32_t DAC_Channel,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
	DAC_InitTypeDef DAC_InitStruct;
	GPIO_InitTypeDef GPIO_InitDef;
	//GPIO_InitTypeDef GPIO_InitDef;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitDef.GPIO_Pin = GPIO_Pin;
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;
	//Initialize pins
	GPIO_Init(GPIOx, &GPIO_InitDef);
	
	/* Enable DAC clock */
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;
	
	/* Set DAC options */
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	
	/* Init and enable proper DAC */
	if (DAC_Channel == DAC_Channel_1) {
		DAC_Init(DAC_Channel_1, &DAC_InitStruct);
		/* Enable DAC channel 1 */
		DAC->CR |= DAC_CR_EN1;
	} else {
		DAC_Init(DAC_Channel_2, &DAC_InitStruct);
		/* Enable DAC channel 2 */
		DAC->CR |= DAC_CR_EN2;
	}
}

void DAC_SetValue(uint32_t DAC_Channel, uint16_t value) {
	/* Check value */
	if (value > 4095) {
		value = 4095;
	}
	
	/* Set 12-bit value, right aligned */
	if (DAC_Channel == DAC_Channel_1) {
		DAC->DHR12R1 = value;
	} else {
		DAC->DHR12R2 = value;
	}
}
