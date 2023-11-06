#include "Message.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_KIM(Message)

namespace qx {
template<> void register_class(QxClass<Message> &t)
{
    t.id(&Message::id, "id");
    t.data(&Message::content, "content");
    t.data(&Message::sender, "sender");
    t.data(&Message::receiver, "receiver");
    t.data(&Message::scene, "scene");
    t.data(&Message::type, "type");
    t.data(&Message::subType, "sub_type");
    t.data(&Message::extra, "extra");
    t.data(&Message::localExtra, "local_extra");
    t.data(&Message::timestamp, "timestamp");
    t.data(&Message::status, "status");
    t.data(&Message::sessionId, "session_id");
    t.data(&Message::readUidList, "read_uid_list");
}
}

Message::Message(){

}

Message::~Message(){

}
