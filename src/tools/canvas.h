#pragma once

#include "tools/stroke.h"
#include <QPixmap>
#include <QList>
#include <QRect>

namespace libreshot {

class canvas {
public:
    void begin(tool_type tool, QPoint pos, QColor color, int width);
    void update(QPoint pos);
    void finish();
    void set_text(const QString &text);
    void undo();

    QPixmap render(const QPixmap &base, const QRect &region) const;
    bool has_active() const { return active_; }
    const stroke &current() const { return current_; }

private:
    QList<stroke> strokes_;
    stroke current_;
    bool active_ = false;
};

}
