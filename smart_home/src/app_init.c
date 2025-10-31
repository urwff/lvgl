#include "app_init.h"
#include "lvgl/lvgl.h"

#include <time.h>

#define DISPLAY_DEVICE "/dev/fb0"

static lv_display_t *g_display = NULL;
static lv_indev_t *g_indev = NULL;

int app_init_all(void) {
    // 1. 初始化LVGL核心
    lv_init();
    
    // 2. 创建显示驱动（LVGL 9.4简化API）
    g_display = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(g_display, DISPLAY_DEVICE);
    
    // 3. 创建输入驱动
    g_indev = lv_evdev_create(LV_INDEV_TYPE_POINTER, INPUT_DEVICE);
    
    return 0;
}


void app_run_loop(void) {
    while (1) {
        uint32_t ms = lv_timer_handler();
        struct timespec ts;
        ts.tv_sec = ms / 1000;
        ts.tv_nsec = (ms % 1000) * 1000000;
        nanosleep(&ts, NULL);
    }
}