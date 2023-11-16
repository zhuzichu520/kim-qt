import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Shapes 1.15
import FluentUI 1.0
import IM 1.0
import "../component"
import "../global"

FluPage{

    id:control
    launchMode: FluPageType.SingleInstance
    property var currentSession : null
    property bool isCtrlEnterForNewline: true

    Connections{
        target: MainGlobal
        function onSwitchSessionEvent(uid){
            switchSession(uid)
        }
    }

    component CusMenuItem:FluIconButton{
        display: Button.TextOnly
        focus: false
        padding: 0
        height: 36
    }


    FluMenu{
        id:menu_item_message_text
        width: 120
        focus: false
        CusMenuItem{
            text: "复制"
            onClicked: {

            }
        }
    }

    FluContentDialog{
        id:dialog_delete_session
        property var onClickListener
        title:"友情提示"
        message:"删除聊天后，将同时删除聊天记录"
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
        negativeText: "取消"
        positiveText:"确定"
        onPositiveClicked:{
            if(dialog_delete_session.onClickListener){
                dialog_delete_session.onClickListener()
            }
        }
        function showDialog(listener){
            dialog_delete_session.onClickListener = listener
            dialog_delete_session.open()
        }
    }


    FluMenu{
        property var display
        id:menu_item_session
        width: 120
        CusMenuItem{
            property alias session: menu_item_session.display
            text: session && session.stayTop ? "取消置顶" : "置顶"
            onClicked: {
                session_model.stayTopItem(session.id,!session.stayTop)
                menu_item_session.close()
            }
        }
        CusMenuItem{
            text: "删除聊天"
            onClicked: {
                dialog_delete_session.showDialog(function(){
                    session_model.deleteItem(menu_item_session.display.id)
                })
                menu_item_session.close()
            }
        }
        function showMenu(display){
            menu_item_session.display = display
            popup()
        }
    }

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
            IMManager.clearUnreadCount(currentSession.id)
            IMManager.openAutoRead(currentSession.id)
        }else{
            loader_session.sourceComponent = undefined
            IMManager.openAutoRead("")
        }
    }

    Connections{
        target: IMManager
        function onWsConnected(){
            session_model.resetData()
        }
    }

    SessionListSortProxyModel{
        id:session_sort_model
        model:session_model
    }

    SessionListModel{
        id:session_model
    }

    Component{
        id:com_message_status_loading
        FluProgressRing{
            width: 20
            height: 20
            strokeWidth:4
        }
    }

    Component{
        id:com_message_status_error
        FluIcon{
            width: 20
            height: 20
            iconSource: FluentIcons.InfoSolid
            iconColor: {
                if(FluTheme.dark){
                    return Qt.rgba(255/255,153/255,164/255,1)
                }else{
                    return Qt.rgba(196/255,43/255,28/255,1)
                }
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    IMManager.resendMessage(modelData.id,callback_message_send)
                }
            }
        }
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
        Shape {
            width: 14
            height: 14
            anchors{
                right: parent.right
                top: parent.top
            }
            visible: display.stayTop
            ShapePath {
                fillColor: FluTheme.primaryColor
                strokeWidth: 0
                strokeColor: "#00000000"
                startX: 14; startY: 14
                PathLine { x: 14; y: 0 }
                PathLine { x: 0; y: 0 }
                PathLine { x: 14; y: 14 }
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
            id:item_session_name
            text: display.user.name
            maximumLineCount: 1
            elide: Text.ElideRight
            anchors{
                top: item_avatar.top
                topMargin: 2
                left: item_avatar.right
                leftMargin: 10
                right: item_session_time.left
                rightMargin: 10
            }
        }
        FluText{
            id:item_session_time
            text: display.time
            anchors{
                verticalCenter: item_session_name.verticalCenter
                right: parent.right
                rightMargin: 10
            }
            color:FluTheme.fontTertiaryColor
        }


        Row{
            id:item_layout_text
            spacing: 0
            anchors{
                bottom: item_avatar.bottom
                left: item_avatar.right
                leftMargin: 10
                right: item_session_unreadcount.left
                rightMargin: 10
            }
            clip: true
            height: 16
            FluText{
                id:item_session_text
                color:FluTheme.fontTertiaryColor
                width: Math.min(implicitWidth,control_session.width-100)
                font.pixelSize: 12
                wrapMode: Text.NoWrap
                textFormat: Text.RichText
                verticalAlignment: Qt.AlignBottom
                text:EmoticonHelper.toEmoticonString(display.text,14)
            }
            Text{
                text:"..."
                color:FluTheme.fontTertiaryColor
                visible: item_session_text.implicitWidth>control_session.width-100
                font.pixelSize: 12
            }
        }

        Rectangle{
            id:item_session_unreadcount
            width: visible ? 18 : 0
            height: 18
            radius: 10
            visible: display.unreadCount !== 0
            color:Qt.rgba(255/255,77/255,79/255,1)
            anchors{
                verticalCenter:item_layout_text.verticalCenter
                right: parent.right
                rightMargin: 10
            }
            Text{
                text: Math.min(display.unreadCount,99)
                font.pixelSize: 10
                color: FluColors.White
                anchors.centerIn: parent
            }
        }
        MouseArea{
            id:mouse_area_session
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            anchors.fill: parent
            hoverEnabled: true
            onClicked:
                (event)=>{
                    if(event.button === Qt.LeftButton){
                        control.currentSession = display
                    }else{
                        menu_item_session.showMenu(display)
                    }
                }
        }
    }
    Item{
        id:layout_session
        width: 250
        height: parent.height
        Item{
            id:layout_session_top_bar
            width: parent.width
            height: 60
            FluTextBox{
                width: 200
                iconSource: FluentIcons.Search
                placeholderText: "搜索"
                anchors{
                    bottom: parent.bottom
                    bottomMargin: 8
                    left: parent.left
                    leftMargin: 10
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
                    rightMargin: 8
                }
                onClicked:{
                    showInfo("还在努力开发中...")
                }
            }
        }
        ListView{
            id:list_session
            anchors{
                left: parent.left
                right: parent.right
                top: layout_session_top_bar.bottom
                bottom: parent.bottom
            }
            boundsBehavior: ListView.StopAtBounds
            model: session_sort_model
            clip: true
            ScrollBar.vertical: FluScrollBar{}
            delegate: SessionItem{
            }
        }
        FluDivider{
            anchors.top: layout_session_top_bar.bottom
        }
    }

    Component{
        id:com_text_message
        Rectangle{
            width: item_message_content.contentWidth + 18
            height: item_message_content.contentHeight + 18
            radius: 4
            color: {
                if(modelData.isSelf){
                    return Qt.rgba(149/255,231/255,105/255,1)
                }
                return FluTheme.dark ? Qt.rgba(38/255,44/255,54/255,1) : Qt.rgba(253/255,253/255,253/255,1)
            }
            border.width: modelData.isSelf ? 0 : 1
            border.color: FluTheme.dark ? Window.active ? Qt.rgba(55/255,55/255,55/255,1):Qt.rgba(45/255,45/255,45/255,1) : Qt.rgba(226/255,229/255,234/255,1)
            FluText{
                id:item_message_content
                text:EmoticonHelper.toEmoticonString(modelData.body.msg)
                color: {
                    if(modelData.isSelf){
                        return FluColors.Black
                    }
                    return FluTheme.dark ?Qt.rgba(233/255,233/255,233/255,1) : FluColors.Black
                }
                textFormat: Text.RichText
                width: Math.min(implicitWidth,viewMessage.width/2+36)
                height: implicitHeight
                wrapMode: Text.WrapAnywhere
                x: 9
                y: 9
            }
        }
    }

    Component{
        id:com_message_panne
        Item{
            id:layout_message_panne

            MessageListModel{
                id:message_model
                session:currentSession
                onViewToBottom:{
                    listview_message.positionViewAtBeginning()
                }
                onViewToPosition:
                    (positon)=>{

                    }
                onLoadCompleted: {
                    rect_divider_bottom.y = Qt.binding(function(){
                        return layout_message_panne.height-150
                    })
                }
            }

            MessageListSortProxyModel{
                id:message_sort_model
                model:message_model
            }

            Item{
                id:layout_message_top_bar
                height: 60

                FluText{
                    text: currentSession.user.name
                    anchors{
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        leftMargin: 20
                    }
                    font.pixelSize: 18
                }

            }

            FluDivider{
                id:rect_divider_top
                height: 1
                width: parent.width
                orientation: Qt.Horizontal
                anchors.top: layout_message_top_bar.bottom
            }

            ListView{
                id:listview_message
                boundsBehavior: ListView.StopAtBounds
                clip: true
                verticalLayoutDirection: ListView.BottomToTop
                model: message_sort_model
                anchors{
                    top: rect_divider_top.bottom
                    left: parent.left
                    right: parent.right
                }
                height:rect_divider_bottom.y - rect_divider_top.y
                Binding on height {
                    when: rect_divider_bottom.y - rect_divider_top.y > listview_message.contentHeight
                    value: listview_message.contentHeight
                }
                cacheBuffer: 500
                footer: Item{
                    height: visible ? 30 : 0
                    width: listview_message.width
                    visible: message_model.loadStatus === 0
                    RowLayout{
                        anchors.centerIn: parent
                        FluText{
                            text: "正在加载"
                            Layout.alignment: Qt.AlignVCenter
                        }
                        FluProgressRing{
                            Layout.preferredWidth: 20
                            Layout.preferredHeight: 20
                            Layout.alignment: Qt.AlignVCenter
                            strokeWidth:4
                        }
                    }
                }
                onContentYChanged: {
                    if(contentY == originY && contentY!=0){
                        message_model.loadData()
                    }
                }
                ScrollBar.vertical: FluScrollBar {}
                Component.onCompleted: {
                    message_model.loadData()
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
                        color: FluTheme.dark ? Qt.rgba(255,255,255,0.1) : Qt.rgba(0,0,0,0.1)
                        anchors.horizontalCenter: parent.horizontalCenter
                        visible: {
                            if(index === listview_message.count-1){
                                return true
                            }
                            return checkTimestampDiff(message_model.data(message_model.index(Math.min(index+1,listview_message.count-1),0),0).timestamp,display.timestamp)
                        }
                        FluText {
                            id: item_message_time
                            text: display.time
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
                            property var viewMessage: listview_message
                            sourceComponent: com_text_message
                        }
                        Item{
                            width: 5
                            height: 1
                        }
                        FluLoader{
                            property var modelData: display
                            property var viewMessage: listview_message
                            anchors.verticalCenter: parent.verticalCenter
                            sourceComponent: {
                                if(display.status === 1){
                                    return com_message_status_loading
                                }
                                if(display.status === 2){
                                    return com_message_status_error
                                }
                                return undefined
                            }
                        }
                    }
                    Item{
                        width: 1
                        height: 10
                    }
                }
            }


            FluDivider{
                id:rect_divider_bottom
                height: 1
                orientation: Qt.Horizontal
                onYChanged: {
                    listview_message.positionViewAtBeginning()
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

            TextDocumentHelper{
                id:text_doc_helper
                document: textbox_message_input.textDocument
                cursorPosition: textbox_message_input.cursorPosition
                selectionStart: textbox_message_input.selectionStart
                selectionEnd: textbox_message_input.selectionEnd
                emoticonSize: 24
                onInsertTextChanged:
                    (text)=>{
                        textbox_message_input.insert(textbox_message_input.cursorPosition,EmoticonHelper.toEmoticonString(text))
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
                flickableDirection: Flickable.VerticalFlick
                ScrollBar.vertical: FluScrollBar{}
                boundsBehavior: Flickable.StopAtBounds
                TextArea.flickable : FluMultilineTextBox{
                    id:textbox_message_input
                    padding: 0
                    leftPadding: 12
                    rightPadding: 12
                    width: parent.width
                    textFormat: Text.RichText
                    background: Item{}
                    onTextChanged: {
                        if (length > 1024) {
                            remove(1024, length)
                            return
                        }
                    }
                    Keys.onEnterPressed: (event)=> {event.accepted = false}
                    Keys.onReturnPressed:(event)=> {event.accepted = false}
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
                    id:btn_emoji
                    verticalPadding: 0
                    horizontalPadding: 0
                    iconSize: 18
                    Layout.preferredWidth: 26
                    Layout.preferredHeight: 26
                    iconSource: FluentIcons.Emoji2
                    onClicked: {
                        var pos = mapToGlobal(0,0)
                        emoji_panel.x = pos.x - (emoji_panel.width-btn_emoji.width) / 2
                        emoji_panel.y = Math.max(pos.y - emoji_panel.height,0)
                        emoji_panel.show()
                    }
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
                    var text =  text_doc_helper.rawText()
                    if(text === ""){
                        showError("不能发送空白信息")
                        return
                    }
                    IMManager.sendTextMessage(currentSession.id,text,callback_message_send)
                    textbox_message_input.clear()
                }
            }

            FluText{
                text:"%1/%2".arg(textbox_message_input.length).arg(1024)
                anchors{
                    left: parent.left
                    bottom: parent.bottom
                    bottomMargin: 5
                    leftMargin: 14
                }
                color:FluTheme.fontTertiaryColor
            }

            EmojiPanel{
                id:emoji_panel
                onEmojiClicked:
                    (tag)=>{
                        textbox_message_input.insert(textbox_message_input.cursorPosition,EmoticonHelper.toEmoticonString(tag))
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

    FluDivider{
        width: 1
        orientation: Qt.Vertical
        anchors{
            top: parent.top
            bottom: parent.bottom
            left: layout_session.right
        }
    }

    function checkTimestampDiff(timestamp1, timestamp2) {
        const time1 = timestamp1;
        const time2 = timestamp2;
        const diff = Math.abs(time1 - time2);
        const diffMinutes = diff / 60000;
        if (diffMinutes <= 5) {
            return false;
        } else {
            return true;
        }
    }

    function switchSession(uid){
        control.currentSession = session_model.getSessionByUid(uid)
    }

}
