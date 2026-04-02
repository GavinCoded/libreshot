#include "util/file_util.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QDateTime>
#include <QDir>

namespace libreshot {

void file_util::save_screenshot(QWidget *parent, const QPixmap &image) {
    auto path = QFileDialog::getSaveFileName(
        parent, "save screenshot", default_path(),
        "PNG (*.png);;JPEG (*.jpg);;BMP (*.bmp)");

    if (path.isEmpty())
        return;

    image.save(path);
}

QString file_util::default_path() {
    auto pictures = QStandardPaths::writableLocation(
        QStandardPaths::PicturesLocation);
    auto timestamp = QDateTime::currentDateTime().toString(
        "yyyy-MM-dd_HH-mm-ss");

    QDir dir(pictures + "/LibreShot");
    dir.mkpath(".");

    return dir.filePath(
        QString("screenshot_%1.png").arg(timestamp));
}

}
