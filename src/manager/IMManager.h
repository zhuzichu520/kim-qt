#ifndef IMMANAGER_H
#define IMMANAGER_H

#include <QObject>
#include <QWebSocket>
#include <QDebug>
#include <QJsonObject>
#include <google/protobuf/message.h>
#include <singleton.h>
#include <db/Message.h>
#include <db/Session.h>
#include <QTimer>

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
    Q_INVOKABLE void wsConnect();
    Q_INVOKABLE void userRegister(const QString& account,const QString& password,const QString& confirmPassword,IMCallback* callback = nullptr);
    Q_INVOKABLE void userLogin(const QString& account,const QString& password,IMCallback* callback = nullptr);
    Q_INVOKABLE void userSearch(const QString& keyword,IMCallback* callback = nullptr);
    Q_INVOKABLE void userProfile(IMCallback* callback = nullptr);
    Q_INVOKABLE void userInfo(const QString& account,IMCallback* callback = nullptr);
    Q_INVOKABLE void friendAdd(const QString& friendId,IMCallback* callback = nullptr);
    Q_INVOKABLE void friendRemove(const QString& friendId,IMCallback* callback = nullptr);
    Q_INVOKABLE void friends(IMCallback* callback = nullptr);
    Q_INVOKABLE void sendTextMessage(const QString& receiver,const QString& text,IMCallback* callback,int scene=0);
    Q_INVOKABLE void addEmptySession(QString sessionId,int scene);
    Q_SIGNAL void receiveMessage(Message &message);
    Q_SIGNAL void updateSessionCompleted(Session &session);
    Q_SIGNAL void wsConnected();

    Q_SLOT void onSocketMessage(const QByteArray &message);
    Q_SLOT void handleMsgResent();

    QList<Session> getSessionList();

private:
    QString wsUri();
    QString apiUri();
    void bind();
    void pong();
    void post(const QString& path, QMap<QString, QVariant> params,IMCallback* callback);
    void sendRequest(google::protobuf::Message* message);
    void sendMessage(Message message,IMCallback* callback);
    void sendMessageToLocal(Message& message);
    void updateSessionByMessage(const Message& message);
    Session message2session(const Message &val);
    Message buildMessage(const QString &sessionId, int scene, int type, const QString &content);
private:
    QString _token = "";
    QString _loginAccid = "";
    QWebSocket* _socket = nullptr;
    QString _host = "localhost";
    QString _wsport = "34567";
    QString _apiport = "8080";
    QMap<QString,Message> _msgBuffer;
    QTimer* _msgResentTimer;
};

#endif // IMMANAGER_H
