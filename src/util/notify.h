#pragma once

#include <QString>

namespace libreshot {

struct notify {
    static void send(const QString &summary, const QString &body);
};

}
