#pragma once

#include "tools/stroke.h"
#include <QPixmap>

namespace libreshot {

struct blur_render {
    static void apply(QPixmap &target, const stroke &s);
};

}
