#include "Message.h"

QX_REGISTER_CPP_QX_KIM(Message)

namespace qx {
template<>
void register_class(QxClass<Message> &t) {
    t.id(&Message::m_id, "id");
    t.data(&Message::m_body, "body");
    t.data(&Message::m_from_accid, "from_accid");
    t.data(&Message::m_to_accid, "to_accid");
    t.data(&Message::m_scene, "scene");
    t.data(&Message::m_type, "type");
    t.data(&Message::m_ex, "ex");
    t.data(&Message::m_local_ex, "local_ex");
    t.data(&Message::m_read_accids, "read_accids");
    t.data(&Message::m_time, "time");
    t.data(&Message::m_status, "status");
    t.data(&Message::m_session_id, "session_id");
}
}

void Message::handleAttachment(){
    QJsonDocument doc = QJsonDocument::fromJson(getBody().toUtf8());
    QJsonObject obj = doc.object();
    setAttachment(obj);
}
