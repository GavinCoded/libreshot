#pragma once

#include <QColor>
#include <QFont>

namespace libreshot::theme {

constexpr int toolbar_btn_w = 32;
constexpr int toolbar_btn_h = 32;
constexpr int action_btn_h = 28;
constexpr int btn_pad = 2;
constexpr int toolbar_gap = 6;
constexpr int edge_margin = 4;
constexpr int btn_radius = 4;
constexpr int select_pad = 10;
constexpr int toolbar_pad = 50;
constexpr int ready_delay_ms = 200;
constexpr int stroke_width = 3;
constexpr int text_font_size = 12;
constexpr int blur_radius = 10;
constexpr int blur_passes = 3;
constexpr int portal_timeout_ms = 30000;

inline QColor dim_overlay() { return {0, 0, 0, 100}; }
inline QColor select_border() { return {60, 140, 255}; }
inline QColor edit_border() { return {100, 160, 255}; }
inline QColor btn_active() { return {80, 130, 255}; }
inline QColor btn_inactive() { return {40, 40, 40, 230}; }
inline QColor draw_default() { return Qt::red; }
inline QColor icon_color() { return Qt::white; }
inline QFont label_font() { return {"sans-serif", 10}; }
inline QFont text_font() { return {"sans-serif", text_font_size}; }

}
