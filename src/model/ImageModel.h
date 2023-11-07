#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <QObject>
#include <stdafx.h>

class ImageModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY_AUTO(QString,source)
public:
    explicit ImageModel(QObject *parent = nullptr);
    QString url;
};

#endif // IMAGEMODEL_H
