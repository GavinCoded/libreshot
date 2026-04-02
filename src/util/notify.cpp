#include "util/notify.h"
#include <QDBusConnection>
#include <QDBusInterface>

namespace libreshot {

void notify::send(const QString &summary, const QString &body) {
    QDBusInterface iface(
        "org.freedesktop.Notifications",
        "/org/freedesktop/Notifications",
        "org.freedesktop.Notifications",
        QDBusConnection::sessionBus());

    iface.call("Notify",
        "LibreShot", 0u, QString(),
        summary, body,
        QStringList(), QVariantMap(), 3000);
}

}
