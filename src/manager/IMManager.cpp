#include "IMManager.h"
#include <QUrl>
#include <QMetaEnum>
#include <QThreadPool>
#include <QCoreApplication>
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QJsonDocument>
#include <QLocale>
#include <QSysInfo>
#include <QJsonObject>
#include <helper/SettingsHelper.h>
#include <manager/DBManager.h>
#include <proto/SentBody.pb.h>
#include <proto/Message.pb.h>
#include <proto/ReplyBody.pb.h>

const int DATA_HEADER_LENGTH = 1;
const int MESSAGE = 2;
const int REPLY_BODY = 4;
const int SENT_BODY = 3;
const int PING = 1;
const int PONG = 0;
QString APP_VERSION = "1.0.0";
QString APP_CHANNEL = "pc";
QString APP_PACKAGE = "com.chuzi.kim";
QString ACTION_999 = "999";
QByteArray PONG_BODY= QByteArray::fromRawData(reinterpret_cast<const char*>(std::string("\x50\x4f\4E\x47").c_str()),4);

IMManager::IMManager(QObject *parent)
    : QObject{parent}
{
    netStatus(0);
    host("127.0.0.1");
    port("8080");
    wsport("34567");
    _reconnectTimer.setSingleShot(true);
    connect(&_reconnectTimer,&QTimer::timeout,this,[this](){
        wsConnect();
    });

}

Session IMManager::message2session(const Message &val){
    Session session;
    session.id = val.sessionId;
    session.content = val.content;
    session.scene = val.scene;
    session.status = val.status;
    session.timestamp = val.timestamp;
    session.type = val.type;
    return session;
}

Message IMManager::json2message(const QString& login,const QJsonObject& val){
    Message message;
    message.id = val.value("id").toString();
    message.scene = val.value("scene").toInt();
    message.type = val.value("type").toInt();
    message.subType = val.value("subType").toInt();
    message.title = val.value("title").toString();
    message.content = val.value("content").toString();
    message.sender = val.value("sender").toString();
    message.receiver = val.value("receiver").toString();
    message.extra = val.value("extra").toString();
    message.timestamp = val.value("timestamp").toDouble();
    message.readUidList = val.value("readUIds").toString();
    if(login == message.sender){
        message.sessionId = message.receiver;
    }else{
        message.sessionId = message.sender;
    }
    return message;
}

void IMManager::updateSessionByMessage(const Message &message) {
    Session session = message2session(message);
    auto sessionList = DBManager::getInstance()->findSessionListById(message.sessionId);
    if (!sessionList.isEmpty()){
        auto it = sessionList.at(0);
        if(it.id== message.sessionId){
            session.unreadCount = it.unreadCount;
            session.extra = it.extra;
            session.stayTop = it.stayTop;
        }
    }
    if (message.sender != loginAccid()) {
        if (!message.readUidList.contains(loginAccid())) {
            session.unreadCount = session.unreadCount + 1;
        }
    }
    bool success = DBManager::getInstance()->saveOrUpdateSession(session);
    if (success) {
        updateSession(session);
    }
}

void IMManager::sessionStayTop(const QString &sessionId,bool stayTop){
    QList<Session> data = DBManager::getInstance()->findSessionListById(sessionId);
    if(!data.isEmpty()){
        Session session =  data.at(0);
        session.stayTop = stayTop;
        DBManager::getInstance()->saveOrUpdateSession(session);
        updateSession(session);
    }
}

void IMManager::clearUnreadCount(const QString &sessionId){
    QList<Message> data = DBManager::getInstance()->findUnreadMessageList(sessionId, loginAccid());
    if (data.count() == 0)
        return;
    QString uuids;
    for (int i = 0; i < data.size(); ++i) {
        auto &item = const_cast<Message &>(data.at(i));
        const QString &accids = item.readUidList;
        if (accids.isEmpty()) {
            item.readUidList = loginAccid();
        } else {
            item.readUidList = accids + "," + loginAccid();
        }
        uuids.append(item.id).append(",");
    }
    uuids.chop(1);
    qx::dao::save(data);
    QList<Session> sessionList = DBManager::getInstance()->findSessionListById(sessionId);
    if(!sessionList.isEmpty()){
        Session session = sessionList.at(0);
        session.unreadCount = 0;
        DBManager::getInstance()->saveOrUpdateSession(session);
        updateSession(session);
    }
    IMCallback* callback = new IMCallback();
    connect(callback,&IMCallback::finish,this,[callback](){
        callback->deleteLater();
    });
    messageRead(uuids,callback);
}

