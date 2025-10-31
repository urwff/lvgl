/**
 * @file ui_styles.h
 * 全局样式系统
 */

#ifndef UI_STYLES_H
#define UI_STYLES_H

#include "lvgl/lvgl.h"

/* ========== 颜色定义 ========== */
#define COLOR_BG_DARK       lv_color_hex(0x0F1419)
#define COLOR_CARD_BG       lv_color_hex(0x1C2128)
#define COLOR_PRIMARY       lv_color_hex(0x58A6FF)
#define COLOR_TEXT_MAIN     lv_color_hex(0xFFFFFF)
#define COLOR_TEXT_SECOND   lv_color_hex(0x8B949E)
#define COLOR_SUCCESS       lv_color_hex(0x3FB950)
#define COLOR_WARNING       lv_color_hex(0xD29922)
#define COLOR_ERROR         lv_color_hex(0xF85149)
#define COLOR_PURPLE        lv_color_hex(0xBC8CFF)
#define COLOR_CYAN          lv_color_hex(0x39C5CF)

/* ========== 全局样式对象 ========== */
extern lv_style_t style_screen_bg;
extern lv_style_t style_card;
extern lv_style_t style_btn_control;
extern lv_style_t style_btn_control_pressed;
extern lv_style_t style_label_title;
extern lv_style_t style_label_value;
extern lv_style_t style_label_desc;

/* ========== 函数声明 ========== */
void ui_styles_init(void);

#endif /* UI_STYLES_H */