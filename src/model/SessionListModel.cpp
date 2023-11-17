#include "SessionListModel.h"

#include <manager/IMManager.h>
#include <provider/UserProvider.h>
#include <helper/EmoticonHelper.h>

SessionListModel::SessionListModel(QObject *parent) : BaseListModel(parent) {
    connect(IMManager::getInstance(),&IMManager::sessionChanged,this,[this](QList<Session> data){
        for (int i = 0; i <= data.count()-1; ++i) {
            auto session = data.at(i);
            QSharedPointer<SessionModel> sessionModel =  handleSession(session);
            addOrUpdateData(sessionModel);
        }
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
            Q_EMIT dataChanged(this->index(i,0),this->index(i,0));
            return;
        }
    }
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _datas.append(session);
    endInsertRows();
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
    model->draft(val.draft);
    model->user(UserProvider::getInstance()->of(val.id));
    model->time(formatSessionime(val.timestamp));
    if(!val.draft.isEmpty()){
        model->text(handleDraft(val.draft));
    }else{
        model->text(handleContent(val.type,val.content));
    }
    return model;
}

QString SessionListModel::formatSessionime(qint64 timestamp){
    QDateTime dateTime;
    dateTime.setMSecsSinceEpoch(timestamp);
    QDateTime currentTime = QDateTime::currentDateTime();
    qint64 days = dateTime.daysTo(currentTime);
    if (days == 0) {
        return dateTime.toString("hh:mm");
    }  else if(days ==1){
        return dateTime.toString("昨天");
    } {
        return dateTime.toString("yy/M/dd");
    }
}

void SessionListModel::stayTopItem(const QString& id,bool stayTop){
    IMManager::getInstance()->sessionStayTop(id,stayTop);
}

void SessionListModel::deleteItem(const QString& id){
    int index = getIndexById(id);
    if(index!=-1){
        beginRemoveRows(QModelIndex(),index,index);
        _datas.removeAt(index);
        endRemoveRows();
    }
}

int SessionListModel::getIndexById(const QString& id){
    int index = -1;
    for (int i = 0; i < _datas.size(); ++i)
    {
        auto item = _datas.at(i);
        if(item.get()->id() == id){
            index = i;
            break;
        }
    }
    return index;
}

QString SessionListModel::handleDraft(const QString& draft){
    return "<font color=\"#c42b1c\">[草稿]</font>"+draft;
}

QString SessionListModel::handleContent(int type,const QString& content){
    QJsonParseError error;
    auto jsonDocument = QJsonDocument::fromJson(content.toUtf8(),&error);
    if(error.error != QJsonParseError::NoError){
        return "[未知消息]";
    }
    auto object = jsonDocument.object();
    switch(type){
    case 0:{
        auto msg = object["msg"].toString();
        if(msg.length()>50){
            msg = msg.mid(0,50);
        }
        return msg;
    }
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

SessionListSortProxyModel::SessionListSortProxyModel(QSortFilterProxyModel *parent)
    : QSortFilterProxyModel {parent}
{
    _model = nullptr;
    connect(this,&SessionListSortProxyModel::modelChanged,this,[=]{
        setSourceModel(this->model());
        sort(0, Qt::AscendingOrder);
    });
}

bool SessionListSortProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const{
    return true;
}

bool SessionListSortProxyModel::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const{
    return true;
}

bool SessionListSortProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const{
    QSharedPointer<SessionModel> left = _model->_datas.at(source_left.row());
    QSharedPointer<SessionModel> right = _model->_datas.at(source_right.row());
    if(left.get()->stayTop() && !right.get()->stayTop()){
        return true;
    }else if(!left.get()->stayTop() && right.get()->stayTop()){
        return false;
    }else{
        return left.get()->timestamp()>right.get()->timestamp();
    }
}