void IMManager::addEmptySession(QString sessionId,int scene){
    QList<Session> it = DBManager::getInstance()->findSessionListById(sessionId);
    if(it.isEmpty()){
        Session it;
        it.id = sessionId;
        it.content = "{\"msg\":\"\"}";
        it.scene = scene;
        it.status = 0;
        it.timestamp = QDateTime::currentMSecsSinceEpoch();
        it.type = 0;
        bool success = DBManager::getInstance()->saveOrUpdateSession(it);
        if (success) {
            updateSession(it);
        }
    }
}

IMManager::~IMManager(){
    if(_socket!=nullptr){
        delete _socket;
        _socket = nullptr;
    }
}

void IMManager::bind(){
    com::chuzi::imsdk::server::model::proto::SentBody body;
    body.set_key("client_bind");
    body.set_timestamp(QDateTime::currentMSecsSinceEpoch());
    body.mutable_data()->insert({"token",token().toLatin1().constData()});
    body.mutable_data()->insert({"channel",APP_CHANNEL.toLatin1().constData()});
    body.mutable_data()->insert({"appVersion",APP_VERSION.toLatin1().constData()});
    body.mutable_data()->insert({"osVersion",QSysInfo::productVersion().toLatin1().constData()});
    body.mutable_data()->insert({"packageName",APP_PACKAGE.toLatin1().constData()});
    body.mutable_data()->insert({"deviceId",QSysInfo::machineUniqueId().constData()});
    body.mutable_data()->insert({"deviceName",QSysInfo::prettyProductName().toLatin1().constData()});
    body.mutable_data()->insert({"language",QLocale::system().name().toLatin1().constData()});
    sendRequest(&body);
}

void IMManager::pong(){
    QByteArray pong;
    pong.resize(PONG_BODY.length()+1);
    pong[0] = PONG;
    std::memcpy(pong.data() + 1, PONG_BODY.constData(), PONG_BODY.length());
    _socket->sendBinaryMessage(pong);
}

void IMManager::wsConnect(){
    QString wsToken = token();
    if(wsToken.isEmpty()){
        return;
    }
    DBManager::getInstance()->initDb();
    if(_socket!=nullptr){
        delete _socket;
        _socket = nullptr;
    }
    _socket = new QWebSocket();
    connect(_socket, &QWebSocket::binaryMessageReceived, this, &IMManager::onSocketMessage);
    connect(_socket, &QWebSocket::stateChanged, this,
            [=](QAbstractSocket::SocketState state) {
                qDebug()<<QMetaEnum::fromType<QAbstractSocket::SocketState>().valueToKey(state);
                if(state == QAbstractSocket::ConnectedState){
                    netStatus(3);
                    handleFailedMessage();
                    bind();
                    syncMessage();
                    Q_EMIT wsConnected();
                    _reconnectTimer.stop();
                }else if(state == QAbstractSocket::UnconnectedState){
                    netStatus(2);
                    _reconnectTimer.start(5000);
                }
            });
    connect(_socket, &QWebSocket::connected, this,
            [=]() {
            });
    QNetworkRequest request(wsUri());
    request.setRawHeader("token", wsToken.toUtf8());
    _socket->open(request);
}

void IMManager::handleFailedMessage(){
    QList<Message> data = DBManager::getInstance()->findMessageByStatus(1);
    for (int i = 0; i < data.count(); ++i) {
        auto item = data.at(i);
        item.status = 2;
        DBManager::getInstance()->saveOrUpdateMessage(item);
    }
}

QString IMManager::loginAccid(){
    return SettingsHelper::getInstance()->getAccount().toString();
}

QString IMManager::token(){
    return SettingsHelper::getInstance()->getToken().toString();
}

