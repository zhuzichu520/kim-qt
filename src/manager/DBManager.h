#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <singleton.h>
#include <QStandardPaths>
#include <db/Message.h>
#include <db/Session.h>

class DBManager : public QObject
{
    Q_OBJECT
private:
private:
    explicit DBManager(QObject *parent = nullptr);
    ~DBManager();
public:
    SINGLETONG(DBManager)
    void initDb();
    bool saveOrUpdateMessage(Message message);
    Session findSessionById(QString id);
    bool saveOrUpdateSession(Session session);

    QList<Session> findSessionAll();

private:
    QString _dbPath = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)+"/db");

};

#endif // DBMANAGER_H
