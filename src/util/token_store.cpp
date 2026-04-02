#include "util/token_store.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>

static QString token_path() {
    auto dir = QStandardPaths::writableLocation(
        QStandardPaths::ConfigLocation) + "/libreshot";
    QDir().mkpath(dir);
    return dir + "/restore_token";
}

namespace libreshot {

void token_store::save(const QString &token) {
    QFile f(token_path());
    if (f.open(QIODevice::WriteOnly | QIODevice::Truncate))
        f.write(token.toUtf8());
}

QString token_store::load() {
    QFile f(token_path());
    if (f.open(QIODevice::ReadOnly))
        return QString::fromUtf8(f.readAll()).trimmed();
    return {};
}

}
