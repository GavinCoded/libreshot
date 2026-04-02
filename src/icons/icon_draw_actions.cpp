#include "icons/icon_paint.h"
#include <QPainterPath>

namespace libreshot {

void icon_paint::rect(QPainter &p, QRect r) {
    p.setPen(QPen(Qt::white, 1.5));
    auto c = r.center();
    p.drawRect(c.x() - 6, c.y() - 5, 12, 10);
}

void icon_paint::blur(QPainter &p, QRect r) {
    p.setPen(Qt::NoPen);
    int x0 = r.center().x() - 7, y0 = r.center().y() - 7;
    for (int i = 0; i < 9; i++) {
        p.setBrush(QColor(255, 255, 255, (i % 2 == 0) ? 255 : 120));
        p.drawRect(x0 + (i % 3) * 5, y0 + (i / 3) * 5, 4, 4);
    }
    p.setBrush(Qt::NoBrush);
}

void icon_paint::text(QPainter &p, QRect r) {
    p.setPen(Qt::white);
    p.setFont(QFont("sans-serif", 14, QFont::Bold));
    p.drawText(r, Qt::AlignCenter, "T");
}

void icon_paint::undo(QPainter &p, QRect r) {
    p.setPen(QPen(Qt::white, 1.5));
    auto c = r.center();
    QPainterPath path;
    path.moveTo(c.x() + 5, c.y() - 4);
    path.arcTo(c.x() - 7, c.y() - 7, 14, 14, 60, -240);
    p.drawPath(path);

    p.setBrush(Qt::white);
    QPolygonF tip;
    tip << QPointF(c.x() - 3, c.y() - 7)
        << QPointF(c.x() + 3, c.y() - 4)
        << QPointF(c.x() - 1, c.y() - 1);
    p.drawPolygon(tip);
    p.setBrush(Qt::NoBrush);
}

void icon_paint::copy(QPainter &p, QRect r) {
    p.setPen(QPen(Qt::white, 1.5));
    auto c = r.center();
    p.drawRect(c.x() - 3, c.y() - 7, 10, 12);
    p.drawRect(c.x() - 7, c.y() - 3, 10, 12);
}

void icon_paint::save(QPainter &p, QRect r) {
    p.setPen(QPen(Qt::white, 1.5));
    auto c = r.center();
    p.drawRect(c.x() - 7, c.y() - 7, 14, 14);
    p.drawRect(c.x() - 4, c.y() - 7, 8, 5);
    p.setBrush(Qt::white);
    p.drawRect(c.x() + 2, c.y() - 6, 3, 3);
    p.setBrush(Qt::NoBrush);
    p.drawRect(c.x() - 5, c.y() + 2, 10, 5);
}

void icon_paint::close(QPainter &p, QRect r) {
    p.setPen(QPen(Qt::white, 2));
    auto c = r.center();
    p.drawLine(c.x() - 5, c.y() - 5, c.x() + 5, c.y() + 5);
    p.drawLine(c.x() + 5, c.y() - 5, c.x() - 5, c.y() + 5);
}

}
