#include "CacheNetworkAccessManagerFactory.h"

#include <QNetworkAccessManager>
#include <QNetworkDiskCache>
#include <QStandardPaths>
#include <QDir>

QNetworkAccessManager *CacheNetworkAccessManagerFactory::create(QObject *parent)
{
    QNetworkAccessManager *nam = new QNetworkAccessManager(parent);
    QNetworkDiskCache* diskCache = new QNetworkDiskCache(nam);
    QString cachePath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)+"/imageCache";
    QDir cacheDir(cachePath);
    if(!cacheDir.exists()){
        cacheDir.mkpath(cacheDir.absolutePath());
    }
    diskCache->setCacheDirectory(cachePath);
    diskCache->setMaximumCacheSize(1024 * 1024 * 1024);
    nam->setCache(diskCache);
    return nam;
}
