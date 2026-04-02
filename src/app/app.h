#pragma once

#include <memory>

class QLocalServer;

namespace libreshot {

class capture;
class tray;

class app {
public:
    explicit app(bool region_now = false);
    ~app();

private:
    void setup_ipc();

    std::unique_ptr<capture> capture_;
    std::unique_ptr<tray>    tray_;
    QLocalServer            *server_ = nullptr;
};

}
