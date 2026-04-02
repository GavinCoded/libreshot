#pragma once

#include <QPixmap>
#include <QString>

namespace libreshot {

struct capture_result {
    QPixmap image;
    QString error;
    bool ok() const { return error.isEmpty(); }
};

struct screen_grab {
    static capture_result all_screens();
};

}
