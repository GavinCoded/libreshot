#include "tools/arrow_render.h"
#include <QtMath>

namespace libreshot {

void arrow_render::draw(QPainter &p, const stroke &s) {
    if (s.points.size() < 2) return;
    auto from = s.points.first();
    auto to = s.points.last();

    p.setPen(QPen(s.color, s.width, Qt::SolidLine,
        Qt::RoundCap, Qt::RoundJoin));
    p.drawLine(from, to);

    double angle = atan2(to.y() - from.y(), to.x() - from.x());
    double sz = s.width * 5.0;

    QPointF tip(to);
    QPointF left(to.x() - sz * cos(angle - 0.4),
                 to.y() - sz * sin(angle - 0.4));
    QPointF right(to.x() - sz * cos(angle + 0.4),
                  to.y() - sz * sin(angle + 0.4));

    QPolygonF head;
    head << tip << left << right;

    p.setBrush(s.color);
    p.drawPolygon(head);
}

}
