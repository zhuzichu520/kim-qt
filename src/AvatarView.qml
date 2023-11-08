import QtQuick 2.15
import FluentUI 1.0

FluClip {

    property var userInfo
    radius:[0,0,0,0]

    onUserInfoChanged: {
        if(userInfo){
            image_source.source = Qt.binding(function(){
                return userInfo.avatar
            })
        }
    }

    Rectangle{
        color: FluTheme.itemPressColor
        anchors.fill: parent
    }

    Image {
        id:image_source
        anchors.fill: parent
        mipmap: true
        cache: true
        sourceSize: Qt.size(width*2,height*2)
    }

}
