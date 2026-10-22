#ifndef __BSP_SYS_H
#define __BSP_SYS_H

#include "stm32f10x.h"

void BSP_SysTickInit(void);
void BSP_SysTickHook(void);
uint32_t BSP_GetTick(void);
void BSP_DelayMs(uint32_t ms);

#endif
