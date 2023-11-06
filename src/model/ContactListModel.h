#ifndef CONTACTLISTMODEL_H
#define CONTACTLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <model/BaseListModel.h>
#include <model/UserModel.h>

class ContactListModel :  public BaseListModel<UserModel>
{
    Q_OBJECT
public:

    explicit ContactListModel(QObject *parent = nullptr);
      ~ContactListModel();

    Q_INVOKABLE void resetData();
    Q_INVOKABLE void clear();
private:
    QSharedPointer<UserModel> handleFriend(QJsonObject val);

};

#endif // CONTACTLISTMODEL_H
