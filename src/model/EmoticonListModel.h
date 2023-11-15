#ifndef EMOTICONLISTMODEL_H
#define EMOTICONLISTMODEL_H

#include <QObject>
#include <helper/EmoticonHelper.h>
#include <model/BaseListModel.h>

class EmoticonListModel : public BaseListModel<Emoticon>
{
    Q_OBJECT
public:
    explicit EmoticonListModel(QObject *parent = nullptr);

    void resetData();

};

#endif // EMOTICONLISTMODEL_H
