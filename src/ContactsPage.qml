import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import FluentUI 1.0
import IM 1.0

Page{

    id:control
    property var currentContact
    signal refreshFriends

    Connections{
        target: IMManager
        function onWsConnected(){
            control.refreshFriends()
        }
    }

    ListModel{
        id:model_contact
    }

    IMCallback{
        id:callback_user_search
        onStart: {
            layout_contact_find_empty.visible = false
            showLoading()
        }
        onFinish: {
            hideLoading()
        }
        onError:
            (code,message)=>{
                showError(message)
            }
        onSuccess:
            (result)=>{
                console.debug(JSON.stringify(result))
                if(result.data){
                    loader_popup_user.userData = result.data
                    loader_popup_user.sourceComponent = com_popup_user
                }else{
                    layout_contact_find_empty.visible = true
                }
            }
    }

    IMCallback{
        id:callback_friends
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
                model_contact.clear()
                model_contact.append(result.data)
                console.debug(JSON.stringify(result))
            }
    }

    IMCallback{
        id:callback_friend_remove
        onStart: {
            showLoading()
        }
        onFinish: {
            hideLoading()
        }
        onError:
            (code,message)=>{
                showError(message)
            }
        onSuccess:
            (result)=>{
                control.refreshFriends()
            }
    }

    IMCallback{
        id:callback_message_send
        onStart: {
            showLoading()
        }
        onFinish: {
            hideLoading()
        }
        onError:
            (code,message)=>{
                showError(message)
            }
        onSuccess:
            (result)=>{
                console.debug(JSON.stringify(result))
            }
    }

    onRefreshFriends: {
        contact_find_page.visible = false
        IMManager.friends(callback_friends)
    }

    FluMenu{
        property string friendId
        id:menu_contact_item
        width: 100
        FluMenuItem{
            text:"删除好友"
            onClicked: {
                IMManager.friendRemove(menu_contact_item.friendId,callback_friend_remove)
            }
        }
        function showMenu(id){
            menu_contact_item.friendId = id
            menu_contact_item.popup()
        }
    }

    component ContactItem:Rectangle{
        property bool selected: control.currentContact === model
        id:control_contact
        height: 65
        width: 250
        color:{
            if(control_contact.selected){
                return FluTheme.itemCheckColor
            }
            if(mouse_area_contact.containsMouse)
                return FluTheme.itemPressColor
            return FluTheme.itemNormalColor
        }
        MouseArea{
            id:mouse_area_contact
            acceptedButtons: Qt.LeftButton|Qt.RightButton
            anchors.fill: parent
            hoverEnabled: true
            onClicked:
                (mouse)=>{
                    if(mouse.button === Qt.LeftButton){
                        control.currentContact = model
                    }else{
                        menu_contact_item.showMenu(model.uid)
                    }
                }
        }
        AvatarView{
            id:item_avatar
            width: 42
            height: 42
            userInfo: model
            anchors{
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 12
            }
        }
        FluText{
            text:model.name
            anchors{
                verticalCenter: parent.verticalCenter
                left: item_avatar.right
                leftMargin: 10
            }
        }
    }
    Rectangle{
        id:layout_contact
        width: 250
        height: parent.height
        color: Qt.rgba(230/255,230/255,230/255,1)
        Rectangle{
            id:layout_contact_top_bar
            color: Qt.rgba(247/255,247/255,247/255,1)
            width: parent.width
            height: 60
            FluTextBox{
                width: 190
                iconSource: FluentIcons.Search
                placeholderText: "搜索"
                anchors{
                    bottom: parent.bottom
                    bottomMargin: 8
                    left: parent.left
                    leftMargin: 8
                }
            }
            FluIconButton{
                width: 24
                height: 24
                iconSize: 14
                verticalPadding: 0
                horizontalPadding: 0
                iconSource: FluentIcons.Add
                anchors{
                    bottom: parent.bottom
                    bottomMargin: 10
                    right: parent.right
                    rightMargin: 14
                }
                onClicked: {
                    textbox_find_contact.clear()
                    contact_find_page.visible = true
                }
            }
        }
        ListView{
            id:list_contacts
            anchors{
                left: parent.left
                right: parent.right
                top: layout_contact_top_bar.bottom
                bottom: parent.bottom
            }
            header:Item{
                width:list_contacts.width
                height: 56
                FluButton{
                    text:"通讯录管理"
                    width: 230
                    anchors.centerIn: parent
                }
            }
            boundsBehavior: ListView.StopAtBounds
            model: model_contact
            delegate: ContactItem{}
        }
        Rectangle{
            color: Qt.rgba(214/255,214/255,214/255,1)
            height: 1
            width: parent.width
            anchors.top: layout_contact_top_bar.bottom
        }
        Page{
            id:contact_find_page
            anchors.fill: parent
            visible: false
            background: Rectangle{
                color: Qt.rgba(230/255,230/255,230/255,1)
            }

            Rectangle{
                id:layout_contact_find_top_bar
                color: Qt.rgba(247/255,247/255,247/255,1)
                width: parent.width
                height: 60
                FluTextBox{
                    id:textbox_find_contact
                    width: 190
                    iconSource: FluentIcons.Search
                    placeholderText: "账号/手机号"
                    anchors{
                        bottom: parent.bottom
                        bottomMargin: 8
                        left: parent.left
                        leftMargin: 8
                    }
                    onTextChanged: {
                        layout_contact_find_empty.visible = false
                    }
                }
                FluTextButton{
                    anchors{
                        bottom: parent.bottom
                        bottomMargin: 8
                        right: parent.right
                        rightMargin: 6
                    }
                    text:"取消"
                    onClicked: {
                        contact_find_page.visible = false
                    }
                }
            }

            Column{
                spacing: 0
                width: parent.width
                anchors{
                    top: layout_contact_find_top_bar.bottom
                }

                Rectangle{
                    id:layout_contact_find_empty
                    width: parent.width
                    height: 60
                    color: Qt.rgba(247/255,247/255,247/255,1)
                    visible: false
                    FluText{
                        color: FluTheme.fontSecondaryColor
                        text:"无法找到该用户，请检查你填写的账号是否正确"
                        wrapMode: Text.WrapAnywhere
                        horizontalAlignment: Qt.AlignHCenter
                        anchors{
                            left: parent.left
                            right: parent.right
                            leftMargin: 14
                            rightMargin: 14
                            verticalCenter: parent.verticalCenter
                        }
                    }
                }

                Rectangle{
                    width: parent.width
                    height: 60
                    color: Qt.rgba(247/255,247/255,247/255,1)
                    visible: textbox_find_contact.text !== ""
                    Rectangle{
                        anchors.fill: parent
                        color: {
                            if(mouse_contact_find.containsPress){
                                return FluTheme.itemPressColor
                            }
                            if(mouse_contact_find.containsMouse){
                                return FluTheme.itemHoverColor
                            }
                            return FluTheme.itemNormalColor
                        }
                    }
                    MouseArea{
                        id:mouse_contact_find
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            IMManager.userSearch(textbox_find_contact.text,callback_user_search)
                        }
                    }
                    RowLayout{
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width
                        spacing: 0
                        Rectangle{
                            Layout.preferredWidth: 36
                            Layout.preferredHeight: 36
                            Layout.alignment: Qt.AlignVCenter
                            Layout.leftMargin: 14
                            color: FluTheme.primaryColor
                            radius: 4
                            FluIcon{
                                iconSize: 20
                                anchors.centerIn: parent
                                iconSource: FluentIcons.Search
                                iconColor: FluColors.White
                            }
                        }
                        FluText{
                            text:"搜索: "
                            Layout.leftMargin: 10
                        }
                        FluText{
                            text:textbox_find_contact.text
                            color: FluTheme.primaryColor
                            Layout.fillWidth: true
                            elide: Text.ElideRight
                        }
                        FluIcon{
                            iconSource: FluentIcons.ChevronRight
                            iconSize: 14
                            Layout.rightMargin: 10
                        }
                    }
                }

            }


            Rectangle{
                color: Qt.rgba(214/255,214/255,214/255,1)
                height: 1
                width: parent.width
                anchors.top: layout_contact_find_top_bar.bottom
            }
        }
    }


    FluLoader{
        property var userData
        id:loader_popup_user
        sourceComponent: userData ? com_popup_user : undefined
    }

    Component{
        id:com_popup_user

        FluPopup{
            id:popup_user
            property var user: userData.userInfo
            property bool isFriend: userData.isFriend
            width: 230
            height: 190
            modal: false
            anchors.centerIn: undefined
            x:255
            y:60
            visible: true
            onVisibleChanged: {
                if(!visible){
                    loader_popup_user.sourceComponent = undefined
                }
            }
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
            contentItem: Item{

                IMCallback{
                    id:callback_friend_add
                    onStart: {
                        showLoading()
                    }
                    onFinish: {
                        hideLoading()
                    }
                    onError:
                        (code,message)=>{
                            popup_user.close()
                            showError(message)
                        }
                    onSuccess:
                        (result)=>{
                            control.refreshFriends()
                            popup_user.close()
                        }
                }

                AvatarView{
                    id:popup_user_avatar
                    width: 60
                    height: 60
                    userInfo: popup_user.user
                    anchors{
                        top: parent.top
                        left: parent.left
                        topMargin: 20
                        leftMargin: 20
                    }
                }

                Column{
                    anchors{
                        left: popup_user_avatar.right
                        top: popup_user_avatar.top
                        leftMargin: 20
                        topMargin: 4
                    }
                    FluText{
                        id:popup_user_name
                        text: {
                            if(popup_user.user){
                                return popup_user.user.name
                            }
                            return ""
                        }
                    }
                    FluText{
                        id:popup_user_uid
                        color : FluTheme.fontTertiaryColor
                        text: {
                            if(popup_user.user){
                                return "账号: " + popup_user.user.uid
                            }
                            return ""
                        }
                    }
                }

                Rectangle{
                    color: Qt.rgba(214/255,214/255,214/255,1)
                    height: 1
                    anchors{
                        top:parent.top
                        topMargin: 100
                        left: parent.left
                        right: parent.right
                        leftMargin: 14
                        rightMargin: 14
                    }
                }

                FluFilledButton{
                    text: popup_user.isFriend ? "发送聊天" : "添加好友"
                    anchors{
                        horizontalCenter: parent.horizontalCenter
                        bottom: parent.bottom
                        bottomMargin: 26
                    }
                    onClicked:{
                        if(popup_user.isFriend){
                            showInfo("待开发")
                            popup_user.close()
                        }else{
                            IMManager.friendAdd(popup_user.user.uid,callback_friend_add)
                        }
                    }
                }
            }
        }
    }


    Component{
        id:com_contact_info_panne
        Rectangle{
            id:layout_contact_info_panne
            color: Qt.rgba(245/255,245/255,245/255,1)

            Item{
                width: 360
                height: parent.height
                anchors.horizontalCenter: parent.horizontalCenter

                AvatarView{
                    id:contact_info_avatar
                    width: 60
                    height: 60
                    radius:[5,5,5,5]
                    anchors{
                        top: parent.top
                        left: parent.left
                        topMargin: 120
                    }
                    userInfo: currentContact
                }

                ColumnLayout{
                    spacing: 0
                    anchors{
                        top: contact_info_avatar.top
                        left: contact_info_avatar.right
                        leftMargin: 16
                    }

                    FluText{
                        text:currentContact.name

                    }
                    FluText{
                        text: "账号: %1".arg(currentContact.uid)
                        color: FluTheme.fontTertiaryColor
                    }
                }


                Rectangle{
                    id:contact_info_divider_1
                    color: Qt.rgba(214/255,214/255,214/255,1)
                    height: 1
                    width: parent.width
                    anchors{
                        top: contact_info_avatar.bottom
                        topMargin: 20
                    }
                }

                RowLayout{
                    anchors{
                        top: contact_info_divider_1.bottom
                        topMargin: 30
                    }

                    FluIconButton{
                        iconSource:FluentIcons.Message
                        text:"发消息"
                        iconColor: Qt.rgba(123/255,138/255,171/255,1)
                        textColor: iconColor
                        display: Button.TextUnderIcon
                        iconSize: 18
                        font.pixelSize: 12
                        onClicked: {
                            IMManager.sendTextMessage(currentContact.uid,"123456",callback_message_send)
                        }
                    }
                }
            }
        }
    }

    FluLoader{
        anchors{
            left: layout_contact.right
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }
        sourceComponent: control.currentContact ? com_contact_info_panne : undefined
    }

    Rectangle{
        width: 1
        height: layout_contact.height
        color: Qt.rgba(214/255,214/255,214/255,1)
        anchors{
            left: layout_contact.right
        }
    }


}
