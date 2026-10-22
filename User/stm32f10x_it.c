#include "stm32f10x_it.h"
#include "bsp_sys.h"

void NMI_Handler(void)        { while (1); }
void MemManage_Handler(void)  { while (1); }
void BusFault_Handler(void)   { while (1); }
void UsageFault_Handler(void) { while (1); }
void SVC_Handler(void)        {}
void DebugMon_Handler(void)   {}
void PendSV_Handler(void)     {}

void HardFault_Handler(void)
{
    while (1);
}

/* 1ms 系统节拍: 喂给 LVGL 和延时函数 */
void SysTick_Handler(void)
{
    BSP_SysTickHook();
}
