import QtQuick 2.15
import FluentUI 1.0

Item {
    id: app

    Component.onCompleted: {
        FluApp.init(app)
        FluApp.vsync = true
        FluApp.routes = {
            "/login":"qrc:/LoginWindow.qml",
            "/register":"qrc:/RegisterWindow.qml",
            "/setting":"qrc:/SettingWindow.qml",
            "/":"qrc:/MainWindow.qml",
        }
        if(SettingsHelper.isLogin()){
            FluApp.initialRoute = "/"
        }else{
            FluApp.initialRoute = "/login"
        }
        FluApp.run()
    }
}
