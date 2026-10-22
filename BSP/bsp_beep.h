#ifndef __BSP_BEEP_H
#define __BSP_BEEP_H

#include "stm32f10x.h"

#define BEEP_GPIO_PORT  GPIOB
#define BEEP_GPIO_PIN   GPIO_Pin_8
#define BEEP_GPIO_CLK   RCC_APB2Periph_GPIOB

void BSP_Beep_Init(void);
void BSP_Beep_On(void);
void BSP_Beep_Off(void);

#endif
