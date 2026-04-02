#pragma once

#include <QPainter>
#include <QPoint>
#include <QColor>
#include <QString>

namespace libreshot {

struct text_cursor_paint {
    static void draw(QPainter &p, QPoint pos, const QString &txt,
                     QColor color, bool show_cursor);
};

}
