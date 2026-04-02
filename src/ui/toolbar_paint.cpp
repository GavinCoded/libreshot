#include "ui/toolbar_paint.h"
#include "icons/icon_paint.h"
#include "ui/theme.h"

namespace libreshot {

void toolbar_paint::draw(QPainter &p, const QList<btn_entry> &btns,
                         tool_type active_tool) {
    for (auto &btn : btns) {
        bool active = (btn.tool != tool_type::none
            && btn.tool == active_tool);

        p.setPen(Qt::NoPen);
        p.setBrush(active ? theme::btn_active() : theme::btn_inactive());
        p.drawRoundedRect(btn.rect, theme::btn_radius, theme::btn_radius);

        p.setRenderHint(QPainter::Antialiasing);
        if (btn.tool != tool_type::none)
            icon_paint::tool(p, btn.rect, btn.tool);
        else if (btn.action >= 0)
            icon_paint::action(p, btn.rect, btn.action);
    }
}

}
