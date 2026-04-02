#include "ui/tray.h"
#include "capture/capture.h"
#include "icons/app_icon.h"
#include <QMenu>
#include <QApplication>

namespace libreshot {

tray::tray(capture &cap, QObject *parent)
    : QSystemTrayIcon(app_icon::make(), parent) {
    setToolTip("LibreShot");

    auto *menu = new QMenu;
    menu->addAction("Take Screenshot", &cap, &capture::region);
    menu->addSeparator();
    menu->addAction("Quit", qApp, &QApplication::quit);
    setContextMenu(menu);

    connect(this, &QSystemTrayIcon::activated, this,
        [&cap](ActivationReason reason) {
            if (reason == Trigger)
                cap.region();
        });

    show();
}

}
