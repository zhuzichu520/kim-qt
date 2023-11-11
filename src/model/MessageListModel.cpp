#include "MessageListModel.h"

#include <manager/IMManager.h>
#include <provider/UserProvider.h>

MessageListModel::MessageListModel(QObject *parent)
    : BaseListModel{parent}
{
    _session = nullptr;
    connect(IMManager::getInstance(),&IMManager::messageChanged,this,[this](QList<Message> data){
        for (int i = 0; i <= data.count()-1; ++i) {
            auto message = data.at(i);
            if(session()->id()==message.sessionId){
                auto model = handleMessage(message);
                addOrUpdateData(model);
            }
        }
    });
}

void MessageListModel::loadData(){
    qint64 lastTimestamp = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
    if(!_anchor.isNull()){
        lastTimestamp = _anchor->timestamp();
    }
    QList<QSharedPointer<MessageModel>> data;
    auto list = IMManager::getInstance()->getMessageByPage(_session->id(),lastTimestamp,30);
    if(list.empty()){
        return;
    }
    foreach (auto item, list) {
        data.append(handleMessage(item));
    }
    beginInsertRows(QModelIndex(), 0, data.count()-1);
    data.append(_datas);
    _datas = data;
    endInsertRows();
    Q_EMIT viewToBottom();
    _anchor = data.last();
}

QSharedPointer<MessageModel> MessageListModel::handleMessage(Message val){
    auto model = QSharedPointer<MessageModel>(new MessageModel(this));
    auto loginAccid = IMManager::getInstance()->loginAccid();
    model->id(val.id);
    model->content(val.content);
    model->sender(val.sender);
    model->receiver(val.receiver);
    model->scene(val.scene);
    model->type(val.type);
    model->subType(val.subType);
    model->extra(val.extra);
    model->localExtra(val.localExtra);
    model->timestamp(val.timestamp);
    model->status(val.status);
    model->sessionId(val.sessionId);
    model->readUidList(val.readUidList);
    model->isSelf(val.sender==loginAccid);
    model->user(model->isSelf() ? UserProvider::getInstance()->of(loginAccid) : UserProvider::getInstance()->of(val.sessionId));
    model->body(QJsonDocument::fromJson(val.content.toUtf8()).object());
    model->time(formatMessageTime(val.timestamp));
    return model;
}

QString MessageListModel::formatMessageTime(qint64 timestamp){
    QDateTime dateTime;
    dateTime.setMSecsSinceEpoch(timestamp);
    QDateTime currentTime = QDateTime::currentDateTime();
    qint64 days = dateTime.daysTo(currentTime);
    if (days == 0) {
        return dateTime.toString("hh:mm");
    }  else if(days ==1){
        return dateTime.toString("昨天　hh:mm");
    } {
        if (dateTime.date().year() == currentTime.date().year())
        {
            return dateTime.toString("M月dd日　hh:mm");
        } else
        {
            return dateTime.toString("yyyy年M月dd日　hh:mm");
        }
    }
}

void MessageListModel::addOrUpdateData(QSharedPointer<MessageModel> message){
    for (int i = 0; i < _datas.size(); ++i)
    {
        auto item = _datas.at(i);
        if(item.get()->id() == message.get()->id()){
            _datas.at(i)->setModel(message);
            Q_EMIT dataChanged(this->index(i),this->index(i));
            return;
        }
    }
    beginInsertRows(QModelIndex(), 0, 0);
    _datas.append(message);
    endInsertRows();
    Q_EMIT viewToBottom();
}
