import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import FluentUI 1.0

Page{

    id:control
    property int currentIndex : -1

    ListModel{
        id:model_session
        ListElement{
            name:"朱子楚"
            content:"哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈"
            time: "1698824141953"
        }
        ListElement{
            name:"孙悟空"
            content:"呵呵呵呵呵"
            time: "1698824141953"
        }
    }
    component SessionItem:Rectangle{
        property bool selected: false
        signal clicked
        id:control_session
        height: 65
        width: 250
        color:{
            if(control_session.selected){
                return Qt.rgba(0,0,0,0.09)
            }
            if(hover_handler_session.hovered)
                return Qt.rgba(0,0,0,0.06)
            return Qt.rgba(0,0,0,0)
        }
        Rectangle{
            id:item_avatar
            width: 42
            height: 42
            anchors{
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 12
            }
        }
        FluText{
            text:model.name
            anchors{
                top: item_avatar.top
                topMargin: 2
                left: item_avatar.right
                leftMargin: 10
            }
        }
        FluText{
            text:model.content
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
        HoverHandler{
            id:hover_handler_session
        }
        TapHandler{
            onTapped: {
                control_session.clicked()
            }
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
            }
        }
        ListView{
            anchors{
                left: parent.left
                right: parent.right
                top: layout_session_top_bar.bottom
                bottom: parent.bottom
            }
            currentIndex: control.currentIndex
            boundsBehavior: ListView.StopAtBounds
            model: model_session
            delegate: SessionItem{
                selected: control.currentIndex === index
                onClicked: {
                    control.currentIndex = index
                }
            }
        }
    }

    Component{
        id:com_message_panne
        Rectangle{
            id:layout_message_panne
            color: Qt.rgba(245/255,245/255,245/255,1)

            Item{
                id:layout_message_top_bar
                height: 60
            }

            Rectangle{
                color: Qt.rgba(214/255,214/255,214/255,1)
                height: 1
                width: parent.width
                anchors.top: layout_message_top_bar.bottom
            }


            Rectangle{
                id:rect_divider
                color: Qt.rgba(214/255,214/255,214/255,1)
                height: 1
                width: parent.width
                y:parent.height-130
                MouseArea {
                    height: 6
                    width: parent.width
                    anchors.centerIn: parent
                    drag.target: rect_divider
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

        }

    }

    Loader{
        anchors{
            left: layout_session.right
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }
        sourceComponent: control.currentIndex === -1 ? undefined : com_message_panne
    }

    Rectangle{
        width: 1
        height: layout_session.height
        color: Qt.rgba(214/255,214/255,214/255,1)
        anchors{
            left: layout_session.right
        }
    }


}
