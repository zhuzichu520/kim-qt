#include "UserProvider.h"

#include <manager/IMManager.h>

UserProvider::UserProvider(QObject *parent)
    : QObject{parent}
{

}

UserProvider::~UserProvider(){

}

UserModel* UserProvider::loginUser(){
    return of(IMManager::getInstance()->loginAccid());
}

UserModel* UserProvider::of(const QString& uid){
    for (int i = 0; i < _datas.size(); ++i)
    {
        auto item = _datas.at(i);
        if(!item.isNull() && item.get()->uid() == uid){
            return item.get();
        }
    }
    QSharedPointer<UserModel> userModel = QSharedPointer<UserModel>(new UserModel(this));
    _datas.append(userModel);
    IMCallback *callback = new IMCallback();
    connect(callback,&IMCallback::finish,this,[callback]{ callback->deleteLater(); });
    connect(callback,&IMCallback::success,this,[callback,userModel](QJsonObject result){
        auto user = result.value("data").toObject();
        userModel->id(user.value("id").toString());
        userModel->uid(user.value("uid").toString());
        userModel->name(user.value("name").toString());
        userModel->avatar(user.value("avatar").toString());
        userModel->signature(user.value("signature").toString());
        userModel->email(user.value("email").toString());
        userModel->mobile(user.value("mobile").toString());
        userModel->birthday(user.value("birthday").toDouble());
        userModel->gender(user.value("gender").toInt());
        userModel->extension(user.value("extension").toString());
    });
    IMManager::getInstance()->userInfo(uid,callback);
    return userModel.get();
}
