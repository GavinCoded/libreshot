#pragma once

#include "tools/tool_types.h"
#include "tools/canvas.h"
#include "tools/text_input.h"
#include <QObject>
#include <QPixmap>
#include <QPoint>
#include <QColor>
#include <QList>

namespace libreshot {

class region_overlay;

class region_select : public QObject {
    Q_OBJECT

public:
    explicit region_select(const QPixmap &screenshot,
                           QObject *parent = nullptr);
    ~region_select();
    void show();

signals:
    void selected(const QPixmap &cropped);
    void cancelled();

public:
    friend class region_overlay;
    void on_press(QPoint global_pos);
    void on_move(QPoint global_pos);
    void on_release(QPoint global_pos);
    void on_cancel();
    void on_tool_click(tool_type tool);
    void on_action(int action);
    void on_key(int key, const QString &text);
    void update_all();
    QPixmap final_image();

    QPixmap screenshot_;
    QList<region_overlay *> overlays_;
    QPoint start_;
    QPoint end_;
    overlay_state state_ = overlay_state::selecting;
    tool_type active_tool_ = tool_type::none;
    QColor draw_color_ = Qt::red;
    canvas canvas_;
    text_input text_in_;
    QRect selection_;
    bool ready_ = false;
    bool mouse_down_ = false;
    bool text_drag_ = false;
};

}
