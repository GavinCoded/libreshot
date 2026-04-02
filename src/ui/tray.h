#pragma once

#include <QSystemTrayIcon>

namespace libreshot {

class capture;

class tray : public QSystemTrayIcon {
    Q_OBJECT

public:
    explicit tray(capture &cap, QObject *parent = nullptr);
};

}
