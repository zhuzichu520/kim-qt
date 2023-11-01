import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import FluentUI 1.0

Page{

    id:control
    property int currentIndex : -1

    ListModel{
        id:model_contact
        ListElement{
            name:"朱子楚"
        }
        ListElement{
            name:"孙悟空"
        }
    }
    component ContactItem:Rectangle{
        property bool selected: false
        signal clicked
        id:control_contact
        height: 65
        width: 250
        color:{
            if(control_contact.selected){
                return Qt.rgba(0,0,0,0.09)
            }
            if(hover_handler_contact.hovered)
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
                verticalCenter: parent.verticalCenter
                left: item_avatar.right
                leftMargin: 10
            }
        }
        HoverHandler{
            id:hover_handler_contact
        }
        TapHandler{
            onTapped: {
                control_contact.clicked()
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
            }
        }
        ListView{
            id:list_contracts
            anchors{
                left: parent.left
                right: parent.right
                top: layout_contact_top_bar.bottom
                bottom: parent.bottom
            }
            header:Item{
                width:list_contracts.width
                height: 56
                FluButton{
                    text:"通讯录管理"
                    width: 230
                    anchors.centerIn: parent
                }
            }
            boundsBehavior: ListView.StopAtBounds
            model: model_contact
            delegate: ContactItem{
                selected: control.currentIndex === index
                onClicked: {
                    control.currentIndex = index
                }
            }
        }
    }

    Component{
        id:com_contact_info_panne
        Rectangle{
            id:layout_contact_info_panne
            color: Qt.rgba(245/255,245/255,245/255,1)


        }
    }

    Loader{
        anchors{
            left: layout_contact.right
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }
        sourceComponent: control.currentIndex === -1 ? undefined : com_contact_info_panne
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
