#ifndef IMMANAGER_H
#define IMMANAGER_H

#include <QObject>
#include <QWebSocket>
#include <qDebug>
#include <QJsonObject>
#include "singleton.h"

class IMCallback: public QObject{
    Q_OBJECT
public:
    explicit IMCallback(QObject *parent = nullptr){};
    ~IMCallback(){
        qDebug()<<"-----~IMCallback------";
    };
    Q_SIGNAL void start();
    Q_SIGNAL void finish();
    Q_SIGNAL void success(QJsonObject result);
    Q_SIGNAL void error(int code,QString message);
};

class IMManager : public QObject
{
    Q_OBJECT
private:
    explicit IMManager(QObject *parent = nullptr);
    ~IMManager();
public:
    SINGLETONG(IMManager)
    void wsConnect(const QString& token);
    Q_INVOKABLE void userRegister(const QString& account,const QString& password,IMCallback* callback = nullptr);
    Q_INVOKABLE void userLogin(const QString& account,const QString& password,IMCallback* callback = nullptr);
private:
    QString wsUri();
    QString apiUri();
    void post(const QString& path, QMap<QString, QVariant> params,IMCallback* callback);
private slots:
    void onSocketMessage(const QString &message);
private:
    QWebSocket* _socket = nullptr;
    QString _host = "192.168.0.109";
    QString _wsport = "34567";
    QString _apiport = "8080";
};

#endif // IMMANAGER_H
