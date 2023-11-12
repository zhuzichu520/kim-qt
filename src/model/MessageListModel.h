#ifndef MESSAGELISTMODEL_H
#define MESSAGELISTMODEL_H

#include <QObject>
#include <model/BaseListModel.h>
#include <model/MessageModel.h>
#include <model/SessionModel.h>
#include <db/Message.h>
#include <stdafx.h>

class MessageListModel : public BaseListModel<MessageModel>
{
    Q_OBJECT
    Q_PROPERTY_AUTO(SessionModel*,session)
    Q_PROPERTY_AUTO(int,loadStatus)
public:
    explicit MessageListModel(QObject *parent = nullptr);
    Q_SIGNAL void viewToBottom();
    Q_SIGNAL void viewToPosition(int position);
    Q_INVOKABLE void loadData();
    Q_INVOKABLE void deleteMessage(int index);
private:
    QSharedPointer<MessageModel> handleMessage(Message val);
    void addOrUpdateData(QSharedPointer<MessageModel> message);
    QString formatMessageTime(qint64 timestamp);
private:
    QSharedPointer<MessageModel> _anchor;
};

#endif // MESSAGELISTMODEL_H
