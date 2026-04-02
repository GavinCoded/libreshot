#include "capture/screencast_portal.h"
#include "capture/portal_handler.h"
#include "util/token_store.h"
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDBusUnixFileDescriptor>
#include <unistd.h>

namespace libreshot {

namespace {
    constexpr auto k_service  = "org.freedesktop.portal.Desktop";
    constexpr auto k_path     = "/org/freedesktop/portal/desktop";
    constexpr auto k_iface    = "org.freedesktop.portal.ScreenCast";
    constexpr auto k_sess_iface = "org.freedesktop.portal.Session";
    constexpr auto k_sess_token = "libreshot_s";
}

QString screencast_portal::restore_token;

screencast_portal::session screencast_portal::start() {
    if (restore_token.isEmpty())
        restore_token = token_store::load();

    auto bus = QDBusConnection::sessionBus();
    QDBusInterface sc(k_service, k_path, k_iface, bus);

    portal_handler h1;
    sc.call("CreateSession", QVariantMap{
        {"handle_token", h1.token()},
        {"session_handle_token", QString(k_sess_token)},
    });
    QString err;
    h1.wait(err);
    if (!err.isEmpty()) return {{}, -1, 0, err};

    auto sess_path = h1.session_path();

    portal_handler h2;
    QVariantMap sel_opts{
        {"handle_token", h2.token()},
        {"types", 1u},
        {"multiple", true},
        {"persist_mode", 2u},
    };
    if (!restore_token.isEmpty())
        sel_opts["restore_token"] = restore_token;
    sc.call("SelectSources", QDBusObjectPath(sess_path), sel_opts);
    h2.wait(err);
    if (!err.isEmpty()) return {{}, -1, 0, err};

    portal_handler h3;
    sc.call("Start", QDBusObjectPath(sess_path), "",
        QVariantMap{{"handle_token", h3.token()}});
    h3.wait(err);
    if (!err.isEmpty()) return {{}, -1, 0, err};

    if (!h3.restore_token().isEmpty()) {
        restore_token = h3.restore_token();
        token_store::save(restore_token);
    }

    auto streams = h3.streams();
    if (streams.isEmpty())
        return {{}, -1, 0, "no streams returned"};

    QDBusReply<QDBusUnixFileDescriptor> fd_reply =
        sc.call("OpenPipeWireRemote",
            QDBusObjectPath(sess_path), QVariantMap());

    if (!fd_reply.isValid())
        return {{}, -1, 0, fd_reply.error().message()};

    int fd = dup(fd_reply.value().fileDescriptor());
    return {QDBusObjectPath(sess_path), fd, streams.first().first, {}};
}

void screencast_portal::close(const QDBusObjectPath &path) {
    QDBusInterface sess(k_service, path.path(), k_sess_iface,
        QDBusConnection::sessionBus());
    sess.call("Close");
}

}
