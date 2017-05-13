#ifndef __DELAY_H
#define __DELAY_H
/* Include core modules */
#include "stm32f4xx.h"

void delayInit(void);
void delayMicros(uint32_t micros);
void delayMillis(uint32_t millis);

#endif  /*__DELAY_H*/
