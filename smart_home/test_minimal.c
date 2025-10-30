#include "libs/lvgl/lvgl.h"
#include <unistd.h>

int main(void) {
    // 1. 初始化LVGL
    lv_init();
    
    // 2. 创建framebuffer显示（LVGL 9.4）
    lv_display_t *disp = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(disp, "/dev/fb0");
    
    // 3. 创建触摸输入（根据你之前的event设备）
    lv_indev_t *indev = lv_evdev_create(LV_INDEV_TYPE_POINTER, "/dev/input/event0");
    
    // 4. 创建简单界面：一个标签 + 一个按钮
    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Hello i.MX 6ULL!");
    lv_obj_center(label);
    
    lv_obj_t *btn = lv_button_create(lv_screen_active());
    lv_obj_set_size(btn, 120, 50);
    lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -20);
    
    lv_obj_t *btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Test");
    lv_obj_center(btn_label);
    
    // 5. 主循环
    while (1) {
        uint32_t time_till_next = lv_timer_handler();
        usleep(time_till_next * 1000);
    }
    
    return 0;
}