#include "MessageModel.h"

MessageModel::MessageModel(QObject *parent)
    : QObject{parent}
{

}

void MessageModel::setModel(QSharedPointer<MessageModel> val){
    auto message = val.get();
    this->id(message->id());
    this->content(message->content());
    this->sender(message->sender());
    this->receiver(message->receiver());
    this->scene(message->scene());
    this->type(message->type());
    this->subType(message->subType());
    this->extra(message->extra());
    this->localExtra(message->localExtra());
    this->timestamp(message->timestamp());
    this->status(message->status());
    this->sessionId(message->sessionId());
    this->readUidList(message->readUidList());

    this->isSelf(message->isSelf());
    this->user(message->user());
    this->body(message->body());
    this->time(message->time());
}
