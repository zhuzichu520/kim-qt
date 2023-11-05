#ifndef MESSAGE_H
#define MESSAGE_H

#include <db/precompiled.h>

class QX_KIM_DLL_EXPORT Message {
public:

    Message();
    ~Message();

public:
    QString id;
    QString content;
    QString sender;
    QString receiver;
    int scene = 0;
    int type = 0;
    int subType = 0;
    QString extra;
    QString localExtra;
    qint64 timestamp = 0;
    int status = 0;
    QString sessionId;
    QString readUidList;
};

QX_REGISTER_PRIMARY_KEY(Message, QString)
QX_REGISTER_HPP_QX_KIM (Message, qx::trait::no_base_class_defined, 0)

#endif // MESSAGE_H
