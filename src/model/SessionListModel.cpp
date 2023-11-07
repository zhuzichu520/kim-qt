#include "SessionListModel.h"

#include <manager/IMManager.h>
#include <provider/UserProvider.h>

SessionListModel::SessionListModel(QObject *parent) : BaseListModel(parent) {
    connect(IMManager::getInstance(),&IMManager::updateSessionCompleted,this,[this](Session& session){
        QSharedPointer<SessionModel> sessionModel =  handleSession(session);
        addOrUpdateData(sessionModel);
    });
}

SessionListModel::~SessionListModel(){

}

void SessionListModel::addOrUpdateData(QSharedPointer<SessionModel> session){
    for (int i = 0; i < _datas.size(); ++i)
    {
        auto item = _datas.at(i);
        if(item.get()->id() == session.get()->id()){
            _datas.at(i)->setModel(session);
            Q_EMIT dataChanged(this->index(i),this->index(i));
            sortDatas();
            return;
        }
    }
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _datas.append(session);
    endInsertRows();
    sortDatas();
}

void SessionListModel::sortDatas(){
    Q_EMIT layoutAboutToBeChanged();
    qSort(_datas.begin(),_datas.end(),[](QSharedPointer<SessionModel> left,QSharedPointer<SessionModel> right){
        if(left.get()->stayTop() && !right.get()->stayTop()){
            return true;
        }else if(!left.get()->stayTop() && right.get()->stayTop()){
            return false;
        }else{
            return left.get()->timestamp()>right.get()->timestamp();
        }
    });
    changePersistentIndex(index(0,0),index(_datas.count()-1,0));
    Q_EMIT layoutChanged(QList<QPersistentModelIndex>(),QAbstractItemModel::VerticalSortHint);
}

void SessionListModel::resetData(){
    beginResetModel();
    _datas.clear();
    QList<QSharedPointer<SessionModel>> data;
    foreach (auto item, IMManager::getInstance()->getSessionList()) {
        data.append(handleSession(item));
    }
    _datas.append(data);
    sortDatas();
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
    model->user(UserProvider::getInstance()->of(val.id));
    return model;
}

QString SessionListModel::handleContent(int type,const QString& content){
    QJsonParseError error;
    auto jsonDocument = QJsonDocument::fromJson(content.toUtf8(),&error);
    if(error.error != QJsonParseError::NoError){
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

SessionModel* SessionListModel::getSessionByUid(const QString& uid){
    for (int i = 0; i < _datas.size(); ++i)
    {
        auto item = _datas.at(i);
        if(item.get()->id() == uid){
            return item.get();
        }
    }
    return nullptr;
}
