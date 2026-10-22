#include "bsp_beep.h"

/* PB8 有源蜂鸣器, 高电平响 */
void BSP_Beep_Init(void)
{
    GPIO_InitTypeDef gpio;
    RCC_APB2PeriphClockCmd(BEEP_GPIO_CLK, ENABLE);
    gpio.GPIO_Pin   = BEEP_GPIO_PIN;
    gpio.GPIO_Mode  = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BEEP_GPIO_PORT, &gpio);
    BSP_Beep_Off();
}

void BSP_Beep_On(void)
{
    GPIO_SetBits(BEEP_GPIO_PORT, BEEP_GPIO_PIN);
}

void BSP_Beep_Off(void)
{
    GPIO_ResetBits(BEEP_GPIO_PORT, BEEP_GPIO_PIN);
}
