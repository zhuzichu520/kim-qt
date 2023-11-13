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
    if(_inited){
        return;
    }
    auto account = SettingsHelper::getInstance()->getAccount().toString();
    auto dbName = QString(QCryptographicHash::hash(account.toUtf8(), QCryptographicHash::Md5).toHex());
    auto db=qx::QxSqlDatabase::getSingleton();
    db->setDriverName("QSQLITE");
    db->setDatabaseName(QString::fromStdString("%1/%2").arg(_dbPath,dbName));
    db->setHostName("localhost");
    db->setUserName("root");
    db->setPassword("");

    db->setFormatSqlQueryBeforeLogging(false);
    db->setDisplayTimerDetails(false);
    db->setVerifyOffsetRelation(true);
    db->setTraceSqlQuery(false);
    db->setTraceSqlBoundValues(false);
    db->setTraceSqlBoundValuesOnError(false);
    db->setTraceSqlRecord(false);

    QSqlError sqlError = qx::dao::create_table<Message>();
    if(sqlError.isValid()){
        qDebug()<<sqlError.text();
    }
    sqlError = qx::dao::create_table<Session>();
    if(sqlError.isValid()){
        qDebug()<<sqlError.text();
    }
    _inited = true;
}

bool DBManager::saveOrUpdateMessage(Message message){
    return qx::dao::save(message).type() == QSqlError::NoError;
}

bool DBManager::saveOrUpdateSession(Session session){
    return qx::dao::save(session).type() == QSqlError::NoError;
}

bool DBManager::deleteMessage(Message message){
    return qx::dao::delete_by_id(message).type() == QSqlError::NoError;
}

QList<Message> DBManager::findMessageByPage(QString sessionId,qint64 anchor,int pageSize){
    qx::QxSqlQuery query(QString("WHERE Message.session_id = '%1' and Message.timestamp < %2 order by Message.timestamp desc limit %3").arg(sessionId).arg(anchor).arg(pageSize));
    QList<Message> list;
    qx::dao::fetch_by_query(query, list);
    return list;
}

QList<Session> DBManager::findSessionListById(QString id){
    qx::QxSqlQuery query(QString("WHERE Session.id = '%1'").arg(id));
    QList<Session> list;
    qx::dao::fetch_by_query(query, list);
    return list;
}

QList<Message> DBManager::findMessageListBySessionId(QString sessionId){
    qx::QxSqlQuery query(QString("WHERE Message.session_id = '%1'").arg(sessionId));
    QList<Message> list;
    qx::dao::fetch_by_query(query, list);
    return list;
}

QList<Message> DBManager::findMessageListById(QString id){
    qx::QxSqlQuery query(QString("WHERE Message.id = '%1'").arg(id));
    QList<Message> list;
    qx::dao::fetch_by_query(query, list);
    return list;
}

QList<Message> DBManager::findLastMessage(){
    qx::QxSqlQuery query(QString("WHERE Message.timestamp = (SELECT max(Message.timestamp) from Message)"));
    QList<Message> list;
    qx::dao::fetch_by_query(query, list);
    return list;
}

QList<Message> DBManager::findUnreadMessageList(const QString &sessionId,const QString &uid){
    qx::QxSqlQuery query(QString("where session_id = '%1' and receiver = '%2'").arg(sessionId,uid));
    QList<Message> list;
    qx::dao::fetch_by_query(query, list);
    QList<Message> data;
    for (int i = 0; i < list.size(); ++i) {
        auto &item = const_cast<Message &>(list.at(i));
        if (!item.readUidList.contains(uid)) {
            data.append(item);
        }
    }
    return data;
}

QList<Message> DBManager::findMessageByStatus(int status){
    qx::QxSqlQuery query(QString("WHERE Message.status = '%1'").arg(status));
    QList<Message> list;
    qx::dao::fetch_by_query(query, list);
    return list;
}

QList<Session> DBManager::findSessionAll(){
    QList<Session> list;
    qx::dao::fetch_all(list);
    return list;
}
