import QtQuick 2.15

Item {

    property var userInfo

    onUserInfoChanged: {
        if(userInfo){
            image_source.source = userInfo.avatar
        }
    }

    Image {
        id:image_source
        anchors.fill: parent
    }

}
