#ifndef APP_INIT_H
#define APP_INIT_H

#define DISPLAY_DEVICE      "/dev/fb0"
#define INPUT_DEVICE        "/dev/input/event0"

int app_init_lvgl(void);
int app_init_display(void);
int app_init_input(void);
int app_init_all(void);
void app_run_loop(void);

#endif