#include "app_init.h"
#include "lvgl/lvgl.h"
#include <stdio.h>

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