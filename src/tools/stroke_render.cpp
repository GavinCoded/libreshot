#include "tools/stroke_render.h"
#include "ui/theme.h"

namespace libreshot {

void stroke_render::draw(QPainter &p, const stroke &s) {
    p.setPen(QPen(s.color, s.width, Qt::SolidLine,
        Qt::RoundCap, Qt::RoundJoin));
    p.setBrush(Qt::NoBrush);

    switch (s.tool) {
    case tool_type::pen: draw_pen(p, s); break;
    case tool_type::line: draw_line(p, s); break;
    case tool_type::arrow: break;
    case tool_type::rect: draw_rect(p, s); break;
    case tool_type::text: draw_text(p, s); break;
    default: break;
    }
}

void stroke_render::draw_pen(QPainter &p, const stroke &s) {
    if (s.points.size() < 2) return;
    for (int i = 1; i < s.points.size(); i++)
        p.drawLine(s.points[i - 1], s.points[i]);
}

void stroke_render::draw_line(QPainter &p, const stroke &s) {
    if (s.points.size() < 2) return;
    p.drawLine(s.points.first(), s.points.last());
}

void stroke_render::draw_rect(QPainter &p, const stroke &s) {
    if (s.points.size() < 2) return;
    p.drawRect(QRect(s.points.first(), s.points.last()).normalized());
}

void stroke_render::draw_text(QPainter &p, const stroke &s) {
    if (s.points.isEmpty() || s.text.isEmpty()) return;
    p.setFont(theme::text_font());
    p.drawText(s.points.first(), s.text);
}

}
