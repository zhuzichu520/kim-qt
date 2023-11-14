import QtQuick 2.15
import FluentUI 1.0

Item {
    id: app

    Component.onCompleted: {
        FluApp.init(app)
        FluApp.vsync = true
        FluApp.routes = {
            "/login":"qrc:/res/qml/window/LoginWindow.qml",
            "/register":"qrc:/res/qml/window/RegisterWindow.qml",
            "/setting":"qrc:/res/qml/window/SettingWindow.qml",
            "/":"qrc:/res/qml/window/MainWindow.qml",
        }
        if(SettingsHelper.isLogin()){
            FluApp.initialRoute = "/"
        }else{
            FluApp.initialRoute = "/login"
        }
        FluApp.run()
    }
}
