/**
 * @file ui_styles.c
 * 全局样式实现
 */

#include "ui_styles.h"

/* 样式对象 */
lv_style_t style_screen_bg;
lv_style_t style_card;
lv_style_t style_card_title;
lv_style_t style_card_value;
lv_style_t style_btn_primary;
lv_style_t style_btn_pressed;

void ui_styles_init(void)
{
    /* ===== 屏幕背景样式 ===== */
    lv_style_init(&style_screen_bg);
    lv_style_set_bg_color(&style_screen_bg, COLOR_BG_DARK);
    lv_style_set_bg_opa(&style_screen_bg, LV_OPA_COVER);

    /* ===== 卡片样式 ===== */
    lv_style_init(&style_card);
    lv_style_set_bg_color(&style_card, COLOR_CARD_BG);
    lv_style_set_bg_opa(&style_card, LV_OPA_COVER);
    lv_style_set_radius(&style_card, 8);
    lv_style_set_pad_all(&style_card, 20);
    lv_style_set_shadow_width(&style_card, 10);
    lv_style_set_shadow_color(&style_card, lv_color_black());
    lv_style_set_shadow_opa(&style_card, LV_OPA_30);
    lv_style_set_border_width(&style_card, 0);

    /* ===== 卡片标题样式 ===== */
    lv_style_init(&style_card_title);
    lv_style_set_text_color(&style_card_title, COLOR_TEXT_MAIN);
    lv_style_set_text_font(&style_card_title, &lv_font_montserrat_20);

    /* ===== 卡片数值样式 ===== */
    lv_style_init(&style_card_value);
    lv_style_set_text_color(&style_card_value, COLOR_PRIMARY);
    lv_style_set_text_font(&style_card_value, &lv_font_montserrat_28);

    /* ===== 主按钮样式 ===== */
    lv_style_init(&style_btn_primary);
    lv_style_set_bg_color(&style_btn_primary, COLOR_PRIMARY);
    lv_style_set_bg_opa(&style_btn_primary, LV_OPA_COVER);
    lv_style_set_radius(&style_btn_primary, 10);
    lv_style_set_text_color(&style_btn_primary, COLOR_TEXT_MAIN);
    lv_style_set_text_font(&style_btn_primary, &lv_font_montserrat_20);

    /* ===== 按钮按下样式 ===== */
    lv_style_init(&style_btn_pressed);
    lv_style_set_bg_color(&style_btn_pressed, lv_color_hex(0x0088CC));
}