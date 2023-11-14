import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import FluentUI 1.0
import IM 1.0

FluWindow {
    id:window
    width: 300
    height: 380
    showStayTop: false
    fixSize: true
    title: "KIM"

    property var registerPageRegister: registerForWindowResult("/register")
    property int pageIndex: 0

    component LoginPage:Page{
        background: Rectangle{
            color:window.backgroundColor
        }

        Connections{
            target: registerPageRegister
            function onResult(data)
            {
                textbox_login_account.text = data.account
                textbox_login_password.text = data.password
            }
        }

        Component.onCompleted: {
            textbox_login_account.forceActiveFocus()
        }

        ColumnLayout{
            anchors.centerIn: parent
            spacing: 0

            FluTextBox{
                id:textbox_login_account
                Layout.preferredWidth: 240
                placeholderText: "请输入账号"
            }

            FluPasswordBox{
                id:textbox_login_password
                Layout.topMargin: 20
                Layout.preferredWidth: 240
                placeholderText: "请输入密码"
            }

            FluFilledButton{
                text: "登录"
                Layout.topMargin: 30
                Layout.preferredWidth: 240
                Layout.preferredHeight: 34
                onClicked: {
                    var account = textbox_login_account.text
                    var password = textbox_login_password.text
                    IMManager.userLogin(account,password,callback_user_login)
                }
            }
            FluButton{
                text: "注册"
                Layout.topMargin: 10
                Layout.preferredWidth: 240
                Layout.preferredHeight: 34
                onClicked: {
                    registerPageRegister.launch()
                }
            }
        }
        FluTextButton{
            text:"设置"
            anchors{
                right: parent.right
                rightMargin: 10
                bottom: parent.bottom
                bottomMargin: 5
            }
            onClicked: {
                window.pageIndex = 1
            }
        }
    }

    component SettingPage:Page{
        background: Rectangle{
            color:window.backgroundColor
        }
        ColumnLayout{
            anchors.centerIn: parent
            spacing: 20

            FluTextBox{
                id:textbox_register_account
                Layout.preferredWidth: 240
                placeholderText: "Host"
                text:IMManager.host
                onTextChanged: {
                    IMManager.host = text
                }
            }

            FluTextBox{
                id:textbox_register_password
                Layout.preferredWidth: 240
                placeholderText: "WS Port"
                text: IMManager.wsport
                onTextChanged: {
                    IMManager.wsport = text
                }
            }

            FluTextBox{
                id:textbox_register_confirm_password
                Layout.preferredWidth: 240
                placeholderText: "Api Port"
                text: IMManager.port
                onTextChanged: {
                    IMManager.port = text
                }
            }
        }
        FluTextButton{
            text:"返回登录"
            anchors{
                right: parent.right
                rightMargin: 10
                bottom: parent.bottom
                bottomMargin: 5
            }
            onClicked: {
                window.pageIndex = 0
            }
        }
    }

    IMCallback{
        id:callback_user_login
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
                SettingsHelper.login(result.data.uid,result.token)
                //                SettingsHelper.saveToken(result.token)
                FluApp.navigate("/")
                window.close()
            }
    }

    SwipeView{
        id:swipe_view
        anchors.fill: parent
        interactive: false
        currentIndex:  window.pageIndex
        LoginPage{

        }
        SettingPage{

        }
    }

}
