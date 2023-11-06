#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>
#include <stdafx.h>

class UserModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY_AUTO(QString,id)
    Q_PROPERTY_AUTO(QString,avatar)
    Q_PROPERTY_AUTO(qint64,birthday)
    Q_PROPERTY_AUTO(QString,extension)
    Q_PROPERTY_AUTO(int,gender)
    Q_PROPERTY_AUTO(QString,mobile)
    Q_PROPERTY_AUTO(QString,email)
    Q_PROPERTY_AUTO(QString,name)
    Q_PROPERTY_AUTO(QString,signature)
    Q_PROPERTY_AUTO(QString,uid)
public:
    explicit UserModel(QObject *parent = nullptr);

signals:

};

#endif // USERMODEL_H
