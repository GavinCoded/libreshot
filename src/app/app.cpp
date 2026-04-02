#include "app/app.h"
#include "capture/capture.h"
#include "ui/tray.h"
#include <QLocalServer>
#include <QLocalSocket>
#include <QTimer>

static QString socket_name() {
    return "libreshot-" + qEnvironmentVariable("USER");
}

namespace libreshot {

app::app(bool region_now)
    : capture_(std::make_unique<capture>()),
      tray_(std::make_unique<tray>(*capture_)) {
    setup_ipc();
    if (region_now)
        QTimer::singleShot(0, capture_.get(), &capture::region);
}

app::~app() = default;

void app::setup_ipc() {
    server_ = new QLocalServer(capture_.get());
    QLocalServer::removeServer(socket_name());
    server_->listen(socket_name());

    QObject::connect(server_, &QLocalServer::newConnection,
        capture_.get(), [this]() {
            auto *sock = server_->nextPendingConnection();
            QObject::connect(sock, &QLocalSocket::readyRead,
                capture_.get(), [this, sock]() {
                    if (sock->readAll().trimmed() == "region")
                        capture_->region();
                    sock->close();
                });
        });
}

}
