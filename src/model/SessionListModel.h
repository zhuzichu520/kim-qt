#ifndef SESSIONLISTMODEL_H
#define SESSIONLISTMODEL_H

#include <memory>
#include <QObject>
#include <QAbstractListModel>
#include <model/SessionModel.h>
#include <model/BaseListModel.h>
#include <db/Session.h>

class SessionListModel : public BaseListModel<SessionModel>
{
    Q_OBJECT
public:
    explicit SessionListModel(QObject *parent = nullptr);
    ~SessionListModel();
    Q_INVOKABLE void resetData();
    Q_INVOKABLE void clear();
    Q_INVOKABLE SessionModel* getSessionByUid(const QString& uid);
private:
    QSharedPointer<SessionModel> handleSession(Session val);
    QString handleContent(int type,const QString& content);
    void addOrUpdateData(QSharedPointer<SessionModel> session);
    QString formatSessionime(qint64 timestamp);
};

#endif // SESSIONLISTMODEL_H