QList<Session> IMManager::getSessionList(){
    return DBManager::getInstance()->findSessionAll();
}

QList<Message> IMManager::getMessageListBySessionId(QString sessionId){
    return DBManager::getInstance()->findMessageListBySessionId(sessionId);
}

QList<Message> IMManager::getMessageByPage(QString sessionId,qint64 anchor,int pageSize){
    return DBManager::getInstance()->findMessageByPage(sessionId,anchor,pageSize);
}

void IMManager::userRegister(
    const QString& account,
    const QString& password,
    const QString& confirmPassword,
    const QString& name,
    const QString& mobile,
    const QString& email,
    qint64 birthday,
    const QString& avatar,
    IMCallback* callback){
    QMap<QString, QVariant> params;
    params.insert("uid",account);
    params.insert("password",password);
    params.insert("confirmPassword",confirmPassword);
    params.insert("name",name);
    params.insert("birthday",birthday);
    if(!mobile.isEmpty()){
        params.insert("mobile",mobile);
    }
    if(!email.isEmpty()){
        params.insert("email",email);
    }
    if(!avatar.isEmpty()){
        params.insert("avatar",avatar);
    }
    post("/user/register",params,callback);
}

void IMManager::userLogin(const QString& account,const QString& password,IMCallback* callback){
    QMap<QString, QVariant> params;
    params.insert("uid",account);
    params.insert("password",password);
    post("/user/login",params,callback);
}

void IMManager::userSearch(const QString& keyword,IMCallback* callback){
    QMap<QString, QVariant> params;
    params.insert("keyword",keyword);
    post("/user/searchUser",params,callback);
}

void IMManager::userInfo(const QString& account,IMCallback* callback){
    QMap<QString, QVariant> params;
    params.insert("uid",account);
    post("/user/getUserInfo",params,callback);
}

void IMManager::userProfile(IMCallback* callback){
    QMap<QString, QVariant> params;
    post("/user/profile",params,callback);
}

void IMManager::friendAdd(const QString& friendId,IMCallback* callback){
    QMap<QString, QVariant> params;
    params.insert("friendId",friendId);
    post("/friend/addFriend",params,callback);
}

void IMManager::friendRemove(const QString& friendId,IMCallback* callback){
    QMap<QString, QVariant> params;
    params.insert("friendId",friendId);
    post("/friend/removeFriend",params,callback);
}

void IMManager::friends(IMCallback* callback){
    QMap<QString, QVariant> params;
    post("/friend/getFriends",params,callback);
}

void IMManager::messageRead(const QString& ids,IMCallback* callback){
    QMap<QString, QVariant> params;
    params.insert("ids",ids);
    post("/message/messageRead",params,callback);
}

void IMManager::syncMessage(){
    IMCallback* callback = new IMCallback();
    connect(callback,&IMCallback::start,this,[](){

    });
    connect(callback,&IMCallback::success,this,[callback,this](QJsonObject result) mutable{
        if(result.contains("data")){
            QJsonArray data = result.value("data").toArray();
            auto login = loginAccid();
            QList<Message> messageList;
            QMap<QString, Message> map;
            QMap<QString, int> mapUnread;
            for (int i = 0; i < data.size(); ++i) {
                auto item = data.at(i).toObject();
                const Message &message = json2message(login,item);
                if (message.sender != login) {
                    if (!message.readUidList.contains(login)) {
                        int unread = mapUnread.value(message.sessionId) + 1;
                        mapUnread.insert(message.sessionId, unread);
                    }
                }
                map.insert(message.sessionId, message);
                messageList.append(message);
            }
            QList<Session> sessionList;
            for (const auto &item: map) {
                Session session = message2session(item);
                int unread = mapUnread.value(session.id);
                session.unreadCount = unread;
                sessionList.append(session);
            }
            qx::dao::save(messageList);
            qx::dao::save(sessionList);
            Q_EMIT messageChanged(messageList);
            Q_EMIT sessionChanged(sessionList);
            Q_EMIT syncMessageCompleted();
        }
    });
    connect(callback,&IMCallback::error,this,[callback,this](int code,QString erroString) mutable{

    });
    connect(callback,&IMCallback::finish,this,[callback](){
        callback->deleteLater();
    });
    QMap<QString, QVariant> params;
    QList<Message> data = DBManager::getInstance()->findLastMessage();
    qint64 timestamp = 0;
    if(!data.isEmpty()){
        timestamp = data.at(0).timestamp;
    }
    params.insert("timestamp",timestamp);
    post("/message/syncMessage",params,callback);
}

