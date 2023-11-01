import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import FluentUI 1.0
import IM 1.0

FluWindow {
    id:window
    width: 560
    height: 480
    showStayTop: false
    fixSize: true
    title: "设置"

    FluArea{
        width: 400
        height: 200
        anchors{
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 50
        }
    }

    FluFilledButton{
        text:"退出登录"
        anchors{
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 20
        }
        onClicked: {
            dialog_logout.open()
        }
    }

    FluContentDialog{
        id:dialog_logout
        title:"友情提示"
        message:"退出登录后将无法收到新消息，确定退出登录？"
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.PositiveButton
        negativeText: "取消"
        positiveText:"确定"
        onPositiveClicked:{
            showLoading()
            SettingsHelper.saveToken("")
            delay_restart.restart()
        }
    }

    Timer{
        id:delay_restart
        interval: 300
        onTriggered: {
            FluApp.exit(931)
        }
    }

}
