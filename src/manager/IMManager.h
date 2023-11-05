#ifndef IMMANAGER_H
#define IMMANAGER_H

#include <QObject>
#include <QWebSocket>
#include <qDebug>
#include <QJsonObject>
#include <google/protobuf/message.h>
#include <singleton.h>

class IMCallback: public QObject{
    Q_OBJECT
public:
    explicit IMCallback(QObject *parent = nullptr){};
    ~IMCallback(){};
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
    Q_INVOKABLE void wsConnect(const QString& token);
    Q_INVOKABLE void userRegister(const QString& account,const QString& password,const QString& confirmPassword,IMCallback* callback = nullptr);
    Q_INVOKABLE void userLogin(const QString& account,const QString& password,IMCallback* callback = nullptr);
    Q_INVOKABLE void userSearch(const QString& keyword,IMCallback* callback = nullptr);
    Q_INVOKABLE void userProfile(IMCallback* callback = nullptr);
    Q_INVOKABLE void friendAdd(const QString& friendId,IMCallback* callback = nullptr);
    Q_INVOKABLE void friendRemove(const QString& friendId,IMCallback* callback = nullptr);
    Q_INVOKABLE void friends(IMCallback* callback = nullptr);
    Q_INVOKABLE void sendTextMessage(const QString& receiver,const QString& text,IMCallback* callback);
    Q_SIGNAL void wsConnected();

    Q_SLOT void onSocketMessage(const QByteArray &message);
private:
    QString wsUri();
    QString apiUri();
    void bind(const QString& token);
    void pong();
    void post(const QString& path, QMap<QString, QVariant> params,IMCallback* callback);
    void sendRequest(google::protobuf::Message* message);
    void sendMessage(const QString& receiver,int type,const QJsonObject& content,IMCallback* callback);
private:
    QString _token = "";
    QWebSocket* _socket = nullptr;
    QString _host = "localhost";
    QString _wsport = "34567";
    QString _apiport = "8080";
};

#endif // IMMANAGER_H