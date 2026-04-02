#pragma once

#include "tools/tool_types.h"
#include <QPainter>
#include <QRect>

namespace libreshot {

struct icon_paint {
    static void tool(QPainter &p, QRect r, tool_type t);
    static void action(QPainter &p, QRect r, int action);
    static void pen(QPainter &p, QRect r);
    static void line(QPainter &p, QRect r);
    static void arrow(QPainter &p, QRect r);
    static void rect(QPainter &p, QRect r);
    static void blur(QPainter &p, QRect r);
    static void text(QPainter &p, QRect r);
    static void undo(QPainter &p, QRect r);
    static void copy(QPainter &p, QRect r);
    static void save(QPainter &p, QRect r);
    static void close(QPainter &p, QRect r);
};

}
