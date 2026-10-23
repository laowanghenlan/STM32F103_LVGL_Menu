/**
 * LVGL 显示移植层 (LVGL v8.x)11
 * C8T6 只有 20KB RAM, 显存缓冲取 240x10 像素 (4.8KB)
 */
#include "lvgl.h"
#include "bsp_lcd.h"

#define DISP_HOR   240
#define DISP_VER   240
#define DISP_BUF_LINES  10

static lv_disp_draw_buf_t draw_buf;
static lv_color_t disp_buf[DISP_HOR * DISP_BUF_LINES];

static void lcd_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p)
{
    int32_t w = area->x2 - area->x1 + 1;
    int32_t h = area->y2 - area->y1 + 1;

    LCD_SetWindow(area->x1, area->y1, area->x2, area->y2);
    /* lv_conf.h 中 LV_COLOR_16_SWAP=1, buf 直接按字节流发送 */
    LCD_WritePixels((const uint8_t *)color_p, (uint32_t)w * h * 2);

    lv_disp_flush_ready(drv);
}

void lv_port_disp_init(void)
{
    static lv_disp_drv_t disp_drv;

    lv_disp_draw_buf_init(&draw_buf, disp_buf, NULL, DISP_HOR * DISP_BUF_LINES);

    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res  = DISP_HOR;
    disp_drv.ver_res  = DISP_VER;
    disp_drv.flush_cb = lcd_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);
}
