#include "capture/pw_grab.h"
#include "capture/pw_stream_data.h"
#include <pipewire/pipewire.h>
#include <spa/param/video/format-utils.h>

static QImage::Format spa_to_qt(uint32_t fmt) {
    switch (fmt) {
    case SPA_VIDEO_FORMAT_BGRx: return QImage::Format_RGB32;
    case SPA_VIDEO_FORMAT_BGRA: return QImage::Format_ARGB32;
    case SPA_VIDEO_FORMAT_RGBx: return QImage::Format_RGBX8888;
    case SPA_VIDEO_FORMAT_RGBA: return QImage::Format_RGBA8888;
    default: return QImage::Format_RGBA8888;
    }
}

static void on_param(void *data, uint32_t id,
                     const struct spa_pod *param) {
    auto *state = static_cast<libreshot::pw_state *>(data);
    if (!param || id != SPA_PARAM_Format) return;

    spa_format_video_raw_parse(param, &state->format);
    state->width = state->format.size.width;
    state->height = state->format.size.height;
    state->qt_format = spa_to_qt(state->format.format);
}

static void on_process(void *data) {
    auto *state = static_cast<libreshot::pw_state *>(data);
    auto *buf = pw_stream_dequeue_buffer(state->stream);
    if (!buf) return;

    auto *sdata = buf->buffer->datas[0].data;
    auto stride = buf->buffer->datas[0].chunk->stride;

    if (sdata && state->width > 0 && !state->got_frame) {
        QImage img(static_cast<uchar *>(sdata),
            state->width, state->height, stride,
            state->qt_format);
        state->image = img.copy();
        state->got_frame = true;
    }

    pw_stream_queue_buffer(state->stream, buf);

    if (state->got_frame)
        pw_main_loop_quit(state->loop);
}

static const pw_stream_events stream_events = {
    .version = PW_VERSION_STREAM_EVENTS,
    .param_changed = on_param,
    .process = on_process,
};

namespace libreshot {

pw_grab::result pw_grab::frame(int fd, uint32_t node) {
    pw_init(nullptr, nullptr);
    pw_state state{};

    state.loop = pw_main_loop_new(nullptr);
    auto *ctx = pw_context_new(
        pw_main_loop_get_loop(state.loop), nullptr, 0);
    auto *core = pw_context_connect_fd(ctx, fd, nullptr, 0);

    if (!core)
        return {{}, "pipewire connect failed"};

    auto r = pw_stream_setup(&state, core, node, &stream_events);
    if (!r.isEmpty()) return {{}, r};

    pw_main_loop_run(state.loop);

    pw_stream_destroy(state.stream);
    pw_core_disconnect(core);
    pw_context_destroy(ctx);
    pw_main_loop_destroy(state.loop);
    pw_deinit();

    if (!state.got_frame)
        return {{}, "no frame received"};

    return {state.image, {}};
}

}
