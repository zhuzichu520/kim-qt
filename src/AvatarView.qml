import QtQuick 2.15
import FluentUI 1.0

FluClip {

    property var userInfo
    radius:[0,0,0,0]

    onUserInfoChanged: {
        if(userInfo){
            image_source.source = Qt.binding(function(){
                if(userInfo === null){
                    return ""
                }
                return userInfo.avatar
            })
        }
    }

    Rectangle{
        color: FluColors.Grey50
        anchors.fill: parent
    }

    Image {
        id:image_source
        anchors.fill: parent
        mipmap: true
        cache: true
        visible: image_source.status === Image.Ready
        sourceSize: Qt.size(width*2,height*2)
    }

}
