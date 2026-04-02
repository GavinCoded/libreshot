#pragma once

#include <QWidget>
#include <QPixmap>
#include <QPainter>

namespace libreshot {

struct region_painter {
    static void paint(QWidget *widget, const QPixmap &original,
                      const QPixmap &dimmed, const QRect &sel);
};

}
