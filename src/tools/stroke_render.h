#pragma once

#include "tools/stroke.h"
#include <QPainter>
#include <QPixmap>

namespace libreshot {

struct stroke_render {
    static void draw(QPainter &p, const stroke &s);
    static void draw_pen(QPainter &p, const stroke &s);
    static void draw_line(QPainter &p, const stroke &s);
    static void draw_arrow(QPainter &p, const stroke &s);
    static void draw_rect(QPainter &p, const stroke &s);
    static void draw_blur(QPainter &p, const stroke &s, QPixmap *target);
    static void draw_text(QPainter &p, const stroke &s);
};

}
