#include "capture/region_overlay.h"
#include "capture/region_select.h"
#include "capture/overlay_paint.h"
#include "ui/toolbar_data.h"
#include <LayerShellQt/window.h>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QGuiApplication>
#include <QScreen>
#include <QWindow>

namespace libreshot {

region_overlay::region_overlay(region_select &owner, QScreen *screen)
    : QWidget(nullptr, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint),
      owner_(owner), screen_(screen) {

    setCursor(Qt::CrossCursor);
    setMouseTracking(true);
    setAttribute(Qt::WA_NativeWindow);

    auto *lsw = LayerShellQt::Window::get(windowHandle());
    lsw->setLayer(LayerShellQt::Window::LayerOverlay);
    LayerShellQt::Window::Anchors edges;
    edges.setFlag(LayerShellQt::Window::AnchorTop);
    edges.setFlag(LayerShellQt::Window::AnchorBottom);
    edges.setFlag(LayerShellQt::Window::AnchorLeft);
    edges.setFlag(LayerShellQt::Window::AnchorRight);
    lsw->setAnchors(edges);
    lsw->setExclusiveZone(-1);
    lsw->setKeyboardInteractivity(
        LayerShellQt::Window::KeyboardInteractivityExclusive);
    lsw->setScreen(screen);
}

void region_overlay::paintEvent(QPaintEvent *) {
    overlay_paint::draw_screen(this, owner_, screen_);
}

bool region_overlay::hit_toolbar(QPoint lp) {
    if (owner_.state_ != overlay_state::editing) return false;
    auto geo = screen_->geometry();
    auto virt = QGuiApplication::primaryScreen()->virtualGeometry();
    auto sel_local = owner_.selection_.translated(
        virt.topLeft() - geo.topLeft());

    auto scr_sz = QSize(geo.width(), geo.height());
    for (auto &btn : toolbar_data::tools(sel_local, scr_sz))
        if (btn.rect.contains(lp)) {
            if (btn.action >= 0) owner_.on_action(btn.action);
            else owner_.on_tool_click(btn.tool);
            return true;
        }
    for (auto &btn : toolbar_data::actions(sel_local, scr_sz))
        if (btn.rect.contains(lp)) {
            owner_.on_action(btn.action);
            return true;
        }
    return false;
}

void region_overlay::mousePressEvent(QMouseEvent *event) {
    if (event->button() != Qt::LeftButton) return;
    if (!hit_toolbar(event->pos()))
        owner_.on_press(event->globalPosition().toPoint());
}

void region_overlay::mouseMoveEvent(QMouseEvent *event) {
    owner_.on_move(event->globalPosition().toPoint());
}

void region_overlay::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        owner_.on_release(event->globalPosition().toPoint());
}

void region_overlay::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape && !owner_.text_in_.active())
        owner_.on_cancel();
    else
        owner_.on_key(event->key(), event->text());
}

}
