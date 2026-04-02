#pragma once

#include <QObject>
#include <QString>
#include <QPixmap>

namespace libreshot {

class capture : public QObject {
    Q_OBJECT

public:
    explicit capture(QObject *parent = nullptr);

    void fullscreen();
    void active_window();
    void region();

signals:
    void captured(const QPixmap &image);
    void failed(const QString &error);
    void cancelled();
};

}
