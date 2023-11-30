#ifndef MAINEVENT_H
#define MAINEVENT_H

#include <QtCore/qobject.h>
#include <QtQml/qqml.h>
#include <QSettings>
#include <QScopedPointer>
#include <QFileInfo>
#include <QCoreApplication>
#include <QDir>
#include <singleton.h>

class MainEvent : public QObject
{
    Q_OBJECT
private:
    explicit MainEvent(QObject* parent = nullptr);
public:
    SINGLETONG(MainEvent)
    ~MainEvent() override;
    Q_SIGNAL void switchSessionEvent(QString uid);
};

#endif // MAINEVENT_H
