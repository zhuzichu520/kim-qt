#include "SessionListModel.h"

#include <manager/IMManager.h>

SessionListModel::SessionListModel(QObject *parent) : BaseListModel(parent) {

}

SessionListModel::~SessionListModel(){

}

void SessionListModel::resetData(){
    beginResetModel();
    _datas.clear();
    QList<QSharedPointer<SessionModel>> data;
    foreach (auto item, IMManager::getInstance()->getSessionList()) {
        data.append(handleSession(item));
    }
    _datas.append(data);
    endResetModel();
}

void SessionListModel::clear(){
    beginResetModel();
    _datas.clear();
    endResetModel();
}

QSharedPointer<SessionModel> SessionListModel::handleSession(Session val){
    auto model = QSharedPointer<SessionModel>(new SessionModel(this));
    model->id(val.id);
    model->content(val.content);
    model->scene(val.scene);
    model->type(val.type);
    model->subType(val.subType);
    model->extra(val.extra);
    model->timestamp(val.timestamp);
    model->unreadCount(val.unreadCount);
    model->status(val.status);
    model->stayTop(val.stayTop);
    model->text(handleContent(val.type,val.content));
    return model;
}

QString SessionListModel::handleContent(int type,const QString& content){
    QJsonParseError parseError;
    auto jsonDocument = QJsonDocument::fromJson(content.toUtf8(),&parseError);
    if(parseError.error != QJsonParseError::NoError){
        return "[未知消息]";
    }
    auto object = jsonDocument.object();
    switch(type){
    case 0:
        return object["msg"].toString();
    case 1:
        return "[图片]";
    case 2:
        return "[文件]";
    default:
        return "[未知消息]";
    }
}
