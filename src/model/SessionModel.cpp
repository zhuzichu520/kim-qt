#include "SessionModel.h"

#include <QDebug>

SessionModel::SessionModel(QObject *parent)
    : QObject{parent}
{

}

SessionModel::~SessionModel(){

}

void SessionModel::setModel(QSharedPointer<SessionModel> val){
    auto session = val.get();
    this->id(session->id());
    this->content(session->content());
    this->scene(session->scene());
    this->type(session->type());
    this->subType(session->subType());
    this->extra(session->extra());
    this->timestamp(session->timestamp());
    this->unreadCount(session->unreadCount());
    this->status(session->status());
    this->stayTop(session->stayTop());
    this->text(session->text());
}
