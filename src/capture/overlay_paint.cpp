#include "capture/overlay_paint.h"
#include "capture/region_select.h"
#include "capture/region_painter.h"
#include "capture/text_cursor_paint.h"
#include "ui/toolbar_data.h"
#include "ui/toolbar_paint.h"
#include "ui/theme.h"
#include <QPainter>
#include <QGuiApplication>

namespace libreshot {

void overlay_paint::draw_screen(QWidget *w, region_select &owner,
                                QScreen *screen) {
    auto geo = screen->geometry();
    auto virt = QGuiApplication::primaryScreen()->virtualGeometry();
    int ox = geo.x() - virt.x();
    int oy = geo.y() - virt.y();

    QPixmap local = owner.screenshot_.copy(ox, oy,
        geo.width(), geo.height());
    QPixmap dimmed = local;
    QPainter dp(&dimmed);
    dp.fillRect(dimmed.rect(), theme::dim_overlay());
    dp.end();

    QPainter p(w);

    if (owner.state_ == overlay_state::selecting) {
        QRect sel = QRect(owner.start_, owner.end_).normalized();
        region_painter::paint(w, local, dimmed,
            sel.translated(-geo.topLeft()));
        return;
    }

    p.drawPixmap(0, 0, dimmed);

    QRect sel_local = owner.selection_.translated(
        virt.x() - geo.x(), virt.y() - geo.y());

    if (!sel_local.intersects(QRect(0, 0, geo.width(), geo.height())))
        return;

    QPixmap cropped = owner.screenshot_.copy(owner.selection_);
    QPixmap rendered = owner.canvas_.render(cropped, owner.selection_);
    p.drawPixmap(sel_local.topLeft(), rendered);

    p.setPen(QPen(theme::edit_border(), 1, Qt::DashLine));
    p.drawRect(sel_local);

    p.setPen(theme::icon_color());
    p.setFont(theme::label_font());
    p.drawText(sel_local.x(), sel_local.y() - theme::toolbar_gap,
        QString("%1x%2").arg(sel_local.width()).arg(sel_local.height()));

    if (owner.text_in_.active()) {
        auto tp = sel_local.topLeft() + owner.text_in_.pos();
        text_cursor_paint::draw(p, tp, owner.text_in_.text(),
            owner.draw_color_, owner.text_in_.cursor_on());
    }

    auto scr_sz = QSize(geo.width(), geo.height());
    toolbar_paint::draw(p, toolbar_data::tools(sel_local, scr_sz),
        owner.active_tool_);
    toolbar_paint::draw(p, toolbar_data::actions(sel_local, scr_sz),
        tool_type::none);
}

}
