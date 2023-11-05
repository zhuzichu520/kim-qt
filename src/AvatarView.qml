import QtQuick 2.15
import FluentUI 1.0

FluClip {

    property var userInfo
    radius:[0,0,0,0]

    onUserInfoChanged: {
        if(userInfo){
            image_source.source = userInfo.avatar
        }
    }

    Image {
        id:image_source
        anchors.fill: parent
        mipmap: true
    }

}
