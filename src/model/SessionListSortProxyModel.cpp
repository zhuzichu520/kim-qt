#include "SessionListSortProxyModel.h"

#include <model/SessionModel.h>

SessionListSortProxyModel::SessionListSortProxyModel(QSortFilterProxyModel *parent)
    : QSortFilterProxyModel {parent}
{
    _model = nullptr;
    connect(this,&SessionListSortProxyModel::modelChanged,this,[=]{
        setSourceModel(this->model());
        sort(0, Qt::AscendingOrder);
    });
}

bool SessionListSortProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const{
    return true;
}

bool SessionListSortProxyModel::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const{
    return true;
}

bool SessionListSortProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const{
    QSharedPointer<SessionModel> left = _model->_datas.at(source_left.row());
    QSharedPointer<SessionModel> right = _model->_datas.at(source_right.row());
    if(left.get()->stayTop() && !right.get()->stayTop()){
        return true;
    }else if(!left.get()->stayTop() && right.get()->stayTop()){
        return false;
    }else{
        return left.get()->timestamp()>right.get()->timestamp();
    }
}
