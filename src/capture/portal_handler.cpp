#include "capture/portal_handler.h"
#include "ui/theme.h"
#include <QDBusConnection>
#include <QDBusArgument>
#include <QRandomGenerator>
#include <QTimer>

namespace libreshot {

portal_handler::portal_handler(QObject *parent) : QObject(parent) {
    auto id = QRandomGenerator::global()->generate();
    token_ = QString("libreshot_%1").arg(id);

    auto sender = QDBusConnection::sessionBus()
        .baseService().mid(1).replace('.', '_');
    handle_path_ = QString(
        "/org/freedesktop/portal/desktop/request/%1/%2")
        .arg(sender, token_);

    QDBusConnection::sessionBus().connect(
        "org.freedesktop.portal.Desktop",
        handle_path_,
        "org.freedesktop.portal.Request",
        "Response",
        this,
        SLOT(on_response(uint, QVariantMap)));
}

void portal_handler::wait(QString &error) {
    if (!responded_) {
        QTimer::singleShot(theme::portal_timeout_ms, &loop_,
            &QEventLoop::quit);
        loop_.exec();
    }

    if (!responded_)
        error = "portal timed out";
    else if (!error_.isEmpty())
        error = error_;
}

void portal_handler::on_response(uint code, QVariantMap results) {
    responded_ = true;
    if (code != 0) {
        error_ = "portal request denied";
        loop_.quit();
        return;
    }

    session_path_ = results.value("session_handle").toString();
    restore_token_ = results.value("restore_token").toString();

    auto streams_var = results.value("streams");
    if (streams_var.isValid()) {
        const auto arg = streams_var.value<QDBusArgument>();
        arg.beginArray();
        while (!arg.atEnd()) {
            uint node = 0;
            arg.beginStructure();
            arg >> node;
            arg.beginMap();
            QVariantMap props;
            while (!arg.atEnd()) {
                QString key;
                QVariant val;
                arg.beginMapEntry();
                arg >> key >> val;
                arg.endMapEntry();
                props[key] = val;
            }
            arg.endMap();
            arg.endStructure();
            streams_ << stream_info(node, props);
        }
        arg.endArray();
    }

    loop_.quit();
}

}
