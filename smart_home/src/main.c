#include "app_init.h"
#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include <stdio.h>

static void event_cb(lv_event_t * e)
{
    LV_LOG_USER("Clicked");

    static uint32_t cnt = 1;
    lv_obj_t * btn = lv_event_get_target_obj(e);
    lv_obj_t * label = lv_obj_get_child(btn, 0);
    lv_label_set_text_fmt(label, "%" LV_PRIu32, cnt);
    cnt++;
}

/**
 * Add click event to a button
 */
void lv_example_event_click(void)
{
    lv_obj_t * btn = lv_button_create(lv_screen_active());
    lv_obj_set_size(btn, 100, 50);
    lv_obj_center(btn);
    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t * label = lv_label_create(btn);
    lv_label_set_text(label, "Click me!");
    lv_obj_center(label);
}

int main(void) {
    // 初始化
    if (app_init_all() != 0) {
        printf("初始化失败\n");
        return -1;
    }
    
    // 创建测试界面
    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Smart Home Test");
    lv_obj_center(label);
    
    // 运行
    app_run_loop();
    return 0;
}