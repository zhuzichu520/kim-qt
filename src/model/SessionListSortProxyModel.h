#ifndef SESSIONLISTSORTPROXYMODEL_H
#define SESSIONLISTSORTPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include <model/SessionListModel.h>
#include <stdafx.h>

class SessionListSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY_AUTO(SessionListModel*,model)
public:
    explicit SessionListSortProxyModel(QSortFilterProxyModel *parent = nullptr);

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const override;
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
};

#endif // SESSIONLISTSORTPROXYMODEL_H
