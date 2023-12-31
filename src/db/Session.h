#ifndef SESSION_H
#define SESSION_H

#include <db/precompiled.h>

class QX_KIM_DLL_EXPORT Session {
public:
    Session();
    ~Session();
    QString m_id;
    QString id;
    QString content;
    int scene = 0;
    int type = 0;
    int subType = 0;
    QString extra;
    qint64 timestamp =0;
    int unreadCount = 0;
    int status = 0;
    QString draft;
    bool stayTop = false;
};

QX_REGISTER_PRIMARY_KEY(Session, QString)
QX_REGISTER_HPP_QX_KIM (Session, qx::trait::no_base_class_defined, 0)

#endif // SESSION_H
