#include <QApplication>
#include <QCommandLineParser>
#include <QLocalSocket>
#include "app/app.h"

static QString socket_name() {
    return "libreshot-" + qEnvironmentVariable("USER");
}

int main(int argc, char *argv[]) {
    QApplication qt_app(argc, argv);
    qt_app.setApplicationName("LibreShot");
    qt_app.setApplicationVersion("0.1.0");
    qt_app.setQuitOnLastWindowClosed(false);

    QCommandLineParser cli;
    cli.addOption({"region", "Take a region screenshot."});
    cli.process(qt_app);

    bool region = cli.isSet("region");

    QLocalSocket sock;
    sock.connectToServer(socket_name());
    if (sock.waitForConnected(300)) {
        if (region) sock.write("region\n");
        sock.waitForBytesWritten(300);
        return 0;
    }

    libreshot::app app(region);
    return qt_app.exec();
}
