#include "Session.h"

QX_REGISTER_CPP_QX_KIM(Session)

namespace qx {
template<>
void register_class(QxClass<Session> &t) {
    t.id(&Session::id, "id");
    t.data(&Session::content, "content");
    t.data(&Session::scene, "scene");
    t.data(&Session::type, "type");
    t.data(&Session::subType, "sub_type");
    t.data(&Session::extra, "extra");
    t.data(&Session::timestamp, "timestamp");
    t.data(&Session::unreadCount, "unread_count");
    t.data(&Session::status, "status");
    t.data(&Session::draft, "draft");
    t.data(&Session::stayTop, "stay_top");
}
}

Session::Session(){

}

Session::~Session(){

}
