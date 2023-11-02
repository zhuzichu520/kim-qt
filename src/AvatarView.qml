import QtQuick 2.15

Item {

    property var profile

    onProfileChanged: {
        if(profile){
            image_source.source = profile.avatar
        }
    }

    Image {
        id:image_source
        anchors.fill: parent
    }

}
