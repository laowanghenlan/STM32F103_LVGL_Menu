/**1111111111111111111
 * LVGL 菜单演示
 * 主菜单: [LED 控制] [蜂鸣器 控制]
 * 子页面: 开启 / 关闭 / 返回, 实时显示状态
 * 按键: PB12=上一个  PB13=下一个  PB14=确定
 */
#include "lvgl.h"
#include "app_menu.h"
#include "bsp_led.h"
#include "bsp_beep.h"

typedef enum {
    DEV_LED = 0,
    DEV_BEEP
} DevId_t;

static lv_group_t *s_group;      /* 按键焦点组 */
static lv_obj_t   *s_status;     /* 子页状态标签 */
static DevId_t     s_dev;

static void App_MenuCreate_Main(void);

/* 把屏幕内可聚焦控件全部加入按键组 */
static void group_add_screen(lv_obj_t *scr)
{
    uint32_t i;
    if (s_group) lv_group_del(s_group);
    s_group = lv_group_create();
    for (i = 0; i < lv_obj_get_child_cnt(scr); i++)
    {
        lv_obj_t *child = lv_obj_get_child(scr, i);
        if (lv_obj_check_type(child, &lv_list_class))
        {
            uint32_t j;
            for (j = 0; j < lv_obj_get_child_cnt(child); j++)
                lv_group_add_obj(s_group, lv_obj_get_child(child, j));
        }
        else if (lv_obj_check_type(child, &lv_btn_class))
        {
            lv_group_add_obj(s_group, child);
        }
    }
    {
        lv_indev_t *indev = lv_indev_get_next(NULL);
        if (indev) lv_indev_set_group(indev, s_group);
    }
}

/*---------------- 子页面事件 ----------------*/
static void btn_on_cb(lv_event_t *e)
{
    (void)e;
    if (s_dev == DEV_LED) BSP_LED_On();
    else                  BSP_Beep_On();
    lv_label_set_text(s_status, "STATE: ON");
}

static void btn_off_cb(lv_event_t *e)
{
    (void)e;
    if (s_dev == DEV_LED) BSP_LED_Off();
    else                  BSP_Beep_Off();
    lv_label_set_text(s_status, "STATE: OFF");
}

static void btn_back_cb(lv_event_t *e)
{
    (void)e;
    App_MenuCreate_Main();
}

/*---------------- 主菜单事件 ----------------*/
static void menu_item_cb(lv_event_t *e)
{
    lv_obj_t *btn_on, *btn_off, *btn_back, *lb;

    s_dev = (DevId_t)(uintptr_t)lv_event_get_user_data(e);
    lv_obj_clean(lv_scr_act());

    /* 标题 */
    lb = lv_label_create(lv_scr_act());
    lv_label_set_text(lb, s_dev == DEV_LED ? "LED CONTROL" : "BUZZER CONTROL");
    lv_obj_align(lb, LV_ALIGN_TOP_MID, 0, 15);

    /* 状态 */
    s_status = lv_label_create(lv_scr_act());
    lv_label_set_text(s_status, "STATE: OFF");
    lv_obj_align(s_status, LV_ALIGN_TOP_MID, 0, 50);

    /* 开启按钮 */
    btn_on = lv_btn_create(lv_scr_act());
    lv_obj_set_size(btn_on, 80, 40);
    lv_obj_align(btn_on, LV_ALIGN_CENTER, -50, 0);
    lb = lv_label_create(btn_on);
    lv_label_set_text(lb, "ON");
    lv_obj_center(lb);
    lv_obj_add_event_cb(btn_on, btn_on_cb, LV_EVENT_CLICKED, NULL);

    /* 关闭按钮 */
    btn_off = lv_btn_create(lv_scr_act());
    lv_obj_set_size(btn_off, 80, 40);
    lv_obj_align(btn_off, LV_ALIGN_CENTER, 50, 0);
    lb = lv_label_create(btn_off);
    lv_label_set_text(lb, "OFF");
    lv_obj_center(lb);
    lv_obj_add_event_cb(btn_off, btn_off_cb, LV_EVENT_CLICKED, NULL);

    /* 返回按钮 */
    btn_back = lv_btn_create(lv_scr_act());
    lv_obj_set_size(btn_back, 100, 35);
    lv_obj_align(btn_back, LV_ALIGN_BOTTOM_MID, 0, -25);
    lb = lv_label_create(btn_back);
    lv_label_set_text(lb, "BACK");
    lv_obj_center(lb);
    lv_obj_add_event_cb(btn_back, btn_back_cb, LV_EVENT_CLICKED, NULL);

    group_add_screen(lv_scr_act());
}

/*---------------- 主菜单 ----------------*/
static void App_MenuCreate_Main(void)
{
    lv_obj_t *title, *list, *btn;

    lv_obj_clean(lv_scr_act());

    title = lv_label_create(lv_scr_act());
    lv_label_set_text(title, "MAIN MENU");
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);

    list = lv_list_create(lv_scr_act());
    lv_obj_set_size(list, 200, 160);
    lv_obj_align(list, LV_ALIGN_BOTTOM_MID, 0, -15);

    btn = lv_list_add_btn(list, LV_SYMBOL_CHARGE, "1. LED ON/OFF");
    lv_obj_add_event_cb(btn, menu_item_cb, LV_EVENT_CLICKED, (void *)(uintptr_t)DEV_LED);

    btn = lv_list_add_btn(list, LV_SYMBOL_AUDIO, "2. Buzzer ON/OFF");
    lv_obj_add_event_cb(btn, menu_item_cb, LV_EVENT_CLICKED, (void *)(uintptr_t)DEV_BEEP);

    group_add_screen(lv_scr_act());
}

void App_MenuCreate(void)
{
    App_MenuCreate_Main();
}
