/**
 * @file ui_styles.c
 * 全局样式实现
 */

#include "ui_styles.h"

/* 样式对象 */
lv_style_t style_screen_bg;
lv_style_t style_card;
lv_style_t style_btn_control;
lv_style_t style_btn_control_pressed;
lv_style_t style_label_title;
lv_style_t style_label_value;
lv_style_t style_label_desc;

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
    lv_style_set_radius(&style_card, 16);
    lv_style_set_pad_all(&style_card, 20);
    lv_style_set_shadow_width(&style_card, 12);
    lv_style_set_shadow_color(&style_card, lv_color_black());
    lv_style_set_shadow_opa(&style_card, LV_OPA_40);
    lv_style_set_shadow_spread(&style_card, 2);
    lv_style_set_border_width(&style_card, 0);

    /* ===== 控制按钮样式 ===== */
    lv_style_init(&style_btn_control);
    lv_style_set_bg_color(&style_btn_control, COLOR_PRIMARY);
    lv_style_set_bg_opa(&style_btn_control, LV_OPA_COVER);
    lv_style_set_radius(&style_btn_control, 12);
    lv_style_set_text_color(&style_btn_control, COLOR_TEXT_MAIN);
    lv_style_set_text_font(&style_btn_control, &lv_font_montserrat_16);
    lv_style_set_shadow_width(&style_btn_control, 8);
    lv_style_set_shadow_color(&style_btn_control, COLOR_PRIMARY);
    lv_style_set_shadow_opa(&style_btn_control, LV_OPA_30);

    /* ===== 按钮按下样式 ===== */
    lv_style_init(&style_btn_control_pressed);
    lv_style_set_bg_color(&style_btn_control_pressed, lv_color_hex(0x3E7FCC));
    lv_style_set_transform_scale(&style_btn_control_pressed, 240);  /* 0.95x = 240/256 */

    /* ===== 标题样式 ===== */
    lv_style_init(&style_label_title);
    lv_style_set_text_color(&style_label_title, COLOR_TEXT_MAIN);
    lv_style_set_text_font(&style_label_title, &lv_font_montserrat_20);

    /* ===== 数值样式 ===== */
    lv_style_init(&style_label_value);
    lv_style_set_text_color(&style_label_value, COLOR_PRIMARY);
    lv_style_set_text_font(&style_label_value, &lv_font_montserrat_32);

    /* ===== 描述样式 ===== */
    lv_style_init(&style_label_desc);
    lv_style_set_text_color(&style_label_desc, COLOR_TEXT_SECOND);
    lv_style_set_text_font(&style_label_desc, &lv_font_montserrat_14);
}