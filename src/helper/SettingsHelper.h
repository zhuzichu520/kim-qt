#ifndef SETTINGSHELPER_H
#define SETTINGSHELPER_H

#include <QtCore/qobject.h>
#include <QtQml/qqml.h>
#include <QSettings>
#include <QScopedPointer>
#include <QFileInfo>
#include <QCoreApplication>
#include <QDir>
#include <singleton.h>

class SettingsHelper : public QObject
{
    Q_OBJECT
private:
    explicit SettingsHelper(QObject* parent = nullptr);
public:
    SINGLETONG(SettingsHelper)
    ~SettingsHelper() override;
    void init(char *argv[]);
    void saveToken(const QVariant& token){save("token",token);}
    Q_INVOKABLE QVariant getToken(){return get("token");}

    void saveAccount(const QVariant& account){save("account",account);}
    Q_INVOKABLE QVariant getAccount(){return get("account");}

    Q_INVOKABLE void login(const QString& account,const QString& token){
        saveAccount(account);
        saveToken(token);
    }
    Q_INVOKABLE void logout(){
        saveAccount("");
        saveToken("");
    }
    Q_INVOKABLE bool isLogin(){
        return !getAccount().toString().isEmpty();
    }

private:
    void save(const QString& key,QVariant val);
    QVariant get(const QString& key,QVariant def={});
private:
    QScopedPointer<QSettings> m_settings;
};

#endif // SETTINGSHELPER_H
