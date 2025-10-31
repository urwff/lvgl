/**
 * @file ui_home.c
 * 智能家居仪表盘主界面实现
 * 布局：
 *   - 顶部状态栏：时间、温度、湿度、空气质量
 *   - 中部控制模块：灯光、窗户、环境、安防（带开关和状态）
 */

#include "ui_home.h"
#include "ui_styles.h"
#include <stdio.h>
#include <time.h>

/* ========== 全局状态 ========== */
typedef struct {
    bool light_on;
    bool window_open;
    bool env_active;
    bool camera_online;
} device_state_t;

static device_state_t g_state = {
    .light_on = false,
    .window_open = false,
    .env_active = true,
    .camera_online = true
};

/* ========== 工具函数 ========== */

static void get_current_time(char *buf, size_t len)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    snprintf(buf, len, "%02d:%02d", t->tm_hour, t->tm_min);
}

/* ========== 创建顶部状态栏 ========== */

static lv_obj_t* create_status_item(lv_obj_t *parent, const char *icon, 
                                     const char *value, const char *label)
{
    /* 容器 */
    lv_obj_t *cont = lv_obj_create(parent);
    lv_obj_set_size(cont, 220, 100);
    lv_obj_add_style(cont, &style_card, 0);
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);

    /* 图标 */
    lv_obj_t *icon_label = lv_label_create(cont);
    lv_label_set_text(icon_label, icon);
    lv_obj_set_style_text_font(icon_label, &lv_font_montserrat_28, 0);
    lv_obj_align(icon_label, LV_ALIGN_LEFT_MID, 0, -8);

    /* 数值 */
    lv_obj_t *value_label = lv_label_create(cont);
    lv_label_set_text(value_label, value);
    lv_obj_add_style(value_label, &style_label_value, 0);
    lv_obj_set_style_text_font(value_label, &lv_font_montserrat_24, 0);
    lv_obj_align(value_label, LV_ALIGN_RIGHT_MID, 0, -8);

    /* 标签 */
    lv_obj_t *desc_label = lv_label_create(cont);
    lv_label_set_text(desc_label, label);
    lv_obj_add_style(desc_label, &style_label_desc, 0);
    lv_obj_align(desc_label, LV_ALIGN_BOTTOM_LEFT, 0, 0);

    return cont;
}

static void create_header(lv_obj_t *parent)
{
    /* 时间 */
    char time_str[16];
    get_current_time(time_str, sizeof(time_str));
    lv_obj_t *time_card = create_status_item(parent, "🕐", time_str, "当前时间");
    lv_obj_set_pos(time_card, 24, 24);

    /* 温度 */
    lv_obj_t *temp_card = create_status_item(parent, "🌡️", "24°C", "室内温度");
    lv_obj_set_pos(temp_card, 24 + 220 + 16, 24);

    /* 湿度 */
    lv_obj_t *humid_card = create_status_item(parent, "💧", "65%", "空气湿度");
    lv_obj_set_pos(humid_card, 24 + (220 + 16) * 2, 24);

    /* 空气质量 */
    lv_obj_t *air_card = create_status_item(parent, "🍃", "优", "空气质量");
    lv_obj_set_pos(air_card, 24 + (220 + 16) * 3, 24);
}

/* ========== 控制模块事件处理 ========== */

static void light_switch_event(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *label = lv_obj_get_child(btn, 0);
    
    g_state.light_on = !g_state.light_on;
    
    if (g_state.light_on) {
        lv_label_set_text(label, "💡");  /* 亮灯 */
        lv_obj_set_style_bg_color(btn, COLOR_WARNING, 0);
        printf("✅ 灯光：已开启\n");
    } else {
        lv_label_set_text(label, "🌑");  /* 关灯 */
        lv_obj_set_style_bg_color(btn, lv_color_hex(0x3A3A3A), 0);
        printf("⭕ 灯光：已关闭\n");
    }
}

static void window_switch_event(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *label = lv_obj_get_child(btn, 0);
    
    g_state.window_open = !g_state.window_open;
    
    if (g_state.window_open) {
        lv_label_set_text(label, "🪟");  /* 开窗 */
        lv_obj_set_style_bg_color(btn, COLOR_CYAN, 0);
        printf("✅ 窗户：已打开\n");
    } else {
        lv_label_set_text(label, "🚪");  /* 关窗 */
        lv_obj_set_style_bg_color(btn, lv_color_hex(0x3A3A3A), 0);
        printf("⭕ 窗户：已关闭\n");
    }
}

static void env_control_event(lv_event_t *e)
{
    printf("🌿 环境控制：打开设置页面\n");
}

static void camera_control_event(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *parent = lv_obj_get_parent(btn);
    lv_obj_t *status_label = lv_obj_get_child(parent, 2);  /* 状态标签 */
    
    g_state.camera_online = !g_state.camera_online;
    
    if (g_state.camera_online) {
        lv_label_set_text(status_label, "🟢 在线");
        lv_obj_set_style_text_color(status_label, COLOR_SUCCESS, 0);
        printf("✅ 安防：摄像头上线\n");
    } else {
        lv_label_set_text(status_label, "🔴 离线");
        lv_obj_set_style_text_color(status_label, COLOR_ERROR, 0);
        printf("⭕ 安防：摄像头离线\n");
    }
}

