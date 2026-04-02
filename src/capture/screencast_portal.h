#pragma once

#include <QString>
#include <QDBusObjectPath>

namespace libreshot {

struct screencast_portal {
    struct session {
        QDBusObjectPath path;
        int pw_fd = -1;
        uint pw_node = 0;
        QString error;
        bool ok() const { return error.isEmpty(); }
    };

    static session start();
    static void close(const QDBusObjectPath &path);

    static QString restore_token;
};

}
