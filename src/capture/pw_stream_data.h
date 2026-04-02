#pragma once

#include <QImage>
#include <QString>
#include <pipewire/pipewire.h>
#include <spa/param/video/raw.h>

struct pw_stream_events;

namespace libreshot {

struct pw_state {
    pw_main_loop *loop = nullptr;
    pw_stream *stream = nullptr;
    spa_hook listener{};
    spa_video_info_raw format{};
    QImage::Format qt_format = QImage::Format_RGBA8888;
    QImage image;
    bool got_frame = false;
    int width = 0;
    int height = 0;
};

QString pw_stream_setup(pw_state *state, pw_core *core,
    uint32_t node, const pw_stream_events *events);

}
