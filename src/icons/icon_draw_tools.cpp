#include "icons/icon_paint.h"
#include "ui/toolbar_data.h"
#include <QPainterPath>

namespace libreshot {

void icon_paint::tool(QPainter &p, QRect r, tool_type t) {
    switch (t) {
    case tool_type::pen: pen(p, r); break;
    case tool_type::line: line(p, r); break;
    case tool_type::arrow: arrow(p, r); break;
    case tool_type::rect: rect(p, r); break;
    case tool_type::blur: blur(p, r); break;
    case tool_type::text: text(p, r); break;
    default: break;
    }
}

void icon_paint::action(QPainter &p, QRect r, int a) {
    switch (a) {
    case action_copy: copy(p, r); break;
    case action_save: save(p, r); break;
    case action_close: close(p, r); break;
    case action_undo: undo(p, r); break;
    }
}

void icon_paint::pen(QPainter &p, QRect r) {
    p.setPen(QPen(Qt::white, 1.5));
    auto c = r.center();
    p.drawLine(c.x() - 7, c.y() + 7, c.x() + 5, c.y() - 5);
    p.drawLine(c.x() + 5, c.y() - 5, c.x() + 7, c.y() - 7);
    p.drawRect(c.x() - 8, c.y() + 7, 3, 3);
}

void icon_paint::line(QPainter &p, QRect r) {
    p.setPen(QPen(Qt::white, 2));
    auto c = r.center();
    p.drawLine(c.x() - 7, c.y() + 7, c.x() + 7, c.y() - 7);
}

void icon_paint::arrow(QPainter &p, QRect r) {
    p.setPen(QPen(Qt::white, 2));
    auto c = r.center();
    p.drawLine(c.x() - 7, c.y() + 7, c.x() + 7, c.y() - 7);

    p.setBrush(Qt::white);
    QPolygonF head;
    head << QPointF(c.x() + 7, c.y() - 7)
         << QPointF(c.x() + 1, c.y() - 5)
         << QPointF(c.x() + 5, c.y() - 1);
    p.drawPolygon(head);
    p.setBrush(Qt::NoBrush);
}

}
