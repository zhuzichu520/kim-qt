#ifndef CACHENETWORKACCESSMANAGERFACTORY_H
#define CACHENETWORKACCESSMANAGERFACTORY_H

#include <QObject>
#include <QQmlNetworkAccessManagerFactory>

class CacheNetworkAccessManagerFactory : public QQmlNetworkAccessManagerFactory
{
public:
    virtual QNetworkAccessManager *create(QObject *parent);
};

#endif // CACHENETWORKACCESSMANAGERFACTORY_H
