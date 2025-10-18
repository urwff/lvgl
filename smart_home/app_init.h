/**
 * @file app_init.h
 * @brief 应用初始化模块 - LVGL 9.4
 * @version 1.0
 * @date 2025-10-18
 */

#ifndef APP_INIT_H
#define APP_INIT_H

#include <stdint.h>

// 显示配置
#define DISPLAY_DEVICE      "/dev/fb0"          // Framebuffer设备
#define INPUT_DEVICE        "/dev/input/event0" // 触摸输入设备

// LVGL任务配置
#define LVGL_TASK_PERIOD_MS 5                   // LVGL任务周期（毫秒）

/**
 * @brief 初始化LVGL核心
 * @return 0:成功 -1:失败
 */
int app_init_lvgl(void);

/**
 * @brief 初始化显示驱动（Framebuffer）
 * @return 0:成功 -1:失败
 */
int app_init_display(void);

/**
 * @brief 初始化输入设备驱动（触摸屏）
 * @return 0:成功 -1:失败
 */
int app_init_input(void);

/**
 * @brief 初始化所有子系统
 * @return 0:成功 -1:失败
 */
int app_init_all(void);

/**
 * @brief 启动LVGL主循环（阻塞）
 * @note 此函数不会返回，除非出错
 */
void app_run_loop(void);

#endif // APP_INIT_H