#include "tools/canvas.h"
#include "tools/stroke_render.h"
#include "tools/arrow_render.h"
#include "tools/blur_render.h"
#include <QPainter>

namespace libreshot {

void canvas::begin(tool_type tool, QPoint pos, QColor color, int w) {
    current_ = stroke{};
    current_.tool = tool;
    current_.color = color;
    current_.width = w;
    current_.points << pos;
    active_ = true;
}

void canvas::update(QPoint pos) {
    if (!active_) return;
    current_.points << pos;
}

void canvas::finish() {
    if (!active_) return;
    strokes_ << current_;
    current_ = stroke{};
    active_ = false;
}

void canvas::set_text(const QString &text) {
    if (!active_) return;
    current_.text = text;
}

void canvas::undo() {
    if (!strokes_.isEmpty())
        strokes_.removeLast();
}

QPixmap canvas::render(const QPixmap &base, const QRect &) const {
    QPixmap result = base;

    auto all = strokes_;
    if (active_) all << current_;

    for (auto &s : all) {
        if (s.tool == tool_type::blur) {
            blur_render::apply(result, s);
            continue;
        }

        QPainter p(&result);
        p.setRenderHint(QPainter::Antialiasing);
        if (s.tool == tool_type::arrow)
            arrow_render::draw(p, s);
        else
            stroke_render::draw(p, s);
    }

    return result;
}

}
