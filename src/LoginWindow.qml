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

    property int pageIndex: 0

    component LoginPage:Page{
        background: Rectangle{
            color:window.backgroundColor
        }
        ColumnLayout{
            anchors.centerIn: parent
            spacing: 20

            FluTextBox{
                id:textbox_login_account
                text:"zhuzichu"
                placeholderText: "请输入账号"
            }

            FluPasswordBox{
                id:textbox_login_password
                text:"123456"
                placeholderText: "请输入密码"
            }

            FluFilledButton{
                text: "登录"
                Layout.topMargin: 10
                Layout.preferredWidth: 240
                onClicked: {
                    var account = textbox_login_account.text
                    var password = textbox_login_password.text
                    if(account.length<4 || account.length>30){
                        showError("用户名只能在4~30位之间")
                        return
                    }
                    if(password.length<4 || password.length>30){
                        showError("密码只能在4~30位之间")
                        return
                    }
                    IMManager.userLogin(account,password,callback_user_login)
                }
            }
        }
        FluTextButton{
            text:"注册"
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

    component RegisterPage:Page{
        background: Rectangle{
            color:window.backgroundColor
        }
        ColumnLayout{
            anchors.centerIn: parent
            spacing: 20

            FluTextBox{
                id:textbox_register_account
                placeholderText: "请输入账号"
            }

            FluPasswordBox{
                id:textbox_register_password
                placeholderText: "请输入密码"
            }

            FluPasswordBox{
                id:textbox_register_repassword
                placeholderText: "请再次输入密码"
            }

            FluFilledButton{
                text: "注册"
                Layout.topMargin: 10
                Layout.preferredWidth: 240
                onClicked: {
                    var account = textbox_register_account.text
                    var password = textbox_register_password.text
                    var repassword = textbox_register_repassword.text
                    if(account.length<4 || account.length>30){
                        showError("用户名只能在4~30位之间")
                        return
                    }
                    if(password.length<4 || password.length>30 || repassword.length<4 || repassword.length>30){
                        showError("密码只能在4~30位之间")
                        return
                    }
                    if(password !== repassword){
                        showError("两次输入密码不一致")
                        return
                    }
                    IMManager.userRegister(account,password,callback_user_register)
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
        id:callback_user_register
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
            (reslut)=>{
                showSuccess("注册成功")
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
            (reslut)=>{
                console.debug(JSON.stringify(reslut))
                SettingsHelper.saveToken(reslut.token)
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
        RegisterPage{

        }
    }

}
