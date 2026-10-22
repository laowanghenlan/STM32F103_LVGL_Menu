#include "bsp_led.h"

/* PC13 板载LED, 低电平点亮 */
void BSP_LED_Init(void)
{
    GPIO_InitTypeDef gpio;
    RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);
    gpio.GPIO_Pin   = LED_GPIO_PIN;
    gpio.GPIO_Mode  = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_GPIO_PORT, &gpio);
    BSP_LED_Off();
}

void BSP_LED_On(void)
{
    GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);
}

void BSP_LED_Off(void)
{
    GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
}

void BSP_LED_Toggle(void)
{
    if (GPIO_ReadOutputDataBit(LED_GPIO_PORT, LED_GPIO_PIN))
        BSP_LED_On();
    else
        BSP_LED_Off();
}
