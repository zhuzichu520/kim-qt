#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <singleton.h>
#include <QStandardPaths>

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
private:
    QString _dbPath = (QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)+"/db");

};

#endif // DBMANAGER_H
