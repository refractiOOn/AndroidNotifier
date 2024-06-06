#include "NotificationClient.hpp"
#include <QJniObject>
#include <QCoreApplication>
#include <QtCore/private/qandroidextras_p.h>

using namespace Qt::StringLiterals;

NotificationClient::NotificationClient(QObject *parent)
    : QObject(parent)
{
    if (QNativeInterface::QAndroidApplication::sdkVersion() >= __ANDROID_API_T__) {
        const auto notificationPermission = "android.permission.POST_NOTIFICATIONS"_L1;
        auto requestResult = QtAndroidPrivate::requestPermission(notificationPermission);
        if (requestResult.result() != QtAndroidPrivate::Authorized) {
            qWarning() << "Failed to acquire permission to post notifications "
                          "(required for Android 13+)";
        }
    }

    connect(this, &NotificationClient::notificationChanged,
            this, &NotificationClient::updateAndroidNotification);
}

void NotificationClient::setNotification(const QString &notification)
{
    if (m_notification == notification) return;

    m_notification = notification;
    emit notificationChanged();
}

QString NotificationClient::notification() const
{
    return m_notification;
}

void NotificationClient::updateAndroidNotification()
{
    QJniObject javaNotification = QJniObject::fromString(m_notification);
    QJniObject::callStaticMethod<void>(
                    "com/androidnotifier/NotificationClient",
                    "notify",
                    "(Landroid/content/Context;Ljava/lang/String;)V",
                    QNativeInterface::QAndroidApplication::context(),
                    javaNotification.object<jstring>());
}
