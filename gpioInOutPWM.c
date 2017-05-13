#include "gpioInOutPWM.h"


GPIO_InitTypeDef GPIO_InitDef;
/*Define Output GPIO*/
void GPIOInitOutput(uint32_t RCC_AHB1Periph,GPIO_TypeDef* GPIOx,uint16_t GPIOPin)
{
	//GPIO_InitTypeDef GPIO_InitDef;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph, ENABLE);

	GPIO_InitDef.GPIO_Pin = GPIOPin;
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;
	//Initialize pins
	GPIO_Init(GPIOx, &GPIO_InitDef);
}
/*Define Input GPIO*/
void GPIOInitInput(uint32_t RCC_AHB1Periph,GPIO_TypeDef* GPIOx,uint16_t GPIOPin)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph, ENABLE);

	GPIO_InitDef.GPIO_Pin = GPIOPin;
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;
	//Initialize pins
	GPIO_Init(GPIOx, &GPIO_InitDef);
}

/**
  * @param  RCC_AHBPeriph: specifies the AHB1 peripheral to gates its clock for GPIO and Timer
  * @param  GPIOx = A, B, C, D, E,..
  * @param  GPIO_PinSource (0..15)
  * @param  GPIO_AF = GPIO_AFSelection
  * @param  GPIO_Pin
  *
*/
void TIM_config(uint32_t RCC_AHB1Periph,GPIO_TypeDef* GPIOx,uint16_t GPIO_PinSource,uint8_t GPIO_AF,uint16_t GPIO_Pin)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    /* Enable Clock for GPIO and Timer */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph, ENABLE);
    /* Alternating functions for pins */
    GPIO_PinAFConfig(GPIOx, GPIO_PinSource, GPIO_AF);    
    /* Set pins */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOx, &GPIO_InitStruct);
}
    TIM_OCInitTypeDef TIM_OCStruct;
void PWM_config(uint32_t RCC_AHB1Periph,TIM_TypeDef* TIMx,uint8_t channel,uint16_t Prescale_value, uint16_t TIM_PeriodValue)
{
  // TM_TIMER_Init
    TIM_TimeBaseInitTypeDef TIM_BaseStruct;
	    /* Enable clock for TIM4 */
    RCC_APB1PeriphClockCmd(RCC_AHB1Periph, ENABLE);
    /*    
    TIM4 is connected to APB1 bus, which has on F407 device 42MHz clock                 
    But, timer has internal PLL, which double this frequency for timer, up to 84MHz     
    Remember: Not each timer is connected to APB1, there are also timers connected     
    on APB2, which works at 84MHz by default, and internal PLL increase                 
    this to up to 168MHz                                                             
    Set timer prescaller 
    Timer count frequency is set with 
    timer_tick_frequency = Timer_default_frequency / (prescaller_set + 1)          
    In our case, we want a max frequency for timer, so we set prescaller to 0         
    And our timer will have tick frequency        
    timer_tick_frequency = 84000000 / (0 + 1) = 84000000 
*/    
    TIM_BaseStruct.TIM_Prescaler = Prescale_value;
    /* Count up */
    TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
/*
    Set timer period when it have reset
    First you have to know max value for timer
    In our case it is 16bit = 65535
    To get your frequency for PWM, equation is simple   
    PWM_frequency = timer_tick_frequency / (TIM_Period + 1)   
    If you know your PWM frequency you want to have timer period set correct   
    TIM_Period = timer_tick_frequency / PWM_frequency - 1  
    In our case, for 10Khz PWM_frequency, set Period to  
    TIM_Period = 84000000 / 10000 - 1 = 8399
    If you get TIM_Period larger than max timer value (in our case 65535),
    you have to choose larger prescaler and slow down timer tick frequency
*/
    TIM_BaseStruct.TIM_Period = TIM_PeriodValue; /* 10kHz PWM */
    TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseStruct.TIM_RepetitionCounter = 0;
    /* Initialize TIMx */
    TIM_TimeBaseInit(TIMx, &TIM_BaseStruct);
		TIM_Cmd(TIMx, ENABLE);
    /* Common settings */
    /* PWM mode 2 = Clear on compare match */
    /* PWM mode 1 = Set on compare match */
    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
		/*
    To get proper duty cycle, you have simple equation
    pulse_length = ((TIM_Period + 1) * DutyCycle) / 100 - 1
    where DutyCycle is in percent, between 0 and 100% 
    25% duty cycle:     pulse_length = ((8399 + 1) * 25) / 100 - 1 = 2099
    50% duty cycle:     pulse_length = ((8399 + 1) * 50) / 100 - 1 = 4199
    75% duty cycle:     pulse_length = ((8399 + 1) * 75) / 100 - 1 = 6299
    100% duty cycle:    pulse_length = ((8399 + 1) * 100) / 100 - 1 = 8399
   Remember: if pulse_length is larger than TIM_Period, you will have output HIGH all the time
*/
    /* Start count on TIMx */
		if(channel == 1) {
			TIM_OCStruct.TIM_Pulse = 0; /* 0% duty cycle */
			TIM_OC1Init(TIMx, &TIM_OCStruct);
			TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
		}
		if(channel == 2) {
			TIM_OCStruct.TIM_Pulse = 0; /* 0% duty cycle */
			TIM_OC2Init(TIMx, &TIM_OCStruct);
			TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
		}
		if(channel == 3) {
			TIM_OCStruct.TIM_Pulse = 0; /* 0% duty cycle */
			TIM_OC3Init(TIMx, &TIM_OCStruct);
			TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
		}
		if(channel == 4) {
			TIM_OCStruct.TIM_Pulse = 0; /* 0% duty cycle */
			TIM_OC4Init(TIMx, &TIM_OCStruct);
			TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
		}		
}

void PWM_SetDC(TIM_TypeDef* TIMx,uint8_t channel,uint16_t dutycycle)
{
	if (channel == 1)
  {
    TIMx->CCR1 = dutycycle;
  }
  else if (channel == 2)
  {
    TIMx->CCR2 = dutycycle;
  }
  else if (channel == 3)
  {
    TIMx->CCR3 = dutycycle;
  }
  else
  {
    TIMx->CCR4 = dutycycle;
  }
}
