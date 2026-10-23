/**
 * @file main.c
 * @brief STM32F103C8T6 + LVGL8 + ST7789 LCD 菜单演示
 *
 * 硬件连接:
 *   LCD(ST7789 240x240 SPI): SCL=PA5  SDA=PA7  CS=PA4  DC=PA3  RES=PA2  BLK=PB9
 *   按键(另一端接GND, 内部上拉): 上=PB12  下=PB13  确定=PB14
 *   LED: PC13 (板载, 低电平点亮)
 *   蜂鸣器: PB8 (高电平响, 有源蜂鸣器)
 *
 * 注意: startup_stm32f10x_md.s 中 Stack_Size 建议改为 0x800
 */
#include "stm32f10x.h"
#include "bsp_sys.h"
#include "bsp_lcd.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "app_menu.h"

int main(void)//kikk
{
    BSP_SysTickInit();      /* 1ms 系统节拍 */
    BSP_LED_Init();
    BSP_Beep_Init();
    BSP_Key_Init();
    LCD_Init();

    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    App_MenuCreate();       /* 创建 LVGL 菜单界面 */

    while (1)
    {
        lv_timer_handler(); /* LVGL 任务处理 */
        BSP_DelayMs(5);
    }
}
