/**
 * @file ui_home.c
 * 智能家居主界面实现
 */

#include "ui_home.h"
#include "ui_styles.h"
#include "ui_card.h"
#include <stdio.h>

/* ========== 事件回调 ========== */

static void scene_btn_clicked(lv_event_t *e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *label = lv_obj_get_child(btn, 1);
    printf("场景按钮点击: %s\n", lv_label_get_text(label));
}

static void settings_btn_clicked(lv_event_t *e)
{
    printf("设置按钮点击（Phase 3 切换到 Qt）\n");
}

/* ========== 创建顶部状态栏 ========== */

static void create_header(lv_obj_t *parent)
{
    lv_obj_t *header = lv_obj_create(parent);
    lv_obj_set_size(header, 1024, 60);
    lv_obj_align(header, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_color(header, COLOR_CARD_BG, 0);
    lv_obj_set_style_border_width(header, 0, 0);
    lv_obj_set_style_radius(header, 0, 0);
    lv_obj_clear_flag(header, LV_OBJ_FLAG_SCROLLABLE);

    /* 标题 */
    lv_obj_t *title = lv_label_create(header);
    lv_label_set_text(title, "🏠 智能家居");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, 0);
    lv_obj_set_style_text_color(title, COLOR_TEXT_MAIN, 0);
    lv_obj_align(title, LV_ALIGN_LEFT_MID, 24, 0);

    /* 时间（模拟）*/
    lv_obj_t *time_label = lv_label_create(header);
    lv_label_set_text(time_label, "15:30");
    lv_obj_set_style_text_font(time_label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(time_label, lv_color_hex(0xCCCCCC), 0);
    lv_obj_align(time_label, LV_ALIGN_RIGHT_MID, -130, 0);

    /* 设置按钮 */
    lv_obj_t *btn_settings = lv_btn_create(header);
    lv_obj_set_size(btn_settings, 100, 42);
    lv_obj_align(btn_settings, LV_ALIGN_RIGHT_MID, -20, 0);
    lv_obj_set_style_bg_color(btn_settings, lv_color_hex(0x3D3D3D), 0);
    lv_obj_set_style_radius(btn_settings, 8, 0);
    lv_obj_add_event_cb(btn_settings, settings_btn_clicked, LV_EVENT_CLICKED, NULL);

    lv_obj_t *btn_label = lv_label_create(btn_settings);
    lv_label_set_text(btn_label, "⚙️ 设置");
    lv_obj_center(btn_label);
}

/* ========== 创建状态卡片区 ========== */

static void create_status_cards(lv_obj_t *parent)
{
    /* 区域标题 */
    lv_obj_t *title = lv_label_create(parent);
    lv_label_set_text(title, "📊 今日概览");
    lv_obj_add_style(title, &style_card_title, 0);
    lv_obj_set_pos(title, 24, 70);

    /* 卡片配置 */
    ui_card_config_t cards[] = {
        {"💡", "灯光", "5/8", "已开启", COLOR_PRIMARY},
        {"🌡️", "温度", "24°C", "舒适", COLOR_PRIMARY},
        {"🔒", "安防", "正常", "已布防", COLOR_SUCCESS},
        {"⚡", "能耗", "12.5kW", "今日", COLOR_PRIMARY}
    };

    /* 创建4个卡片 */
    int x_start = 24;
    int y = 110;
    int spacing = 20;
    
    for (int i = 0; i < 4; i++) {
        lv_obj_t *card = ui_card_create(parent, &cards[i]);
        lv_obj_set_pos(card, x_start + i * (230 + spacing), y);
    }
}

/* ========== 创建场景按钮区 ========== */

static void create_scene_buttons(lv_obj_t *parent)
{
    /* 区域标题 */
    lv_obj_t *title = lv_label_create(parent);
    lv_label_set_text(title, "🎬 常用场景");
    lv_obj_add_style(title, &style_card_title, 0);
    lv_obj_set_pos(title, 24, 310);

    /* 场景配置 */
    struct {
        const char *icon;
        const char *name;
    } scenes[] = {
        {"☀️", "回家模式"},
        {"🌙", "睡眠模式"},
        {"👔", "离家模式"}
    };

    /* 创建3个场景按钮 */
    int x_start = 24;
    int y = 350;
    int spacing = 24;

    for (int i = 0; i < 3; i++) {
        lv_obj_t *btn = lv_btn_create(parent);
        lv_obj_set_size(btn, 320, 140);
        lv_obj_set_pos(btn, x_start + i * (320 + spacing), y);
        lv_obj_add_style(btn, &style_btn_primary, 0);
        lv_obj_add_style(btn, &style_btn_pressed, LV_STATE_PRESSED);
        lv_obj_add_event_cb(btn, scene_btn_clicked, LV_EVENT_CLICKED, NULL);

        /* 设置垂直布局 */
        lv_obj_set_flex_flow(btn, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_flex_align(btn, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        /* 图标 */
        lv_obj_t *icon = lv_label_create(btn);
        lv_label_set_text(icon, scenes[i].icon);
        lv_obj_set_style_text_font(icon, &lv_font_montserrat_32, 0);

        /* 名称 */
        lv_obj_t *name = lv_label_create(btn);
        lv_label_set_text(name, scenes[i].name);
        lv_obj_set_style_text_font(name, &lv_font_montserrat_20, 0);
    }
}

/* ========== 创建主界面 ========== */

void ui_home_create(void)
{
    /* 初始化样式 */
    ui_styles_init();

    /* 创建屏幕 */
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_add_style(screen, &style_screen_bg, 0);
    lv_scr_load(screen);

    /* 创建各个区域 */
    create_header(screen);
    create_status_cards(screen);
    create_scene_buttons(screen);

    printf("✅ 智能家居主界面创建完成\n");
}