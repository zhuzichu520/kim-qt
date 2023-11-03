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
#include "proto/SentBody.pb.h"
#include "proto/Message.pb.h"
#include "proto/ReplyBody.pb.h"

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

}

IMManager::~IMManager(){
    if(_socket!=nullptr){
        delete _socket;
        _socket = nullptr;
    }
}

void IMManager::bind(const QString& token){
    _token = token;
    com::chuzi::imsdk::server::model::proto::SentBody body;
    body.set_key("client_bind");
    body.set_timestamp(QDateTime::currentMSecsSinceEpoch());
    body.mutable_data()->insert({"token",token.toStdString()});
    body.mutable_data()->insert({"channel",APP_CHANNEL.toStdString()});
    body.mutable_data()->insert({"appVersion",APP_VERSION.toStdString()});
    body.mutable_data()->insert({"osVersion",QSysInfo::productVersion().toStdString()});
    body.mutable_data()->insert({"packageName",APP_PACKAGE.toStdString()});
    body.mutable_data()->insert({"deviceId",QSysInfo::machineUniqueId().toStdString()});
    body.mutable_data()->insert({"deviceName",QSysInfo::prettyProductName().toStdString()});
    body.mutable_data()->insert({"language",QLocale::system().name().toStdString()});
    sendRequest(&body);
}

void IMManager::pong(){
    QByteArray pong;
    pong.resize(PONG_BODY.length()+1);
    pong[0] = PONG;
    std::memcpy(pong.data() + 1, PONG_BODY.constData(), PONG_BODY.length());
    _socket->sendBinaryMessage(pong);
}

void IMManager::wsConnect(const QString& token){
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
                    bind(token);
                    Q_EMIT wsConnected();
                }
            });
    connect(_socket, &QWebSocket::connected, this,
            [=]() {
            });
    connect(_socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this,
            [=](QAbstractSocket::SocketError error) {
                qDebug()<<QMetaEnum::fromType<QAbstractSocket::SocketError>().valueToKey(error);
            });
    QNetworkRequest request(wsUri());
    request.setRawHeader("token", token.toUtf8());
    _socket->open(request);
}

void IMManager::userRegister(const QString& account,const QString& password,const QString& confirmPassword,IMCallback* callback){
    QMap<QString, QVariant> params;
    params.insert("uid",account);
    params.insert("password",password);
    params.insert("confirmPassword",confirmPassword);
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

void IMManager::userProfile(IMCallback* callback){
    QMap<QString, QVariant> params;
    post("/user/profile",params,callback);
}

void IMManager::friendAdd(const QString& friendId,IMCallback* callback){
    QMap<QString, QVariant> params;
    params.insert("friendId",friendId);
    post("/friend/addFriend",params,callback);
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
    QThreadPool::globalInstance()->start([=](){
        if(callback){
            Q_EMIT callback->start();
        }
        QNetworkRequest req(apiUri()+path);
        if(!_token.isEmpty()){
            req.setRawHeader("access-token",_token.toUtf8());
        }
        QHttpMultiPart multiPart(QHttpMultiPart::FormDataType);
        for (const auto& each : params.toStdMap())
        {
            const QString& key = each.first;
            const QString& value = each.second.toString();
            QString dispositionHeader = QString("form-data; name=\"%1\"").arg(key);
            QHttpPart part;
            part.setHeader(QNetworkRequest::ContentDispositionHeader, dispositionHeader);
            part.setBody(value.toUtf8());
            multiPart.append(part);
        }
        QNetworkAccessManager manager;
        QNetworkReply* reply = manager.post(req,&multiPart);
        QEventLoop loop;
        connect(&manager,&QNetworkAccessManager::finished,&manager,[&loop](QNetworkReply *reply){loop.quit();});
        connect(qApp,&QCoreApplication::aboutToQuit,&manager, [&loop,reply](){reply->abort(),loop.quit();});
        loop.exec();
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
        reply = nullptr;
        if(callback){
            Q_EMIT callback->finish();
        }
    });

}

QString IMManager::wsUri(){
    return "ws://" + _host + ":" + _wsport;
}

QString IMManager::apiUri(){
    return "http://" + _host + ":" + _apiport;
}

void  IMManager::onSocketMessage(const QByteArray &message)
{
    int type = message[0];
    QByteArray body = message.mid(1);
    if(type == PING){
        qDebug()<<QString::fromStdString("ws recevie ping");
        pong();
    }else if(type == MESSAGE){
        com::chuzi::imsdk::server::model::proto::Message message;
        message.ParseFromArray(body.data(),body.size());
        qDebug()<<QString::fromStdString("ws recevie message: ")<<QString::fromUtf8(message.Utf8DebugString().c_str());
    }else if(type == REPLY_BODY){
        com::chuzi::imsdk::server::model::proto::ReplyBody replyBody;
        replyBody.ParseFromArray(body.data(),body.size());
        qDebug()<<QString::fromStdString("ws recevie replyBody: ")<<QString::fromUtf8(replyBody.Utf8DebugString().c_str());
    }
}
