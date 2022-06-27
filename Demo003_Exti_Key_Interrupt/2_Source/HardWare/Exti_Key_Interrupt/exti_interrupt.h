#ifndef __EXTI_INTERRUPT_H
#define __EXTI_INTERRUPT_H
#include "gd32f4xx.h"


void extiInterruptInit(void);
static void led_flash(uint8_t times);

#endif
