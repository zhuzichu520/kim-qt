#ifndef MESSAGELISTMODEL_H
#define MESSAGELISTMODEL_H

#include <QObject>

class MessageListModel : public QObject
{
    Q_OBJECT
public:

    enum Roles {
        Id = 0,
        Content = 1,
        Sender = 2,
        Receiver = 3,
        Scene = 4,
        Type = 5,
        SubType = 6,
        Extra = 7,
        LocalExtra = 8,
        Timestamp = 9,
        Status = 10,
        SessionId = 11
    };


    explicit MessageListModel(QObject *parent = nullptr);


};

#endif // MESSAGELISTMODEL_H