void IMManager::sendMessage(Message message,IMCallback* callback){
    QMap<QString, QVariant> params;
    params.insert("id",message.id);
    params.insert("receiver",message.receiver);
    params.insert("scene",message.scene);
    params.insert("type",message.type);
    params.insert("content",message.content);
    IMCallback* sendback = new IMCallback();
    connect(sendback,&IMCallback::start,this,[callback](){
        callback->start();
    });
    connect(sendback,&IMCallback::success,this,[callback,message,this](QJsonObject result) mutable{
        message.status = 0;
        sendMessageToLocal(message);
        callback->success(result);
    });
    connect(sendback,&IMCallback::error,this,[callback,message,this](int code,QString erroString) mutable{
        message.status = 2;
        sendMessageToLocal(message);
        callback->error(code,erroString);
    });
    connect(sendback,&IMCallback::finish,this,[callback,sendback](){
        sendback->deleteLater();
        callback->finish();
    });
    post("/message/send",params,sendback);
}

void IMManager::sendTextMessage(const QString& receiver,const QString& text,IMCallback* callback,int scene){
    QJsonObject object;
    object.insert("msg",text);
    auto content = QString(QJsonDocument(object).toJson(QJsonDocument::Compact));
    auto message = buildMessage(receiver,scene,0,content);
    sendMessageToLocal(message);
    sendMessage(message,callback);
}

void IMManager::resendMessage(const QString& id,IMCallback* callback){
    QList<Message> data = DBManager::getInstance()->findMessageListById(id);
    if(!data.isEmpty()){
        auto message = data.at(0);
        message.status = 1;
        message.timestamp = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
        sendMessageToLocal(message);
        sendMessage(message,callback);
    }
}

Message IMManager::buildMessage(const QString &sessionId, int scene, int type, const QString &content){
    Message message;
    message.id = QUuid::createUuid().toString().remove("{").remove("}");
    message.content = content;
    message.sender = loginAccid();
    message.receiver = sessionId;
    message.sessionId = sessionId;
    message.scene = scene;
    message.type = type;
    message.timestamp = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
    message.status = 1;
    return message;
}

void IMManager::sendMessageToLocal(Message& message){
    DBManager::getInstance()->saveOrUpdateMessage(message);
    updateMessage(message);
    updateSessionByMessage(message);
}

void IMManager::updateMessage(Message message){
    QList<Message> data;
    data.append(message);
    Q_EMIT messageChanged(data);
}

void IMManager::updateSession(Session session){
    QList<Session> data;
    data.append(session);
    Q_EMIT sessionChanged(data);
}

void IMManager::sendRequest(google::protobuf::Message* message){
    QByteArray data = QByteArray::fromStdString(message->SerializeAsString());
    QByteArray protobuf;
    protobuf.resize(data.length() + 1);
    protobuf[0] = SENT_BODY;
    std::memcpy(protobuf.data() + 1, data.constData(), data.length());
    _socket->sendBinaryMessage(protobuf);
}

