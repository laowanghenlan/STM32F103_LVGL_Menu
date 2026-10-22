/**
 * LVGL v8.3 精简配置 - 适配 STM32F103C8T6 (64KB Flash / 20KB RAM)
 * 只保留 label/btn/list, 关闭其余控件与字体, 否则 64KB 放不下
 */
#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>

/*==================== 显示 ====================*/
#define LV_COLOR_DEPTH          16
#define LV_COLOR_16_SWAP        1   /* SPI 大端字节序, 配合 LCD_WritePixels */
#define LV_COLOR_SCREEN_TRANSP  0
#define LV_DPI_DEF              100
#define LV_DRAW_COMPLEX         0   /* 关闭渐变/阴影/蒙版, 大幅减小体积 */

/*==================== 内存 ====================*/
#define LV_MEM_CUSTOM           0
#define LV_MEM_SIZE             (6U * 1024U)   /* LVGL 堆, 20KB RAM 下取 6KB */
#define LV_MEM_BUF_MAX_NUM      16
#define LV_MEMCPY_MEMSET_STD    1

/*==================== 刷新 ====================*/
#define LV_DISP_DEF_REFR_PERIOD     30
#define LV_INDEV_DEF_READ_PERIOD    30
#define LV_USE_PERF_MONITOR         0
#define LV_USE_MEM_MONITOR          0

/*==================== 特性开关 ====================*/
#define LV_USE_LOG              0
#define LV_USE_ASSERT_NULL      0
#define LV_USE_ASSERT_MALLOC    0
#define LV_USE_ASSERT_STYLE     0
#define LV_USE_ASSERT_MEM_INTEGRITY 0
#define LV_USE_ASSERT_OBJ       0
#define LV_USE_USER_DATA        1
#define LV_USE_GROUP            1   /* 实体按键导航必须 */
#define LV_USE_FILESYSTEM       0
#define LV_USE_GPU_STM32_DMA2D  0

/*==================== 主题 ====================*/
#define LV_USE_THEME_DEFAULT    1
#define LV_THEME_DEFAULT_DARK   0
#define LV_THEME_DEFAULT_GROW   0
#define LV_FONT_MONTSERRAT_14   1
#define LV_FONT_DEFAULT         &lv_font_montserrat_14

/*==================== 字体(只留14号, 其余全关省Flash) ====================*/
#define LV_FONT_MONTSERRAT_8    0
#define LV_FONT_MONTSERRAT_10   0
#define LV_FONT_MONTSERRAT_12   0
#define LV_FONT_MONTSERRAT_16   0
#define LV_FONT_MONTSERRAT_18   0
#define LV_FONT_MONTSERRAT_20   0
#define LV_FONT_MONTSERRAT_22   0
#define LV_FONT_MONTSERRAT_24   0
#define LV_FONT_MONTSERRAT_26   0
#define LV_FONT_MONTSERRAT_28   0
#define LV_FONT_MONTSERRAT_30   0
#define LV_FONT_MONTSERRAT_32   0
#define LV_FONT_MONTSERRAT_34   0
#define LV_FONT_MONTSERRAT_36   0
#define LV_FONT_MONTSERRAT_38   0
#define LV_FONT_MONTSERRAT_40   0
#define LV_FONT_MONTSERRAT_42   0
#define LV_FONT_MONTSERRAT_44   0
#define LV_FONT_MONTSERRAT_46   0
#define LV_FONT_MONTSERRAT_48   0
#define LV_FONT_UNNUMBER        0
#define LV_FONT_SIMSUN_16_CJK   0

/*==================== 控件(只用到的开着) ====================*/
#define LV_USE_ARC          0
#define LV_USE_BAR          0
#define LV_USE_BTN          1
#define LV_USE_BTNMATRIX    0
#define LV_USE_CANVAS       0
#define LV_USE_CHECKBOX     0
#define LV_USE_DROPDOWN     0
#define LV_USE_IMG          0
#define LV_USE_LABEL        1
#define LV_LABEL_TEXT_SELECTION 0
#define LV_LABEL_LONG_TXT_HINT  0
#define LV_USE_LINE         0
#define LV_USE_ROLLER       0
#define LV_USE_SLIDER       0
#define LV_USE_SWITCH       0
#define LV_USE_TEXTAREA     0
#define LV_USE_TABLE        0
#define LV_USE_ANIMIMG      0
#define LV_USE_CALENDAR     0
#define LV_USE_CHART        0
#define LV_USE_COLORWHEEL   0
#define LV_USE_IMGBTN       0
#define LV_USE_KEYBOARD     0
#define LV_USE_LED          0
#define LV_USE_LIST         1
#define LV_USE_MENU         0
#define LV_USE_METER        0
#define LV_USE_MSGBOX       0
#define LV_USE_OBJMASK      0
#define LV_USE_SPINBOX      0
#define LV_USE_SPINNER      0
#define LV_USE_TABVIEW      0
#define LV_USE_TILEVIEW     0
#define LV_USE_WIN          0
#define LV_USE_SPAN         0

/*==================== 布局 ====================*/
#define LV_USE_FLEX         1
#define LV_USE_GRID         0

/*==================== 3rd party ====================*/
#define LV_USE_FS_STDIO     0
#define LV_USE_PNG          0
#define LV_USE_BMP          0
#define LV_USE_SJPG         0
#define LV_USE_GIF          0
#define LV_USE_QRCODE       0
#define LV_USE_FREETYPE     0

/*==================== 演示 ====================*/
#define LV_USE_DEMO_WIDGETS       0
#define LV_USE_DEMO_KEYPAD_AND_ENCODER 0
#define LV_USE_DEMO_BENCHMARK     0
#define LV_USE_DEMO_STRESS        0
#define LV_USE_DEMO_MUSIC         0

/* 编译期检查 */
#define LV_CONF_SKIP 0

#endif /* LV_CONF_H */
