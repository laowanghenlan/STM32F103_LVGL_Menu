#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "stm32f10x.h"

/* 按键另一端接GND, 按下为低电平 */
#define KEY_PREV_PIN    GPIO_Pin_12     /* PB12 上一个 */
#define KEY_NEXT_PIN    GPIO_Pin_13     /* PB13 下一个 */
#define KEY_OK_PIN      GPIO_Pin_14     /* PB14 确定   */
#define KEY_GPIO_PORT   GPIOB
#define KEY_GPIO_CLK    RCC_APB2Periph_GPIOB

typedef enum {
    KEY_NONE = 0,
    KEY_PREV,
    KEY_NEXT,
    KEY_OK
} Key_Id_t;

void      BSP_Key_Init(void);
Key_Id_t  BSP_Key_GetPressed(void);

#endif
