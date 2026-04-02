#pragma once

#include "tools/stroke.h"
#include <QPainter>

namespace libreshot {

struct arrow_render {
    static void draw(QPainter &p, const stroke &s);
};

}
