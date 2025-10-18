#include "app_init.h"
#include "stdio.h"
#include "unistd.h"
#include "libs/lvgl/lvgl.h"
#include "libs/lvgl/src/misc/lv_log.h"
#include "libs/lvgl/src/tick/lv_tick.h"
#include "libs/lvgl/src/misc/lv_timer.h"
static lv_display_t *g_disp = NULL;

int app_init_lvgl(void)
{
    LV_LOG_INFO("Initializing LVGL core...\n");

    lv_init();

    LV_LOG_INFO("LVGL core initialized successfully.version: %d.%d.%d)", 
             lv_version_major(), lv_version_minor(), lv_version_patch());
    LV_LOG_INFO("-------------------------------------------");
    return 0;
}

int app_init_display(void)
{
    g_disp = lv_linux_fbdev_create();
    if (g_disp == NULL)
    {
        LV_LOG_ERROR("Failed to create Linux framebuffer display driver.\n");
        return -1;
    }

    lv_linux_fbdev_set_file(g_disp, DISPLAY_DEVICE);
    LV_LOG_INFO("Display driver initialized with device: %s", DISPLAY_DEVICE);
     LV_LOG_INFO("-------------------------------------------\n");
    return 0;
}

int app_init_input(void)
{
    lv_indev_t *touch = lv_linux_input_create();
    if (touch == NULL)
    {
        LV_LOG_ERROR("Failed to create Linux input device driver.\n");
        LV_LOG_INFO("-------------------------------------------\n");
        return -1;
    }

    lv_linux_input_set_file(touch, INPUT_DEVICE);
    LV_LOG_INFO("Input device driver initialized with device: %s\n", INPUT_DEVICE);

    //resolution log
    int32_t hor_res = lv_display_get_horizontal_resolution(g_disp);
    int32_t ver_res = lv_display_get_vertical_resolution(g_disp);
    LV_LOG_INFO("display resolution: %d x %d\n", hor_res, ver_res);
    LV_LOG_INFO("-------------------------------------------\n");
    /* Register the input device with the display */
    lv_set_disp_indev(g_disp, touch);

    return 0;
}

int app_init_all(void)
{
    if (app_init_lvgl() != 0)
        return -1;

    if (app_init_display() != 0)
        return -1;

    if (app_init_input() != 0)
        return -1;

    LV_LOG_INFO("All subsystems initialized successfully.\n");
    LV_LOG_INFO("-------------------------------------------\n");
    return 0;
}
void app_run_loop(void)
{
    LOG_INFO("Starting LVGL main loop on i.MX6ull...");

    while (1)
    {
        uint32_t time_till_next = lv_timer_handler();
        usleep(time_till_next * 1000);
    }
    LV_LOG_INFO("-------------------------------------------\n");
}
