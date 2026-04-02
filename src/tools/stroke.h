#pragma once

#include "tools/tool_types.h"
#include <QColor>
#include <QPoint>
#include <QList>
#include <QString>

namespace libreshot {

struct stroke {
    tool_type tool = tool_type::none;
    QColor color = Qt::red;
    int width = 3;
    QList<QPoint> points;
    QString text;
};

}
