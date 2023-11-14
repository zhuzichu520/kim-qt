import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import FluentUI 1.0
import "../model"

Window{
    id:control
    flags: Qt.FramelessWindowHint
    width: 460
    height: 320
    color: "#00000000"
    signal emojiClicked(string tag)
    onActiveFocusItemChanged: {
        if(!activeFocusItem){
            close()
        }
    }
    Page{
        padding: 0
        anchors{
            fill: parent
            margins: 10
        }
        background: FluArea{
            radius: 5
        }
        FluShadow{
            radius: 5
        }
        GridView{
            clip: true
            cellWidth: 42
            cellHeight: 40
            boundsBehavior: GridView.StopAtBounds
            anchors{
                fill: parent
                topMargin: 10
                bottomMargin: 10
                leftMargin: 12
            }
            model:EmojiListModel
            delegate: FluIconButton{
                width: 32
                height: 32
                verticalPadding: 0
                horizontalPadding: 0
                iconDelegate:Image{
                    width: 26
                    height: 26
                    source: "qrc:/res/image/emoji/"+model.file
                }
                text:model.tag.replace("[","").replace("]","")
                onClicked: {
                    control.emojiClicked(model.tag)
                }
            }
        }
    }
}
