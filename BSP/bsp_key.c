#include "bsp_key.h"

void BSP_Key_Init(void)
{
    GPIO_InitTypeDef gpio;
    RCC_APB2PeriphClockCmd(KEY_GPIO_CLK, ENABLE);
    gpio.GPIO_Pin   = KEY_PREV_PIN | KEY_NEXT_PIN | KEY_OK_PIN;
    gpio.GPIO_Mode  = GPIO_Mode_IPU;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY_GPIO_PORT, &gpio);
}

/* 返回当前按下的键(未消抖, LVGL indev 周期调用即可) */
Key_Id_t BSP_Key_GetPressed(void)
{
    if (GPIO_ReadInputDataBit(KEY_GPIO_PORT, KEY_PREV_PIN) == Bit_RESET) return KEY_PREV;
    if (GPIO_ReadInputDataBit(KEY_GPIO_PORT, KEY_NEXT_PIN) == Bit_RESET) return KEY_NEXT;
    if (GPIO_ReadInputDataBit(KEY_GPIO_PORT, KEY_OK_PIN)   == Bit_RESET) return KEY_OK;
    return KEY_NONE;
}
