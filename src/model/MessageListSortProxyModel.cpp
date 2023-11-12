#include "MessageListSortProxyModel.h"

#include <model/MessageModel.h>

MessageListSortProxyModel::MessageListSortProxyModel(QSortFilterProxyModel *parent)
    : QSortFilterProxyModel {parent}
{
    _model = nullptr;
    connect(this,&MessageListSortProxyModel::modelChanged,this,[=]{
        setSourceModel(this->model());
        sort(0, Qt::AscendingOrder);
    });
}

bool MessageListSortProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const{
    return true;
}

bool MessageListSortProxyModel::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const{
    return true;
}

bool MessageListSortProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const{
    QSharedPointer<MessageModel> left = _model->_datas.at(source_left.row());
    QSharedPointer<MessageModel> right = _model->_datas.at(source_right.row());
    return left.get()->timestamp() > right.get()->timestamp();
}
