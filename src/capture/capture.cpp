#include "capture/capture.h"
#include "capture/kwin_dbus.h"
#include "capture/region_select.h"

namespace libreshot {

capture::capture(QObject *parent) : QObject(parent) {}

void capture::fullscreen() {
    auto res = screen_grab::all_screens();
    if (res.ok())
        emit captured(res.image);
    else
        emit failed(res.error);
}

void capture::active_window() {
    fullscreen();
}

void capture::region() {
    auto res = screen_grab::all_screens();
    if (!res.ok()) {
        emit failed(res.error);
        return;
    }

    auto *sel = new region_select(res.image);
    connect(sel, &region_select::selected,  this, &capture::captured);
    connect(sel, &region_select::cancelled, this, &capture::cancelled);
    connect(sel, &region_select::cancelled, sel,  &QObject::deleteLater);
    connect(sel, &region_select::selected,  sel,  &QObject::deleteLater);
    sel->show();
}

}
