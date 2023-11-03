import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import FluentUI 1.0
import IM 1.0

FluWindow {
    id:window
    width: 880
    height: 610
    showStayTop: false
    title: "KIM"
    minimumWidth: 680
    minimumHeight: 500
    appBar:undefined

    property int pageIndex: 0


    Component.onCompleted: {
        IMManager.wsConnect(SettingsHelper.getToken())
    }

    UserViewModel{
        id:user_viewmodel
    }

    IMCallback{
        id:callback_userprofile
        onStart: {
        }
        onFinish: {
        }
        onError:
            (code,message)=>{
                showError(message)
            }
        onSuccess:
            (result)=>{
                console.debug(JSON.stringify(result.data))
                user_viewmodel.profile = result.data
            }
    }

    Connections{
        target: IMManager
        function onWsConnected(){
            IMManager.userProfile(callback_userprofile)
        }
    }

    FluAppBar {
        id:app_bar_front
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        showDark: false
        z:7
    }

    ListModel{
        id:model_tab
        ListElement{
            title:"聊天"
            icon: FluentIcons.Message
        }
        ListElement{
            title:"通讯录"
            icon: FluentIcons.ContactInfo
        }
    }

    component TabButton:Rectangle{
        property int iconSource: FluentIcons.Message
        property string title: FluentIcons.Message
        property bool selected: true
        signal clicked
        id:control_tab
        width: 55
        height: 55
        color: {
            if(control_tab.selected){
                return Qt.rgba(34/255,34/255,34/255,1)
            }
            if(hover_handler_tab.hovered){
                return  Qt.rgba(94/255,94/255,94/255,1)
            }
            return Qt.rgba(0,0,0,0)
        }

        Rectangle{
            width: 2
            height: parent.height
            color: FluTheme.primaryColor
            visible: control_tab.selected
        }

        ColumnLayout{
            width: parent.width
            spacing: 6
            FluIcon{
                Layout.topMargin: 10
                Layout.preferredHeight: 20
                Layout.preferredWidth: 20
                iconSize: 20
                iconColor: Qt.rgba(190/255,190/255,190/255,1)
                iconSource: control_tab.iconSource
                Layout.alignment: Qt.AlignHCenter
            }
            FluText{
                text: control_tab.title
                color:Qt.rgba(190/255,190/255,190/255,1)
                font.pixelSize: 10
                font.bold: true
                Layout.alignment: Qt.AlignHCenter
            }
        }
        HoverHandler{
            id:hover_handler_tab
        }
        TapHandler{
            onTapped: {
                control_tab.clicked()
            }
        }

    }

    Rectangle{
        id:layout_tab
        width: 55
        height: parent.height
        color:Qt.rgba(64/255,64/255,64/255,1)
        AvatarView{
            width: 38
            height: 38
            userInfo: user_viewmodel.profile
            anchors{
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 36
            }
        }
        ColumnLayout{
            spacing: 0
            width: parent.width
            anchors{
                top: parent.top
                topMargin: 100
            }
            Repeater{
                model: model_tab
                TabButton{
                    iconSource: model.icon
                    title: model.title
                    selected: index === window.pageIndex
                    onClicked: {
                        window.pageIndex = index
                    }
                }
            }
        }

        ColumnLayout{
            spacing: 0
            width: parent.width
            anchors{
                bottom: parent.bottom
            }
            TabButton{
                iconSource: FluentIcons.GlobalNavButton
                title: "设置"
                selected: false
                onClicked: {
                    FluApp.navigate("/setting")
                }
            }
        }
    }


    StackLayout {
        currentIndex: window.pageIndex
        anchors{
            left: layout_tab.right
            top: layout_tab.top
            bottom: layout_tab.bottom
            right: parent.right
        }
        clip: true
        SessionPage{

        }

        ContactsPage{

        }
    }


}
