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
#include <QNetworkAccessManager>
#include <QTimer>
#include <stdafx.h>

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
    Q_PROPERTY_AUTO(QString,host)
    Q_PROPERTY_AUTO(QString,port)
    Q_PROPERTY_AUTO(QString,wsport)
private:
    explicit IMManager(QObject *parent = nullptr);
    ~IMManager();
public:
    SINGLETONG(IMManager)
    Q_INVOKABLE void wsConnect();
    Q_INVOKABLE void userRegister(
        const QString& account,
        const QString& password,
        const QString& confirmPassword,
        const QString& name,
        const QString& mobile,
        const QString& email,
        qint64 birthday,
        const QString& avatar,
        IMCallback* callback = nullptr
        );
    Q_INVOKABLE void userLogin(const QString& account,const QString& password,IMCallback* callback = nullptr);
    Q_INVOKABLE void userSearch(const QString& keyword,IMCallback* callback = nullptr);
    Q_INVOKABLE void userProfile(IMCallback* callback = nullptr);
    Q_INVOKABLE void userInfo(const QString& account,IMCallback* callback = nullptr);
    Q_INVOKABLE void friendAdd(const QString& friendId,IMCallback* callback = nullptr);
    Q_INVOKABLE void friendRemove(const QString& friendId,IMCallback* callback = nullptr);
    Q_INVOKABLE void friends(IMCallback* callback = nullptr);
    Q_INVOKABLE void messageRead(const QString& ids,IMCallback* callback = nullptr);
    Q_INVOKABLE void resendMessage(const QString& id,IMCallback* callback);
    Q_INVOKABLE void sendTextMessage(const QString& receiver,const QString& text,IMCallback* callback,int scene=0);
    Q_INVOKABLE void addEmptySession(QString sessionId,int scene);
    Q_INVOKABLE void clearUnreadCount(const QString &sessionId);
    Q_SIGNAL void syncMessageCompleted();
    Q_SIGNAL void messageChanged(QList<Message> data);
    Q_SIGNAL void sessionChanged(QList<Session> data);
    Q_SIGNAL void wsConnected();
    Q_SLOT void onSocketMessage(const QByteArray &message);
    Q_INVOKABLE QString loginAccid();
    Q_INVOKABLE QString token();
    Q_INVOKABLE void openAutoRead(QString sessionId);
    QList<Session> getSessionList();
    QList<Message> getMessageListBySessionId(QString sessionId);
    QList<Message> getMessageByPage(QString sessionId,qint64 anchor = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch(),int pageSize=30);
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
    void syncMessage();
    void updateMessage(Message message);
    void updateSession(Session session);
    void handleFailedMessage();
    Session message2session(const Message& val);
    Message json2message(const QString& login,const QJsonObject& val);
    Message buildMessage(const QString &sessionId, int scene, int type, const QString &content);
private:
    QWebSocket* _socket = nullptr;
    QString _autoReadSessionId = "";
};

#endif // IMMANAGER_H
