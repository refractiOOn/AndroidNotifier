#pragma once

#include <QObject>

class NotificationClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString notification READ notification WRITE setNotification NOTIFY notificationChanged FINAL)

public:
    explicit NotificationClient(QObject *parent = 0);

    void setNotification(const QString &notification);
    QString notification() const;

private:
    void updateAndroidNotification();

private:
    QString m_notification;

signals:
    void notificationChanged();

};
