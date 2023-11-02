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
                return FluTheme.itemCheckColor
            }
            if(mouse_area_contract.containsMouse)
                return FluTheme.itemPressColor
            return FluTheme.itemNormalColor
        }
        MouseArea{
            id:mouse_area_contract
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                control_contact.clicked()
            }
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
                    contract_find_page.visible = true
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
        Rectangle{
            color: Qt.rgba(214/255,214/255,214/255,1)
            height: 1
            width: parent.width
            anchors.top: layout_contact_top_bar.bottom
        }
        Page{
            id:contract_find_page
            anchors.fill: parent
            visible: false
            background: Rectangle{
                color: Qt.rgba(230/255,230/255,230/255,1)
            }

            Rectangle{
                id:layout_contract_find_top_bar
                color: Qt.rgba(247/255,247/255,247/255,1)
                width: parent.width
                height: 60
                FluTextBox{
                    id:textbox_find_contract
                    width: 190
                    iconSource: FluentIcons.Search
                    placeholderText: "姓名/手机号"
                    anchors{
                        bottom: parent.bottom
                        bottomMargin: 8
                        left: parent.left
                        leftMargin: 8
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
                        textbox_find_contract.clear()
                        contract_find_page.visible = false
                    }
                }
            }

            Rectangle{
                width: parent.width
                height: 60
                color: Qt.rgba(247/255,247/255,247/255,1)
                anchors{
                    top: layout_contract_find_top_bar.bottom
                }
                visible: textbox_find_contract.text !== ""
            }

            Rectangle{
                color: Qt.rgba(214/255,214/255,214/255,1)
                height: 1
                width: parent.width
                anchors.top: layout_contract_find_top_bar.bottom
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

    FluLoader{
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
