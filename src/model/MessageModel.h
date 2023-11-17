#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QObject>
#include <stdafx.h>
#include <QSharedPointer>
#include <model/UserModel.h>
#include <QJsonObject>

class MessageModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY_AUTO(QString,id)
    Q_PROPERTY_AUTO(QString,content)
    Q_PROPERTY_AUTO(QString,sender)
    Q_PROPERTY_AUTO(QString,receiver)
    Q_PROPERTY_AUTO(int,scene)
    Q_PROPERTY_AUTO(int,type)
    Q_PROPERTY_AUTO(int,subType)
    Q_PROPERTY_AUTO(QString,extra)
    Q_PROPERTY_AUTO(QString,localExtra)
    Q_PROPERTY_AUTO(qint64,timestamp)
    Q_PROPERTY_AUTO(int,status)
    Q_PROPERTY_AUTO(QString,sessionId)
    Q_PROPERTY_AUTO(QString,readUidList)

    Q_PROPERTY_AUTO(bool,isSelf)
    Q_PROPERTY_AUTO(UserModel*,user)
    Q_PROPERTY_AUTO(QJsonObject,body)
    Q_PROPERTY_AUTO(QString,text)
    Q_PROPERTY_AUTO(QString,time)
public:
    explicit MessageModel(QObject *parent = nullptr);
    void setModel(QSharedPointer<MessageModel> val);
};

#endif // MESSAGEMODEL_H
