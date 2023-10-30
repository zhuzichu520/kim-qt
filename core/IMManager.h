#ifndef IMMANAGER_H
#define IMMANAGER_H

#include <QObject>
#include <QWebSocket>
#include "singleton.h"

class IMManager : public QObject
{
    Q_OBJECT
private:
    explicit IMManager(QObject *parent = nullptr);
public:
    SINGLETONG(IMManager)
    void wsConnect();
private:
    QString wsUri();
private slots:
    void onSocketMessage(const QString &message);
private:
    QWebSocket _socket;
    QString _host = "124.222.224.186";
    QString _port = "8800";
};

#endif // IMMANAGER_H
