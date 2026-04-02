#pragma once

#include <QWidget>
#include <QScreen>

namespace libreshot {

class region_select;

struct overlay_paint {
    static void draw_screen(QWidget *w, region_select &owner,
                            QScreen *screen);
};

}
