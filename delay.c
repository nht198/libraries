#include "delay.h"

uint32_t multiplier;
 
void delayInit(void) {
	/* Make sure System init called first*/
    RCC_ClocksTypeDef RCC_Clocks;
    
    /* Get system clocks */
    RCC_GetClocksFreq(&RCC_Clocks);
    
    /* While loop takes 4 cycles */
    /* For 1 us delay, we need to divide with 4M */
    multiplier = RCC_Clocks.HCLK_Frequency / 4000000;
}
 
void delayMicros(uint32_t micros) {
    /* Multiply micros with multipler */
    /* Substract 10 */
    micros = micros * multiplier - 10;
    /* 4 cycles for one loop */
    while (micros--);
}
 
void delayMillis(uint32_t millis) {
    /* Multiply millis with multipler */
    /* Substract 10 */
    millis = 1000 * millis * multiplier - 10;
    /* 4 cycles for one loop */
    while (millis--);
}
