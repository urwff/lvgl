/**
 * @file main.c
 * LVGL 9.4 智能家居仪表盘主程序
 * 分辨率：1024×600
 */

#include "lvgl/lvgl.h"
#include "ui/ui_home.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

static volatile bool running = true;

static void signal_handler(int signum)
{
    printf("\n收到信号 %d，退出程序...\n", signum);
    running = false;
}

int main(void)
{
    printf("========================================\n");
    printf("  智能家居仪表盘 v2.0 (LVGL 9.4)  \n");
    printf("========================================\n\n");

    /* 注册信号处理 */
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    /* ===== 1. 初始化 LVGL ===== */
    printf("[1/4] 初始化 LVGL...\n");
    lv_init();

    /* ===== 2. 创建显示驱动（LVGL 9.4 简化 API）===== */
    printf("[2/4] 初始化显示驱动...\n");
    lv_display_t *display = lv_linux_fbdev_create();
    if (!display) {
        fprintf(stderr, "❌ 错误：无法创建 fbdev 显示设备\n");
        return -1;
    }
    lv_linux_fbdev_set_file(display, "/dev/fb0");
    printf("  ✓ Framebuffer: /dev/fb0\n");

    /* ===== 3. 创建输入驱动（LVGL 9.4 简化 API）===== */
    printf("[3/4] 初始化输入设备...\n");
    lv_indev_t *indev = lv_evdev_create(LV_INDEV_TYPE_POINTER, "/dev/input/event1");
    if (!indev) {
        fprintf(stderr, "❌ 警告：无法创建输入设备，触摸功能不可用\n");
    } else {
        printf("  ✓ 输入设备: /dev/input/event1\n");
    }

    /* ===== 4. 创建 UI ===== */
    printf("[4/4] 创建用户界面...\n\n");
    ui_home_create();

    printf("========================================\n");
    printf("  系统启动成功！按 Ctrl+C 退出  \n");
    printf("========================================\n\n");

    /* ===== 主事件循环 ===== */
    while (running) {
        uint32_t delay = lv_timer_handler();
        usleep(delay * 1000);
    }

    printf("\n程序正常退出\n");
    return 0;
}