import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import FluentUI 1.0
import IM 1.0

FluWindow {
    id:window
    width: 880
    height: 580
    showStayTop: false
    title: "KIM"
    minimumWidth: 702
    minimumHeight: 500
    appBar:undefined
    property var loginUser : UserProvider.loginUser()

    Component.onCompleted: {
        IMManager.wsConnect()
    }

    Connections{
        target: IMManager
        function onWsConnected(){
            loginUser = UserProvider.loginUser()
        }
    }

    Connections{
        target: MainGlobal
        function onSwitchSessionEvent(uid){
            nav_view.startPageByItem(pane_item_session)
        }
    }

    FluObject{
        id:items_original
        FluPaneItem{
            id:pane_item_session
            count: 99
            title: "聊天"
            icon:FluentIcons.Home
            url:"qrc:/SessionPage.qml"
            onTap:{
                nav_view.push(url)
            }
        }
        FluPaneItem{
            id:pane_item_contacts
            count: 99
            title: "联系人"
            icon:FluentIcons.ContactPresence
            url:"qrc:/ContactsPage.qml"
            onTap:{
                nav_view.push(url)
            }
        }
    }

    FluObject{
        id:items_footer
        FluPaneItem{
            title:"设置"
            icon:FluentIcons.Settings
            onTapListener:function(){
                FluApp.navigate("/setting")
            }
        }
    }


    FluNavigationView{
        id:nav_view
        width: parent.width
        height: parent.height
        pageMode: FluNavigationViewType.Stack
        items: items_original
        navCompactWidth: 60
        footerItems:items_footer
        hideNavAppBar: true
        navTopMargin: 86
        displayMode:FluNavigationViewType.Compact
        logo: UserProvider.loginUser().avatar
        title: UserProvider.loginUser().name
        Component.onCompleted: {
            setCurrentIndex(0)
        }
    }

    AvatarView{
        width: 38
        height: 38
        userInfo: loginUser
        anchors{
            left: parent.left
            leftMargin: (nav_view.navCompactWidth - width) / 2
            top: parent.top
            topMargin: 36
        }
    }

    FluAppBar {
        id:app_bar_front
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        darkText: "夜间模式"
        showDark: true
        z:7
        darkClickListener:(button)=>handleDarkChanged(button)
    }

    Component{
        id:com_reveal
        CircularReveal{
            id:reveal
            target:window.contentItem
            anchors.fill: parent
            onAnimationFinished:{
                loader_reveal.sourceComponent = undefined
            }
            onImageChanged: {
                changeDark()
            }
        }
    }

    FluLoader{
        id:loader_reveal
        anchors.fill: parent
    }

    function distance(x1,y1,x2,y2){
        return Math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
    }

    function handleDarkChanged(button){
        if(!FluTheme.enableAnimation){
            changeDark()
        }else{
            loader_reveal.sourceComponent = com_reveal
            var target = window.contentItem
            var pos = button.mapToItem(target,0,0)
            var mouseX = pos.x
            var mouseY = pos.y
            var radius = Math.max(distance(mouseX,mouseY,0,0),distance(mouseX,mouseY,target.width,0),distance(mouseX,mouseY,0,target.height),distance(mouseX,mouseY,target.width,target.height))
            var reveal = loader_reveal.item
            reveal.start(reveal.width*Screen.devicePixelRatio,reveal.height*Screen.devicePixelRatio,Qt.point(mouseX,mouseY),radius)
        }
    }

    function changeDark(){
        if(FluTheme.dark){
            FluTheme.darkMode = FluThemeType.Light
        }else{
            FluTheme.darkMode = FluThemeType.Dark
        }
    }

    Window{
        flags: Qt.FramelessWindowHint
        width: 330
        height: 34
        visible: IMManager.netStatus === 2
        color: Qt.rgba(204/255,83/255,83/255,1)
        x:window.x + (window.width - width)/2
        y:Math.max(window.y - height - 5,0)
        Row{
            anchors.centerIn: parent
            Text{
                text:"网络不可用, 请检查你的网络设置"
                color: FluColors.White
                font.pixelSize: 15
            }
        }
    }

}
