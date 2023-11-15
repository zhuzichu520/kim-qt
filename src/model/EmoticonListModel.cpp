#include "EmoticonListModel.h"

EmoticonListModel::EmoticonListModel(QObject *parent)
    : BaseListModel{parent}
{
    resetData();
}

void  EmoticonListModel::resetData(){
    beginResetModel();
    _datas = EmoticonHelper::getInstance()->_datas;
    endResetModel();
}
