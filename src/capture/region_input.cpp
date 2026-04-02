#include "capture/region_select.h"
#include "ui/theme.h"
#include <QGuiApplication>
#include <QScreen>

namespace libreshot {

void region_select::on_press(QPoint gp) {
    if (!ready_) return;
    auto virt = QGuiApplication::primaryScreen()->virtualGeometry();
    auto gp_local = gp - virt.topLeft();

    if (state_ == overlay_state::selecting) {
        start_ = gp; end_ = gp; mouse_down_ = true;
    } else if (state_ == overlay_state::editing) {
        auto sel_padded = selection_.adjusted(
            -theme::select_pad, -theme::select_pad,
            theme::toolbar_pad, theme::toolbar_pad);

        if (text_in_.active()) {
            text_drag_ = true;
            mouse_down_ = true;
            text_in_.set_pos(gp_local - selection_.topLeft());
        } else if (!sel_padded.contains(gp_local)) {
            state_ = overlay_state::selecting;
            canvas_ = canvas{};
            active_tool_ = tool_type::none;
            start_ = gp; end_ = gp; mouse_down_ = true;
        } else if (active_tool_ == tool_type::text) {
            text_in_.start(gp_local - selection_.topLeft());
        } else if (active_tool_ != tool_type::none) {
            canvas_.begin(active_tool_, gp_local - selection_.topLeft(),
                draw_color_, theme::stroke_width);
            state_ = overlay_state::drawing;
            mouse_down_ = true;
        }
    }
    update_all();
}

void region_select::on_move(QPoint gp) {
    if (!ready_ || !mouse_down_) return;
    if (!(QGuiApplication::mouseButtons() & Qt::LeftButton)) {
        mouse_down_ = false; text_drag_ = false; return;
    }
    auto virt = QGuiApplication::primaryScreen()->virtualGeometry();
    if (state_ == overlay_state::selecting) {
        end_ = gp;
    } else if (text_drag_ && text_in_.active()) {
        text_in_.set_pos(gp - virt.topLeft() - selection_.topLeft());
    } else if (state_ == overlay_state::drawing) {
        canvas_.update(gp - virt.topLeft() - selection_.topLeft());
    }
    update_all();
}

void region_select::on_release(QPoint gp) {
    if (!ready_) return;
    mouse_down_ = false;
    text_drag_ = false;
    if (state_ == overlay_state::selecting) {
        end_ = gp;
        auto rect = QRect(start_, end_).normalized();
        if (rect.width() > 5 && rect.height() > 5) {
            auto virt =
                QGuiApplication::primaryScreen()->virtualGeometry();
            selection_ = rect.translated(-virt.topLeft());
            state_ = overlay_state::editing;
        }
    } else if (state_ == overlay_state::drawing) {
        canvas_.finish();
        state_ = overlay_state::editing;
    }
    update_all();
}

}
