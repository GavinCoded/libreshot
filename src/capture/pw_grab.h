#pragma once

#include <QImage>
#include <QString>
#include <cstdint>

namespace libreshot {

struct pw_grab {
    struct result {
        QImage image;
        QString error;
        bool ok() const { return error.isEmpty(); }
    };

    static result frame(int fd, uint32_t node);
};

}
