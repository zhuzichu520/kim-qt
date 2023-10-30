import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import FluentUI 1.0

FluWindow {
    width: 300
    height: 380
    showStayTop: false
    fixSize: true
    title: "KIM"

    ColumnLayout{
        anchors.centerIn: parent
        spacing: 20

        FluTextBox{
            placeholderText: "请输入账号"
            text: "18229858146"
        }

        FluPasswordBox{
            placeholderText: "请输入密码"
            text:"123456"
        }

        FluFilledButton{
            text: "登录"
            Layout.topMargin: 10
            Layout.preferredWidth: 240
            onClicked: {
                FluApp.navigate("/")
                close()
            }
        }
    }

}
