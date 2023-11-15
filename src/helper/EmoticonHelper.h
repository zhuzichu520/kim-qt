#ifndef EMOTICONHELPER_H
#define EMOTICONHELPER_H

#include <QObject>
#include <singleton.h>
#include <stdafx.h>
#include <QRegularExpression>
#include <QSharedPointer>

class Emoticon : public QObject
{
    Q_OBJECT
    Q_PROPERTY_AUTO(QString,file);
    Q_PROPERTY_AUTO(QString,name);
    Q_PROPERTY_AUTO(QString,tag);
public:
    explicit Emoticon(QObject *parent = nullptr);
    Emoticon(QString file,QString name,QString tag,QObject *parent = nullptr);

};

class EmoticonHelper : public QObject
{
    Q_OBJECT
public:
    SINGLETONG(EmoticonHelper)
    explicit EmoticonHelper(QObject *parent = nullptr);

    QList<QSharedPointer<Emoticon>> _datas;
    QString getFileByTag(const QString& tag);
    QString getTagByFile(const QString& file);
    Q_INVOKABLE QString toEmoticonString(QString text,int size = 20);
public:
    QRegularExpression  _tagRegular;
    QString _prefix = "qrc:/res/image/emoji/";
};

#endif // EMOTICONHELPER_H
