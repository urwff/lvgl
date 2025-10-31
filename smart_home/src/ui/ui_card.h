/**
 * @file ui_card.h
 * 状态卡片组件
 */

#ifndef UI_CARD_H
#define UI_CARD_H

#include "lvgl/lvgl.h"

typedef struct {
    const char *icon;         /* 图标 emoji */
    const char *title;        /* 标题 */
    const char *value;        /* 数值 */
    const char *desc;         /* 描述 */
    lv_color_t value_color;   /* 数值颜色 */
} ui_card_config_t;

lv_obj_t* ui_card_create(lv_obj_t *parent, const ui_card_config_t *config);
void ui_card_update_value(lv_obj_t *card, const char *value, lv_color_t color);

#endif /* UI_CARD_H */