#ifndef USERPROVIDER_H
#define USERPROVIDER_H

#include <QObject>
#include <model/UserModel.h>
#include <stdafx.h>
#include <singleton.h>
#include <QSharedPointer>

class UserProvider : public QObject
{
    Q_OBJECT
public:
    SINGLETONG(UserProvider);
    explicit UserProvider(QObject *parent = nullptr);
    ~UserProvider();
    Q_INVOKABLE UserModel* of(const QString& uid);
    Q_INVOKABLE UserModel* loginUser();
private:
    QList<QSharedPointer<UserModel>> _datas;
};

#endif // USERPROVIDER_H
