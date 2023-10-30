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
    QString _host = "localhost";
    QString _port = "34567";
};

#endif // IMMANAGER_H
