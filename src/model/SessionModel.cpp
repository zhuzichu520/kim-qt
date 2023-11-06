#include "SessionModel.h"

#include <QDebug>

SessionModel::SessionModel(QObject *parent)
    : QObject{parent}
{

}

SessionModel::~SessionModel(){
    qDebug()<<"---------SessionModel 析构了--------->";
}
