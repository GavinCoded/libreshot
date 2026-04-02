#include "capture/region_painter.h"
#include "ui/theme.h"

namespace libreshot {

void region_painter::paint(QWidget *widget, const QPixmap &original,
                           const QPixmap &dimmed, const QRect &sel) {
    QPainter p(widget);
    p.drawPixmap(0, 0, dimmed);

    if (!sel.isNull() && sel.isValid()) {
        p.drawPixmap(sel, original, sel);
        p.setPen(QPen(theme::select_border(), 2));
        p.drawRect(sel);
    }
}

}
