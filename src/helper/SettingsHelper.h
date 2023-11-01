#ifndef SETTINGSHELPER_H
#define SETTINGSHELPER_H

#include <QtCore/qobject.h>
#include <QtQml/qqml.h>
#include <QSettings>
#include <QScopedPointer>
#include <QFileInfo>
#include <QCoreApplication>
#include <QDir>
#include "singleton.h"

class SettingsHelper : public QObject
{
    Q_OBJECT
private:
    explicit SettingsHelper(QObject* parent = nullptr);
public:
    SINGLETONG(SettingsHelper)
    ~SettingsHelper() override;
    void init(char *argv[]);
    Q_INVOKABLE void saveToken(const QVariant& token){save("token",token);}
    Q_INVOKABLE QVariant getToken(){return get("token");}
private:
    void save(const QString& key,QVariant val);
    QVariant get(const QString& key,QVariant def={});
private:
    QScopedPointer<QSettings> m_settings;
};

#endif // SETTINGSHELPER_H
