#pragma once

#include <QPixmap>

class QWidget;

namespace libreshot {

struct file_util {
    static void save_screenshot(QWidget *parent, const QPixmap &image);
    static QString default_path();
};

}
