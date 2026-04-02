#include "ui/toolbar_data.h"
#include "ui/theme.h"

namespace libreshot {

QList<btn_entry> toolbar_data::tools(QRect sel, QSize screen) {
    using namespace theme;
    int tool_h = 7 * (toolbar_btn_h + btn_pad) + edge_margin;

    int x = sel.right() + toolbar_gap;
    int y = sel.top();

    if (x + toolbar_btn_w + toolbar_gap > screen.width())
        x = sel.left() - toolbar_btn_w - toolbar_gap;

    if (y + tool_h > screen.height())
        y = screen.height() - tool_h - edge_margin;
    if (y < edge_margin) y = edge_margin;

    QList<btn_entry> btns;
    tool_type items[] = {
        tool_type::pen, tool_type::line, tool_type::arrow,
        tool_type::rect, tool_type::blur, tool_type::text,
    };

    for (auto t : items) {
        btns << btn_entry{QRect(x, y, toolbar_btn_w, toolbar_btn_h),
            t, -1};
        y += toolbar_btn_h + btn_pad;
    }

    btns << btn_entry{QRect(x, y + edge_margin,
        toolbar_btn_w, toolbar_btn_h), tool_type::none, action_undo};
    return btns;
}

QList<btn_entry> toolbar_data::actions(QRect sel, QSize screen) {
    using namespace theme;
    int bar_w = 3 * (toolbar_btn_w + btn_pad) - btn_pad;

    int y = sel.bottom() + toolbar_gap;
    int x = sel.right() - bar_w;

    if (y + action_btn_h + toolbar_gap > screen.height())
        y = sel.top() - action_btn_h - toolbar_gap;

    if (x < edge_margin) x = edge_margin;
    if (x + bar_w > screen.width())
        x = screen.width() - bar_w - edge_margin;

    QList<btn_entry> btns;
    int actions[] = {action_copy, action_save, action_close};

    for (auto a : actions) {
        btns << btn_entry{QRect(x, y, toolbar_btn_w, action_btn_h),
            tool_type::none, a};
        x += toolbar_btn_w + btn_pad;
    }
    return btns;
}

}
