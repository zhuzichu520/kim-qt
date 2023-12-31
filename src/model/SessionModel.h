#ifndef SESSIONMODEL_H
#define SESSIONMODEL_H

#include <QObject>
#include <stdafx.h>
#include <model/UserModel.h>

class SessionModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY_AUTO(QString,id)
    Q_PROPERTY_AUTO(QString,content)
    Q_PROPERTY_AUTO(int,scene)
    Q_PROPERTY_AUTO(int,type)
    Q_PROPERTY_AUTO(int,subType)
    Q_PROPERTY_AUTO(QString,extra)
    Q_PROPERTY_AUTO(qint64,timestamp)
    Q_PROPERTY_AUTO(int,unreadCount)
    Q_PROPERTY_AUTO(int,status)
    Q_PROPERTY_AUTO(bool,stayTop)

    Q_PROPERTY_AUTO(QString,text)
    Q_PROPERTY_AUTO(UserModel*,user)
    Q_PROPERTY_AUTO(QString,time)
    Q_PROPERTY_AUTO(QString,draft)

    void setModel(QSharedPointer<SessionModel> val);

public:
    explicit SessionModel(QObject *parent = nullptr);
    ~SessionModel();

};

#endif // SESSIONMODEL_H
