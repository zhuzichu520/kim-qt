#ifndef MESSAGELISTMODEL_H
#define MESSAGELISTMODEL_H

#include <QObject>

class MessageListModel : public QObject
{
    Q_OBJECT
public:
    explicit MessageListModel(QObject *parent = nullptr);
};

#endif // MESSAGELISTMODEL_H
