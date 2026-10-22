#include "bsp_sys.h"
#include "lvgl.h"

static volatile uint32_t s_tick = 0;

void BSP_SysTickInit(void)
{
    /* 72MHz / 1000 = 1ms 中断一次 */
    SysTick_Config(SystemCoreClock / 1000);
}

/* 由 stm32f10x_it.c 的 SysTick_Handler 调用 */
void BSP_SysTickHook(void)
{
    s_tick++;
    lv_tick_inc(1);
}

uint32_t BSP_GetTick(void)
{
    return s_tick;
}

void BSP_DelayMs(uint32_t ms)
{
    uint32_t start = s_tick;
    while ((s_tick - start) < ms)
    {
    }
}
