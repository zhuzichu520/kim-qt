#include "IMManager.h"

#include <QDebug>
#include <QUrl>
#include <QMetaEnum>

IMManager::IMManager(QObject *parent)
    : QObject{parent}
{
    qDebug()<<"1111111111111111111111111";
    connect(&_socket, &QWebSocket::textMessageReceived, this, &IMManager::onSocketMessage);
//    connect(&_socket,&QWebSocket::connected,this,[](){
//            qDebug()<<"-------connected--";
//    });
//    connect(&_socket,&QWebSocket::disconnected,this,[](){
//        qDebug()<<"-------disconnected--";
//    });
    connect(&_socket, &QWebSocket::stateChanged, this,
            [=](QAbstractSocket::SocketState error) {
                qDebug()<<QMetaEnum::fromType<QAbstractSocket::SocketState>().valueToKey(error);
            });

    connect(&_socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this,
            [=](QAbstractSocket::SocketError error) {
                qDebug()<<"-------------------------------------------->QAbstractSocket::SocketError";
                qDebug()<<QMetaEnum::fromType<QAbstractSocket::SocketError>().valueToKey(error);
            });
}

void IMManager::wsConnect(){
    _socket.open(wsUri());
}

QString IMManager::wsUri(){
    return "ws://" + _host + ":" + _port;
}

void  IMManager::onSocketMessage(const QString &message)
{
    qDebug()<<"-------------------------------------------->onSocketMessage";
    qDebug() << message;

}
