#include "icons/app_icon.h"
#include <QSvgRenderer>
#include <QPainter>
#include <QPixmap>

namespace libreshot {

QIcon app_icon::make() {
    QSvgRenderer svg(QString(":/icons/libreshot.svg"));
    QIcon icon;
    for (int sz : {16, 22, 32, 48, 64, 128}) {
        QPixmap pm(sz, sz);
        pm.fill(Qt::transparent);
        QPainter p(&pm);
        svg.render(&p);
        icon.addPixmap(pm);
    }
    return icon;
}

}
