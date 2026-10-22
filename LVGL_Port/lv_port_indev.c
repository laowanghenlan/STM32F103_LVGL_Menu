/**
 * LVGL 输入移植层: 三个实体按键 -> LV_INDEV_TYPE_KEYPAD
 * PB12=上一个  PB13=下一个  PB14=确定
 */
#include "lvgl.h"
#include "bsp_key.h"

static void keypad_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    static uint32_t last_key = 0;
    Key_Id_t key = BSP_Key_GetPressed();

    if (key != KEY_NONE)
    {
        data->state = LV_INDEV_STATE_PRESSED;
        switch (key)
        {
            case KEY_PREV: last_key = LV_KEY_PREV;  break;
            case KEY_NEXT: last_key = LV_KEY_NEXT;  break;
            case KEY_OK:   last_key = LV_KEY_ENTER; break;
            default: break;
        }
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
    data->key = last_key;
}

void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;

    lv_indev_drv_init(&indev_drv);
    indev_drv.type    = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = keypad_read;
    lv_indev_drv_register(&indev_drv);
}
