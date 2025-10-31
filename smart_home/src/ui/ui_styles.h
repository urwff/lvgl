/**
 * @file ui_styles.h
 * 全局样式系统
 */

#ifndef UI_STYLES_H
#define UI_STYLES_H

#include "lvgl/lvgl.h"

/* ========== 颜色定义 ========== */
#define COLOR_BG_DARK       lv_color_hex(0x1A1A1A)
#define COLOR_CARD_BG       lv_color_hex(0x2D2D2D)
#define COLOR_PRIMARY       lv_color_hex(0x00A6FF)
#define COLOR_TEXT_MAIN     lv_color_hex(0xFFFFFF)
#define COLOR_TEXT_SECOND   lv_color_hex(0x999999)
#define COLOR_SUCCESS       lv_color_hex(0x00CC66)
#define COLOR_WARNING       lv_color_hex(0xFFAA00)
#define COLOR_ERROR         lv_color_hex(0xFF3333)

/* ========== 全局样式对象 ========== */
extern lv_style_t style_screen_bg;
extern lv_style_t style_card;
extern lv_style_t style_card_title;
extern lv_style_t style_card_value;
extern lv_style_t style_btn_primary;
extern lv_style_t style_btn_pressed;

/* ========== 函数声明 ========== */
void ui_styles_init(void);

#endif /* UI_STYLES_H */