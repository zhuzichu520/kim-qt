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

    Image{
        anchors.fill: parent
        visible: image_source.progress !==1
        source: "qrc:/res/image/avatar_default.png"
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