/* ========== 创建控制模块卡片 ========== */

static lv_obj_t* create_control_card(lv_obj_t *parent, const char *icon, 
                                      const char *title, lv_color_t btn_color,
                                      lv_event_cb_t event_cb, bool show_status)
{
    /* 卡片容器 */
    lv_obj_t *card = lv_obj_create(parent);
    lv_obj_set_size(card, 220, 240);
    lv_obj_add_style(card, &style_card, 0);
    lv_obj_clear_flag(card, LV_OBJ_FLAG_SCROLLABLE);

    /* 图标按钮 */
    lv_obj_t *btn = lv_obj_create(card);
    lv_obj_set_size(btn, 100, 100);
    lv_obj_align(btn, LV_ALIGN_TOP_MID, 0, 20);
    lv_obj_set_style_bg_color(btn, btn_color, 0);
    lv_obj_set_style_radius(btn, 50, 0);  /* 圆形按钮 */
    lv_obj_set_style_border_width(btn, 0, 0);
    lv_obj_set_style_shadow_width(btn, 10, 0);
    lv_obj_set_style_shadow_color(btn, btn_color, 0);
    lv_obj_set_style_shadow_opa(btn, LV_OPA_40, 0);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, NULL);

    /* 按钮按下效果 */
    lv_obj_set_style_transform_scale(btn, 240, LV_STATE_PRESSED);  /* 0.94x */
    lv_obj_set_style_bg_color(btn, lv_color_darken(btn_color, 30), LV_STATE_PRESSED);

    /* 图标标签 */
    lv_obj_t *icon_label = lv_label_create(btn);
    lv_label_set_text(icon_label, icon);
    lv_obj_set_style_text_font(icon_label, &lv_font_montserrat_48, 0);
    lv_obj_center(icon_label);

    /* 状态标签（可选） */
    if (show_status) {
        lv_obj_t *status_label = lv_label_create(card);
        lv_label_set_text(status_label, "🟢 在线");
        lv_obj_set_style_text_color(status_label, COLOR_SUCCESS, 0);
        lv_obj_set_style_text_font(status_label, &lv_font_montserrat_14, 0);
        lv_obj_align(status_label, LV_ALIGN_TOP_MID, 0, 130);
    }

    /* 标题标签 */
    lv_obj_t *title_label = lv_label_create(card);
    lv_label_set_text(title_label, title);
    lv_obj_add_style(title_label, &style_label_title, 0);
    lv_obj_set_style_text_font(title_label, &lv_font_montserrat_18, 0);
    lv_obj_align(title_label, LV_ALIGN_BOTTOM_MID, 0, -10);

    return card;
}

/* ========== 创建控制区域 ========== */

static void create_control_area(lv_obj_t *parent)
{
    /* 灯光控制 */
    lv_obj_t *light_card = create_control_card(parent, "🌑", "灯光控制", 
                                                lv_color_hex(0x3A3A3A), 
                                                light_switch_event, false);
    lv_obj_set_pos(light_card, 24, 150);

    /* 窗户控制 */
    lv_obj_t *window_card = create_control_card(parent, "🚪", "窗户控制", 
                                                 lv_color_hex(0x3A3A3A), 
                                                 window_switch_event, false);
    lv_obj_set_pos(window_card, 24 + 220 + 16, 150);

    /* 环境控制 */
    lv_obj_t *env_card = create_control_card(parent, "🌿", "环境控制", 
                                              COLOR_SUCCESS, 
                                              env_control_event, false);
    lv_obj_set_pos(env_card, 24 + (220 + 16) * 2, 150);
    
    /* 添加环境状态标签 */
    lv_obj_t *env_status = lv_label_create(env_card);
    lv_label_set_text(env_status, "自动调节中");
    lv_obj_set_style_text_color(env_status, COLOR_TEXT_SECOND, 0);
    lv_obj_set_style_text_font(env_status, &lv_font_montserrat_14, 0);
    lv_obj_align(env_status, LV_ALIGN_TOP_MID, 0, 130);

    /* 安防控制 */
    lv_obj_t *camera_card = create_control_card(parent, "📹", "安防监控", 
                                                 COLOR_ERROR, 
                                                 camera_control_event, true);
    lv_obj_set_pos(camera_card, 24 + (220 + 16) * 3, 150);
}

/* ========== 主界面创建 ========== */

void ui_home_create(void)
{
    /* 初始化全局样式 */
    ui_styles_init();

    /* 获取当前活动屏幕 */
    lv_obj_t *screen = lv_screen_active();
    lv_obj_add_style(screen, &style_screen_bg, 0);

    /* 创建顶部状态栏 */
    create_header(screen);

    /* 创建控制区域 */
    create_control_area(screen);

    printf("✅ UI 创建完成\n");
}