#include "capture/text_cursor_paint.h"
#include "ui/theme.h"
#include <QFontMetrics>

namespace libreshot {

void text_cursor_paint::draw(QPainter &p, QPoint pos,
                              const QString &txt, QColor color,
                              bool show_cursor) {
    auto font = theme::text_font();
    p.setFont(font);
    p.setPen(color);
    p.drawText(pos, txt);
    if (show_cursor) {
        int tx = QFontMetrics(font).horizontalAdvance(txt);
        int h = QFontMetrics(font).height();
        p.setPen(QPen(color, 2));
        p.drawLine(pos.x() + tx, pos.y() - h + 2,
                   pos.x() + tx, pos.y() + 3);
    }
}

}
