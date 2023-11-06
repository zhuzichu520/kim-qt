#include "ContactListModel.h"

#include <manager/IMManager.h>
#include <QJsonArray>

ContactListModel::ContactListModel(QObject *parent)
    : BaseListModel{parent}
{

}

ContactListModel::~ContactListModel(){

}

QSharedPointer<UserModel> ContactListModel::handleFriend(QJsonObject val){
    QSharedPointer<UserModel> userModel = QSharedPointer<UserModel>(new UserModel());
    userModel->id(val.value("id").toString());
    userModel->uid(val.value("uid").toString());
    userModel->name(val.value("name").toString());
    userModel->avatar(val.value("avatar").toString());
    userModel->signature(val.value("signature").toString());
    userModel->email(val.value("email").toString());
    userModel->mobile(val.value("mobile").toString());
    userModel->birthday(val.value("birthday").toDouble());
    userModel->gender(val.value("gender").toInt());
    userModel->extension(val.value("extension").toString());
    return userModel;
}

void ContactListModel::resetData(){
    IMCallback* callback = new IMCallback(this);
    connect(callback,&IMCallback::finish,this,[callback](){callback->deleteLater();});
    connect(callback,&IMCallback::success,this,[callback,this](QJsonObject result){
        beginResetModel();
        _datas.clear();
        if(result.contains("data")){
            QJsonArray arr = result.value("data").toArray();
            QList<QSharedPointer<UserModel>> data;
            foreach (auto item, arr) {
                data.append(handleFriend(item.toObject()));
            }
            _datas.append(data);
        }
        endResetModel();
    });
    IMManager::getInstance()->friends(callback);
}

void ContactListModel::clear(){
    beginResetModel();
    _datas.clear();
    endResetModel();
}
