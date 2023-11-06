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



};

#endif // CONTACTLISTMODEL_H
