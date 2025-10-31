/**
 * @file ui_card.c
 * 状态卡片实现
 */

#include "ui_card.h"
#include "ui_styles.h"
#include <stdio.h>

lv_obj_t* ui_card_create(lv_obj_t *parent, const ui_card_config_t *config)
{
    /* 创建卡片容器 */
    lv_obj_t *card = lv_obj_create(parent);
    lv_obj_set_size(card, 230, 180);
    lv_obj_add_style(card, &style_card, 0);
    lv_obj_clear_flag(card, LV_OBJ_FLAG_SCROLLABLE);

    /* 图标（左上角）*/
    lv_obj_t *label_icon = lv_label_create(card);
    lv_label_set_text(label_icon, config->icon);
    lv_obj_set_style_text_font(label_icon, &lv_font_montserrat_32, 0);
    lv_obj_align(label_icon, LV_ALIGN_TOP_LEFT, 0, 0);

    /* 标题（右上角）*/
    lv_obj_t *label_title = lv_label_create(card);
    lv_label_set_text(label_title, config->title);
    lv_obj_add_style(label_title, &style_card_title, 0);
    lv_obj_set_style_text_font(label_title, &lv_font_montserrat_16, 0);
    lv_obj_align(label_title, LV_ALIGN_TOP_RIGHT, 0, 5);

    /* 数值（中心）*/
    lv_obj_t *label_value = lv_label_create(card);
    lv_label_set_text(label_value, config->value);
    lv_obj_set_style_text_font(label_value, &lv_font_montserrat_28, 0);
    lv_obj_set_style_text_color(label_value, config->value_color, 0);
    lv_obj_align(label_value, LV_ALIGN_CENTER, 0, 5);

    /* 描述（底部）*/
    lv_obj_t *label_desc = lv_label_create(card);
    lv_label_set_text(label_desc, config->desc);
    lv_obj_set_style_text_color(label_desc, COLOR_TEXT_SECOND, 0);
    lv_obj_set_style_text_font(label_desc, &lv_font_montserrat_16, 0);
    lv_obj_align(label_desc, LV_ALIGN_BOTTOM_MID, 0, 0);

    return card;
}

void ui_card_update_value(lv_obj_t *card, const char *value, lv_color_t color)
{
    /* 获取数值标签（第3个子元素）*/
    lv_obj_t *label_value = lv_obj_get_child(card, 2);
    if (label_value) {
        lv_label_set_text(label_value, value);
        lv_obj_set_style_text_color(label_value, color, 0);
    }
}