#include "capture/pw_stream_data.h"
#include <spa/param/video/format-utils.h>
#include <spa/pod/builder.h>

namespace libreshot {

QString pw_stream_setup(pw_state *state, pw_core *core,
    uint32_t node, const pw_stream_events *events) {

    auto *props = pw_properties_new(
        PW_KEY_MEDIA_TYPE, "Video",
        PW_KEY_MEDIA_CATEGORY, "Capture",
        PW_KEY_MEDIA_ROLE, "Screen",
        nullptr);

    state->stream = pw_stream_new(core, "libreshot", props);
    if (!state->stream)
        return "failed to create stream";

    pw_stream_add_listener(state->stream,
        &state->listener, events, state);

    uint8_t buf[1024];
    spa_pod_builder b;
    spa_pod_builder_init(&b, buf, sizeof(buf));

    auto *param = static_cast<const spa_pod *>(
        spa_pod_builder_add_object(&b,
            SPA_TYPE_OBJECT_Format, SPA_PARAM_EnumFormat,
            SPA_FORMAT_mediaType, SPA_POD_Id(SPA_MEDIA_TYPE_video),
            SPA_FORMAT_mediaSubtype, SPA_POD_Id(SPA_MEDIA_SUBTYPE_raw),
            SPA_FORMAT_VIDEO_format, SPA_POD_CHOICE_ENUM_Id(
                3, SPA_VIDEO_FORMAT_BGRx,
                SPA_VIDEO_FORMAT_RGBx, SPA_VIDEO_FORMAT_RGBA)));

    auto flags = static_cast<pw_stream_flags>(
        PW_STREAM_FLAG_AUTOCONNECT | PW_STREAM_FLAG_MAP_BUFFERS);

    pw_stream_connect(state->stream, PW_DIRECTION_INPUT,
        node, flags, &param, 1);

    return {};
}

}
