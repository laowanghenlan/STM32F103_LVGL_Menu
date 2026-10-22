#ifndef __BSP_LCD_H
#define __BSP_LCD_H

#include "stm32f10x.h"

#define LCD_W   240
#define LCD_H   240

/* 若显示内容整体偏移, 按屏幕规格修改(常见 0/0 或 0/80) */
#define LCD_X_OFFSET    0
#define LCD_Y_OFFSET    0

/* 若红蓝颜色对调, 改为 1 */
#define LCD_COLOR_BGR   1

void LCD_Init(void);
void LCD_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void LCD_WritePixels(const uint8_t *data, uint32_t len);
void LCD_Fill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

#endif
