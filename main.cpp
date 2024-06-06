#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "NotificationClient.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    NotificationClient *notificationClient = new NotificationClient(&app);
    qmlRegisterSingletonInstance("androidnotifier", 1, 0, "NotificationClient", notificationClient);

    engine.loadFromModule("androidnotifier", "Main");
    return app.exec();
}
