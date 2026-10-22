#ifndef __STM32F10x_CONF_H
#define __STM32F10x_CONF_H

/* 只包含用到的外设, 节省编译时间 */
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "misc.h"

/* 关闭参数断言, 减小程序体积 */
#define assert_param(expr) ((void)0)

#endif
