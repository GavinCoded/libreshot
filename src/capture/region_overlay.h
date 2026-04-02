#pragma once

#include <QWidget>

class QScreen;

namespace libreshot {

class region_select;

class region_overlay : public QWidget {
    Q_OBJECT

public:
    region_overlay(region_select &owner, QScreen *screen);
    QScreen *screen() const { return screen_; }

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    bool hit_toolbar(QPoint local_pos);
    region_select &owner_;
    QScreen *screen_;
};

}
