#pragma once

namespace libreshot {

enum class tool_type {
    none,
    pen,
    line,
    arrow,
    rect,
    blur,
    text,
};

enum class overlay_state {
    selecting,
    editing,
    drawing,
};

}
