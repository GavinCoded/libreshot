#include "tools/text_input.h"
#include <Qt>

namespace libreshot {

text_input::text_input(QObject *parent) : QObject(parent) {
    blink_.setInterval(500);
    connect(&blink_, &QTimer::timeout, this, [this]() {
        cursor_on_ = !cursor_on_;
        emit changed();
    });
}

void text_input::start(QPoint pos) {
    active_ = true;
    pos_ = pos;
    text_.clear();
    cursor_on_ = true;
    blink_.start();
    emit changed();
}

void text_input::commit() {
    if (!active_) return;
    active_ = false;
    blink_.stop();
    if (!text_.isEmpty()) emit committed(pos_, text_);
    emit changed();
}

void text_input::cancel() {
    active_ = false;
    text_.clear();
    blink_.stop();
    emit changed();
}

void text_input::on_key(int key, const QString &ch) {
    if (!active_) return;
    if (key == Qt::Key_Return || key == Qt::Key_Enter) {
        commit(); return;
    }
    if (key == Qt::Key_Escape) {
        cancel(); return;
    }
    if (key == Qt::Key_Backspace) {
        text_.chop(1);
    } else if (!ch.isEmpty() && ch[0].isPrint()) {
        text_ += ch;
    }
    cursor_on_ = true;
    blink_.start();
    emit changed();
}

void text_input::set_pos(QPoint pos) {
    pos_ = pos;
    emit changed();
}

}
