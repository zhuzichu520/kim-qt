import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import FluentUI 1.0
import IM 1.0

FluWindow {
    id:window
    width: 480
    height: 640
    showStayTop: false
    fixSize: true
    title: "账号注册"
    modality: Qt.ApplicationModal

    component MustItem:Row{
        spacing: 8
        Text{
            text:"*"
            color: "red"
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Component.onCompleted: {
        textbox_register_account.forceActiveFocus()
    }

    FluText{
        font.pixelSize: 20
        font.weight: Font.Medium
        text:"欢迎注册KIM"
        anchors{
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 20
        }
    }

    ColumnLayout{
        anchors.centerIn: parent
        spacing: 20

        MustItem{
            FluTextBox{
                id:textbox_register_account
                Layout.preferredWidth: 240
                placeholderText: "请输入账号"
            }
        }
        MustItem{
            FluPasswordBox{
                id:textbox_register_password
                Layout.preferredWidth: 240
                placeholderText: "请输入密码"
            }
        }

        MustItem{
            FluPasswordBox{
                id:textbox_register_confirm_password
                Layout.preferredWidth: 240
                placeholderText: "请再次输入密码"
            }
        }

        MustItem{
            FluTextBox{
                id:textbox_register_name
                Layout.preferredWidth: 240
                placeholderText: "请输入姓名"
            }
        }

        FluTextBox{
            id:textbox_register_mobile
            Layout.preferredWidth: 240
            placeholderText: "请输入手机号"
            Layout.alignment: Qt.AlignRight
        }

        FluTextBox{
            id:textbox_register_email
            Layout.preferredWidth: 240
            placeholderText: "请输入邮箱"
            Layout.alignment: Qt.AlignRight
        }

        FluCalendarPicker{
            id:picker_birthday
            text:"您的出生年月"
            Layout.leftMargin: 12
        }

        Row{
            spacing: 12
            Layout.leftMargin: 12
            FluText{
                text:"选择您的头像"
                anchors.verticalCenter: parent.verticalCenter
            }
            FluClip{
                anchors.verticalCenter: parent.verticalCenter
                width: 40
                height: 40
                radius: [20,20,20,20]
                Image{
                    anchors.fill: parent
                    source: "https://zhu-zichu.gitee.io/default.png"
                }
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        showInfo("敬请期待")
                    }
                }
            }
        }

        FluFilledButton{
            text: "注册"
            Layout.preferredHeight: 34
            Layout.topMargin: 10
            Layout.fillWidth: true
            onClicked: {
                var account = textbox_register_account.text
                var password = textbox_register_password.text
                var confirmPassword = textbox_register_confirm_password.text
                var name = textbox_register_name.text
                var mobile = textbox_register_mobile.text
                var email = textbox_register_email.text
                var birthday
                if(picker_birthday.current){
                    birthday = picker_birthday.current.valueOf()
                }else{
                    birthday = 0
                }
                var avatar = "https://zhu-zichu.gitee.io/default.png"
                IMManager.userRegister(account,password,confirmPassword,name,mobile,email,birthday,avatar,callback_user_register)
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
            (result)=>{
                showSuccess("注册成功")
                onResult({account:textbox_register_account.text,password:textbox_register_password.text})
                window.close()
            }
    }

}
