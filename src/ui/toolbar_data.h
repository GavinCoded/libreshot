#pragma once

#include "tools/tool_types.h"
#include <QRect>
#include <QList>
#include <QSize>

namespace libreshot {

struct btn_entry {
    QRect rect;
    tool_type tool = tool_type::none;
    int action = -1;
};

enum action_id {
    action_copy = 0,
    action_save = 1,
    action_close = 2,
    action_undo = 3,
};

struct toolbar_data {
    static QList<btn_entry> tools(QRect selection, QSize screen);
    static QList<btn_entry> actions(QRect selection, QSize screen);
};

}
