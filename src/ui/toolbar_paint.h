#pragma once

#include "ui/toolbar_data.h"
#include "tools/tool_types.h"
#include <QPainter>
#include <QList>

namespace libreshot {

struct toolbar_paint {
    static void draw(QPainter &p, const QList<btn_entry> &btns,
                     tool_type active_tool);
};

}
