import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import FluentUI 1.0
import IM 1.0

Page{

    id:control
    property var currentSession : null

    IMCallback{
        id:callback_message_send
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
                console.debug(JSON.stringify(result))
            }
    }

    onCurrentSessionChanged: {
        if(currentSession){
            loader_session.sourceComponent = undefined
            loader_session.sourceComponent = com_message_panne
        }else{
            loader_session.sourceComponent = undefined
        }
    }

    Connections{
        target: IMManager
        function onWsConnected(){
            session_model.resetData()
        }
    }

    SessionListModel{
        id:session_model
    }

    component SessionItem:Rectangle{
        property bool selected: control.currentSession === display
        id:control_session
        height: 65
        width: 250
        color:{
            if(control_session.selected){
                return FluTheme.itemCheckColor
            }
            if(mouse_area_session.containsMouse)
                return FluTheme.itemPressColor
            return FluTheme.itemNormalColor
        }
        MouseArea{
            id:mouse_area_session
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                control.currentSession = display
            }
        }
        AvatarView{
            id:item_avatar
            width: 42
            height: 42
            userInfo: display.user
            anchors{
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 12
            }
        }
        FluText{
            text: display.user.name
            anchors{
                top: item_avatar.top
                topMargin: 2
                left: item_avatar.right
                leftMargin: 10
            }
        }
        FluText{
            text:display.text
            anchors{
                bottom: item_avatar.bottom
                bottomMargin: 2
                left: item_avatar.right
                leftMargin: 10
                right: parent.right
                rightMargin: 10
            }
            elide: Text.ElideRight
            color: FluColors.Grey110
            font.pixelSize: 12
        }
    }
    Rectangle{
        id:layout_session
        width: 250
        height: parent.height
        color: Qt.rgba(230/255,230/255,230/255,1)
        Rectangle{
            id:layout_session_top_bar
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
                onClicked:{
                    session_model.clear()
                }
            }
        }
        ListView{
            anchors{
                left: parent.left
                right: parent.right
                top: layout_session_top_bar.bottom
                bottom: parent.bottom
            }
            boundsBehavior: ListView.StopAtBounds
            model: session_model
            clip: true
            ScrollBar.vertical: FluScrollBar{}
            delegate: SessionItem{
            }
        }
        Rectangle{
            color: Qt.rgba(214/255,214/255,214/255,1)
            height: 1
            width: parent.width
            anchors.top: layout_session_top_bar.bottom
        }
    }

    Component{
        id:com_text_message
        Rectangle{
            width: Math.min(item_message_content.implicitWidth,listviewMessage.width/2+30)
            height: Math.max(item_message_content.implicitHeight,36)
            radius: 4
            color: modelData.isSelf ? Qt.rgba(149/255,231/255,105/255,1)  : Qt.rgba(255/255,255/255,255/255,1)
            FluCopyableText{
                id:item_message_content
                text:modelData.content
                width: parent.width
                topPadding: 8
                leftPadding: 8
                bottomPadding: 8
                rightPadding: 8
                wrapMode: Text.WrapAnywhere
                anchors.centerIn: parent
                readOnly: true
            }
        }
    }

    Component{
        id:com_message_panne
        Rectangle{
            id:layout_message_panne
            color: Qt.rgba(245/255,245/255,245/255,1)

            MessageListModel{
                id:message_model
                session:currentSession
                onViewToBottom:{
                    listview_message.positionViewAtEnd()
                    listview_message.positionViewAtEnd()
                }
                onViewToPosition:
                    (positon)=>{
                        listview_message.positionViewAtIndex(pos,ListView.Beginning)
                    }
            }

            Item{
                id:layout_message_top_bar
                height: 60
            }

            Rectangle{
                id:rect_divider_top
                color: Qt.rgba(214/255,214/255,214/255,1)
                height: 1
                width: parent.width
                anchors.top: layout_message_top_bar.bottom
            }

            ListView{
                id:listview_message
                boundsBehavior: ListView.StopAtBounds
                clip: true
                model: message_model
                ScrollBar.vertical: FluScrollBar {}
                anchors{
                    top: rect_divider_top.bottom
                    left: parent.left
                    right: parent.right
                    bottom: rect_divider_bottom.top
                }
                reuseItems: true
                Component.onCompleted: {
                    message_model.resetData()
                }
                delegate: Column{
                    id:item_message_control
                    Item{
                        width: 1
                        height: 10
                    }
                    Rectangle{
                        width: item_message_time.width+8
                        height: item_message_time.height+8
                        radius: 3
                        color: Qt.rgba(218/255,218/255,218/255,1)
                        anchors.horizontalCenter: parent.horizontalCenter
                        Text {
                            id:item_message_time
                            text: "21:11"
                            color: Qt.rgba(255/255,255/255,255/255,1)
                            anchors.centerIn: parent
                        }
                    }
                    Item{
                        width: 1
                        height: 10
                    }
                    Row{
                        width: listview_message.width
                        layoutDirection: display.isSelf ? Qt.RightToLeft : Qt.LeftToRight
                        Item{
                            width: 30
                            height: 1
                        }
                        AvatarView{
                            width: 36
                            height: 36
                            userInfo: display.user
                        }
                        Item{
                            width: 10
                            height: 1
                        }
                        FluLoader{
                            property var modelData: display
                            property var listviewMessage: listview_message
                            sourceComponent: com_text_message
                        }
                    }
                    Item{
                        width: 1
                        height: 10
                    }
                }
            }


            Rectangle{
                id:rect_divider_bottom
                color: Qt.rgba(214/255,214/255,214/255,1)
                height: 1
                width: parent.width
                y:parent.height-150
                onYChanged: {
                    listview_message.positionViewAtEnd()
                }
                MouseArea {
                    height: 6
                    width: parent.width
                    anchors.centerIn: parent
                    drag.target: rect_divider_bottom
                    drag.axis: Drag.YAxis
                    drag.minimumY: 80
                    cursorShape: Qt.SizeVerCursor
                    drag.maximumY: layout_message_panne.height-130
                    onReleased: {
                        FluTools.restoreOverrideCursor()
                    }
                    onCanceled: {
                        FluTools.restoreOverrideCursor()
                    }
                    onPressed: {
                        FluTools.setOverrideCursor(Qt.SizeVerCursor)
                    }
                }
            }

            Flickable{
                id:flickable_message_input
                anchors{
                    top: rect_divider_bottom.bottom
                    topMargin: 36
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                    bottomMargin: 40
                }
                clip: true
                ScrollBar.vertical: FluScrollBar{}
                boundsBehavior: Flickable.StopAtBounds
                contentHeight: textbox_message_input.height
                FluMultilineTextBox{
                    id:textbox_message_input
                    padding: 0
                    leftPadding: 12
                    rightPadding: 12
                    width: parent.width
                    height: Math.max(flickable_message_input.height,textbox_message_input.contentHeight)
                    background: Item{}
                }
            }

            RowLayout{
                anchors{
                    top: rect_divider_bottom.bottom
                    topMargin: 5
                    left: parent.left
                    leftMargin: 8
                }

                FluIconButton{
                    verticalPadding: 0
                    horizontalPadding: 0
                    iconSize: 18
                    Layout.preferredWidth: 24
                    Layout.preferredHeight: 24
                    iconSource: FluentIcons.Emoji2
                }
            }

            FluFilledButton{
                text:"发送"
                width: 80
                anchors{
                    bottom: parent.bottom
                    right: parent.right
                    rightMargin: 20
                    bottomMargin: 5
                }
                onClicked:{
                    var text =  textbox_message_input.text
                    IMManager.sendTextMessage(currentSession.id,text,callback_message_send)
                    //                    model_message.append({isIsent:true,content:textbox_message_input.text})
                    //                    listview_message.positionViewAtEnd()
                    //                    textbox_message_input.clear()
                }
            }
        }
    }

    FluLoader{
        id:loader_session
        anchors{
            left: layout_session.right
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }
    }

    Rectangle{
        width: 1
        height: layout_session.height
        color: Qt.rgba(214/255,214/255,214/255,1)
        anchors{
            left: layout_session.right
        }
    }

    function switchSession(uid){
        control.currentSession = session_model.getSessionByUid(uid)
    }

}
