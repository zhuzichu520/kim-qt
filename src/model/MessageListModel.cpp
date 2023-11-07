#include "MessageListModel.h"

#include <manager/IMManager.h>
#include <provider/UserProvider.h>

MessageListModel::MessageListModel(QObject *parent)
    : BaseListModel{parent}
{
    _session = nullptr;
    connect(IMManager::getInstance(),&IMManager::receiveMessage,this,[this](Message &message){
        if(session()->id()==message.sessionId){
            auto model = handleMessage(message);
            addOrUpdateData(model);
        }
    });
}

void MessageListModel::resetData(){
    beginResetModel();
    _datas.clear();
    QList<QSharedPointer<MessageModel>> data;
    foreach (auto item, IMManager::getInstance()->getMessageListBySessionId(_session->id())) {
        data.append(handleMessage(item));
    }
    _datas.append(data);
    endResetModel();
    Q_EMIT viewToBottom();
}

QSharedPointer<MessageModel> MessageListModel::handleMessage(Message val){
    auto model = QSharedPointer<MessageModel>(new MessageModel(this));
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
    model->isSelf(val.sender==IMManager::getInstance()->loginAccid());
    model->user(UserProvider::getInstance()->of(val.sessionId));
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
        int minutes = dateTime.time().minute() / 5 * 5;
        QTime roundedTime(dateTime.time().hour(), minutes);
        return roundedTime.toString("hh:mm");
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

void MessageListModel::addOrUpdateData(QSharedPointer<MessageModel> session){
    for (int i = 0; i < _datas.size(); ++i)
    {
        auto item = _datas.at(i);
        if(item.get()->id() == session.get()->id()){
            _datas.at(i)->setModel(session);
            Q_EMIT dataChanged(this->index(i),this->index(i));
            return;
        }
    }
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _datas.append(session);
    endInsertRows();
    Q_EMIT viewToBottom();
}
