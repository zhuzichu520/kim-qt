#ifndef BASELISTMODEL_H
#define BASELISTMODEL_H

#include <QObject>
#include <QSharedPointer>
#include <QAbstractListModel>

template <typename T>
class BaseListModel : public QAbstractListModel
{
public:
    explicit BaseListModel(QObject *parent = nullptr){};

    int rowCount(const QModelIndex &parent = QModelIndex()) const override{
        Q_UNUSED(parent);
        return _datas.count();
    }

    QVariant data(const QModelIndex &index, int role =Qt::DisplayRole) const override{
        if (index.row() < 0 || index.row() >= _datas.count())
            return {};
        switch (role) {
        case Qt::DisplayRole:
            return  QVariant::fromValue(_datas.at(index.row()).get());
        default:
            break;
        }
        return QVariant();
    }

    QHash<int, QByteArray> roleNames() const override{
        return { {Qt::DisplayRole, "display"} };
    }

    QList<QSharedPointer<T>> _datas;
};

#endif // BASELISTMODEL_H
