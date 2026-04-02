#include "capture/kwin_dbus.h"
#include "capture/screencast_portal.h"
#include "capture/pw_grab.h"

namespace libreshot {

capture_result screen_grab::all_screens() {
    auto sess = screencast_portal::start();
    if (!sess.ok())
        return {{}, sess.error};

    auto frame = pw_grab::frame(sess.pw_fd, sess.pw_node);
    screencast_portal::close(sess.path);

    if (!frame.ok())
        return {{}, frame.error};

    return {QPixmap::fromImage(frame.image), {}};
}

}
