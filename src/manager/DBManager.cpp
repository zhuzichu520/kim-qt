#include "DBManager.h"
#include <QDir>
#include <db/precompiled.h>
#include <helper/SettingsHelper.h>
#include <db/Message.h>
#include <db/Session.h>
#include <QCryptographicHash>
#include <QSqlError>

DBManager::DBManager(QObject *parent)
    : QObject{parent}
{
    QDir dbDir(_dbPath);
    if(!dbDir.exists()){
        dbDir.mkpath(dbDir.absolutePath());
    }
}

DBManager::~DBManager(){

}

void DBManager::initDb(){
    auto account = SettingsHelper::getInstance()->getAccount().toString();
    auto dbName = QString(QCryptographicHash::hash(account.toUtf8(), QCryptographicHash::Md5).toHex());
    //    qx::QxSqlDatabase * pDatabaseSettings = qx::QxSqlDatabase::getSingleton();
    //    pDatabaseSettings->setTraceSqlQuery(false);
    auto db=qx::QxSqlDatabase::getSingleton();
    db->setDriverName("QSQLITE");
    db->setDatabaseName(QString::fromStdString("%1/%2").arg(_dbPath,dbName));
    db->setHostName("localhost");
    db->setUserName("root");
    db->setPassword("");

    qx::QxSqlDatabase::getSingleton()->setVerifyOffsetRelation(true);
    QSqlError daoError = qx::dao::create_table<Message>();
    daoError = qx::dao::create_table<Session>();
}

bool DBManager::saveOrUpdateMessage(Message message){
    return qx::dao::save(message).type() == QSqlError::NoError;
}

bool DBManager::saveOrUpdateSession(Session session){
    return qx::dao::save(session).type() == QSqlError::NoError;
}

Session DBManager::getSessionById(QString id){
    Session session;
    session.id = id;
    qx::dao::fetch_by_id<Session>(session);
    return session;
}
