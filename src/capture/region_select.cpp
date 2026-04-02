#include "capture/region_select.h"
#include "capture/region_overlay.h"
#include "ui/toolbar_data.h"
#include "ui/theme.h"
#include "util/file_util.h"
#include "util/notify.h"
#include <QGuiApplication>
#include <QScreen>
#include <QClipboard>
#include <QTimer>

namespace libreshot {

region_select::region_select(const QPixmap &screenshot, QObject *parent)
    : QObject(parent), screenshot_(screenshot) {
    for (auto *screen : QGuiApplication::screens())
        overlays_.append(new region_overlay(*this, screen));

    connect(&text_in_, &text_input::changed, this,
        &region_select::update_all);
    connect(&text_in_, &text_input::committed, this,
        [this](QPoint pos, const QString &txt) {
            canvas_.begin(tool_type::text, pos, draw_color_,
                theme::stroke_width);
            canvas_.set_text(txt);
            canvas_.finish();
            update_all();
        });
}

region_select::~region_select() { qDeleteAll(overlays_); }

void region_select::show() {
    for (auto *o : overlays_) o->show();
    QTimer::singleShot(theme::ready_delay_ms, this,
        [this]() { ready_ = true; });
}

void region_select::on_tool_click(tool_type t) {
    if (text_in_.active()) text_in_.commit();
    active_tool_ = t;
    update_all();
}

void region_select::on_cancel() {
    emit cancelled();
    for (auto *o : overlays_) o->close();
}

void region_select::update_all() {
    for (auto *o : overlays_) o->update();
}

QPixmap region_select::final_image() {
    if (text_in_.active()) text_in_.commit();
    return canvas_.render(screenshot_.copy(selection_), selection_);
}

void region_select::on_key(int key, const QString &text) {
    if (text_in_.active())
        text_in_.on_key(key, text);
}

void region_select::on_action(int action) {
    if (text_in_.active()) text_in_.commit();
    if (action == action_copy) {
        QGuiApplication::clipboard()->setPixmap(final_image());
        notify::send("LibreShot", "Screenshot copied to clipboard.");
        on_cancel();
    } else if (action == action_save) {
        file_util::save_screenshot(nullptr, final_image());
        on_cancel();
    } else if (action == action_close) {
        on_cancel();
    } else if (action == action_undo) {
        canvas_.undo(); update_all();
    }
}

}
