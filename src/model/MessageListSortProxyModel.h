#ifndef MESSAGELISTSORTPROXYMODEL_H
#define MESSAGELISTSORTPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include <model/MessageListModel.h>
#include <stdafx.h>

class MessageListSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY_AUTO(MessageListModel*,model)
public:
    explicit MessageListSortProxyModel(QSortFilterProxyModel *parent = nullptr);

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const override;
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
};

#endif // MESSAGELISTSORTPROXYMODEL_H
