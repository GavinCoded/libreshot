#pragma once

#include <QString>

namespace libreshot {

struct token_store {
    static void save(const QString &token);
    static QString load();
};

}
