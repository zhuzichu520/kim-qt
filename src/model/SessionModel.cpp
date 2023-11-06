#include "SessionModel.h"

#include <QDebug>

SessionModel::SessionModel(QObject *parent)
    : QObject{parent}
{

}

SessionModel::~SessionModel(){
    qDebug()<<"123123123";
}
