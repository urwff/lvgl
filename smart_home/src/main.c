#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>

int main(void)
{
    printf("🚀 智能家居控制系统启动...\n");
    
    // 1. 初始化 LVGL
    lv_init();
    printf("✓ LVGL 初始化完成\n");
    
    // 2. 初始化 Framebuffer 显示驱动
    fbdev_init();
    
    static lv_disp_draw_buf_t draw_buf;
    static lv_color_t buf[800 * 10];  // 10行缓冲
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, 800 * 10);
    
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &draw_buf;
    disp_drv.flush_cb = fbdev_flush;
    disp_drv.hor_res = 800;
    disp_drv.ver_res = 480;
    lv_disp_drv_register(&disp_drv);
    printf("✓ Framebuffer 显示驱动初始化完成 (800x480)\n");
    
    // 3. 初始化触摸驱动
    evdev_init();
    
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = evdev_read;
    lv_indev_drv_register(&indev_drv);
    printf("✓ 触摸驱动初始化完成\n");
    
    // 4. 创建欢迎界面
    lv_obj_t *scr = lv_scr_act();
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x1A1A1A), 0);
    
    lv_obj_t *label = lv_label_create(scr);
    lv_label_set_text(label, "🏠 智能家居控制系统\n\n欢迎使用！");
    lv_obj_set_style_text_color(label, lv_color_hex(0x00A6FF), 0);
    lv_obj_center(label);
    
    printf("✓ 欢迎界面创建完成\n");
    printf("🎉 系统启动成功！\n");
    
    // 5. 主循环
    while(1) {
        lv_task_handler();
        usleep(5000);  // 5ms
    }
    
    return 0;
}
