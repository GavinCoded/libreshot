#include "tools/blur_render.h"
#include "ui/theme.h"
#include <QPainter>
#include <QImage>

namespace libreshot {

void blur_render::apply(QPixmap &target, const stroke &s) {
    if (s.points.size() < 2) return;
    QRect area = QRect(s.points.first(), s.points.last()).normalized();
    if (area.isEmpty()) return;

    area = area.intersected(target.rect());
    if (area.isEmpty()) return;

    QImage img = target.toImage();

    for (int pass = 0; pass < theme::blur_passes; pass++) {
        QImage tmp = img.copy(area);
        QImage scaled = tmp.scaled(
            qMax(1, area.width() / theme::blur_radius),
            qMax(1, area.height() / theme::blur_radius),
            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        scaled = scaled.scaled(
            area.width(), area.height(),
            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        QPainter p(&img);
        p.drawImage(area.topLeft(), scaled);
    }

    target = QPixmap::fromImage(img);
}

}
