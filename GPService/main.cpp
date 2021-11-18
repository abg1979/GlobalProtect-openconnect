#include <QtDBus/QtDBus>

#include "gpservice.h"
#include "singleapplication.h"

#ifndef WIN32
#include "sigwatch.h"
#endif

int main(int argc, char *argv[])
{
    SingleApplication app(argc, argv);

    if (!QDBusConnection::sessionBus().isConnected()) {
        qWarning("Cannot connect to the D-Bus session bus.\n"
                 "Please check your system settings and try again.\n");
        return 1;
    }

    GPService service;

#ifndef WIN32
    UnixSignalWatcher sigwatch;
    sigwatch.watchForSignal(SIGINT);
    sigwatch.watchForSignal(SIGTERM);
    sigwatch.watchForSignal(SIGQUIT);
    sigwatch.watchForSignal(SIGHUP);
    QObject::connect(&sigwatch, &UnixSignalWatcher::unixSignal, &service, &GPService::quit);
#endif
    return app.exec();
}