void IMManager::post(const QString& path, QMap<QString, QVariant> params,IMCallback* callback){
    if(callback){
        Q_EMIT callback->start();
    }
    QNetworkRequest req(apiUri()+path);
    if(!token().isEmpty()){
        req.setRawHeader("access-token",token().toUtf8());
    }
    QHttpMultiPart* multiPart= new QHttpMultiPart(QHttpMultiPart::FormDataType);
    for (const auto& each : params.toStdMap())
    {
        const QString& key = each.first;
        const QString& value = each.second.toString();
        QString dispositionHeader = QString("form-data; name=\"%1\"").arg(key);
        QHttpPart part;
        part.setHeader(QNetworkRequest::ContentDispositionHeader, dispositionHeader);
        part.setBody(value.toUtf8());
        multiPart->append(part);
    }

    QNetworkAccessManager* netManager = new QNetworkAccessManager();
    netManager->setTransferTimeout(5000);
    auto reply =  netManager->post(req,multiPart);
    multiPart->setParent(reply);
    connect(reply,&QNetworkReply::finished,this,[reply,callback,netManager](){
        QString response = QString::fromUtf8(reply->readAll());
        QJsonObject result;
        int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        QString message = reply->errorString();
        QNetworkReply::NetworkError error = reply->error();
        bool isSuccess = false;
        if(error == QNetworkReply::NoError){
            QJsonParseError jsonError;
            QJsonDocument doucment = QJsonDocument::fromJson(response.toUtf8(), &jsonError);
            if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {
                result = doucment.object();
                int code = result.value("code").toInt();
                if(code == 200){
                    isSuccess = true;
                }else{
                    isSuccess = false;
                    message = result.value("message").toString();
                }
            }else{
                isSuccess = false;
                code = -1;
                message = "JSON解析失败";
            }
        }else{
            isSuccess = false;
        }
        if(isSuccess){
            if(callback){
                Q_EMIT callback->success(result);
            }
        }else{
            if(callback){
                Q_EMIT callback->error(code,message);
            }
        }
        reply->deleteLater();
        netManager->deleteLater();
        if(callback){
            Q_EMIT callback->finish();
        }
    });
}

void IMManager::openAutoRead(QString sessionId){
    _autoReadSessionId = sessionId;
}

QString IMManager::wsUri(){
    return "ws://" + _host + ":" + _wsport;
}

QString IMManager::apiUri(){
    return "http://" + _host + ":" + _port;
}

void IMManager::onSocketMessage(const QByteArray &message)
{
    int type = message[0];
    QByteArray body = message.mid(1);
    if(type == PING){
        qDebug()<<QString::fromStdString("ws recevie ping");
        pong();
    }else if(type == MESSAGE){
        auto login = loginAccid();
        com::chuzi::imsdk::server::model::proto::Message messageProto;
        messageProto.ParseFromArray(body.data(),body.size());
        Message message;
        message.id = QString::fromStdString(messageProto.id());
        message.scene = messageProto.scene();
        message.type = messageProto.type();
        message.subType = messageProto.subtype();
        message.title = QString::fromStdString(messageProto.title());
        message.content = QString::fromStdString(messageProto.content());
        message.sender = QString::fromStdString(messageProto.sender());
        message.receiver = QString::fromStdString(messageProto.receiver());
        message.extra = QString::fromStdString(messageProto.extra());
        message.readUidList = QString::fromStdString(messageProto.readuids());
        message.timestamp = messageProto.timestamp();
        message.status = 0;
        if(message.sender == login){
            message.sessionId = message.receiver;
        }else{
            message.sessionId = message.sender;
        }
        if(_autoReadSessionId  == message.sessionId){
            const QString &accids = message.readUidList;
            if (accids.isEmpty()) {
                message.readUidList = login;
            } else {
                if(!accids.contains(login)){
                    message.readUidList = accids + "," + loginAccid();
                }
            }
            messageRead(message.readUidList);
        }
        QList<Message> data = DBManager::getInstance()->findMessageListById(message.id);
        if(!data.isEmpty()){
            message.localExtra = data.at(0).localExtra;
        }
        bool success = DBManager::getInstance()->saveOrUpdateMessage(message);
        if (success) {
            updateMessage(message);
            updateSessionByMessage(message);
        }
        qDebug()<<QString::fromStdString("ws recevie message: ")<<QString::fromUtf8(messageProto.Utf8DebugString().c_str());
    }else if(type == REPLY_BODY){
        com::chuzi::imsdk::server::model::proto::ReplyBody replyBody;
        replyBody.ParseFromArray(body.data(),body.size());
        qDebug()<<QString::fromStdString("ws recevie replyBody: ")<<QString::fromUtf8(replyBody.Utf8DebugString().c_str());
    }
}
