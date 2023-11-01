import QtQuick 2.15
import FluentUI 1.0

Item {
    id: app

    Component.onCompleted: {
        FluApp.init(app)
        FluApp.vsync = true
        FluApp.routes = {
            "/login":"qrc:/LoginWindow.qml",
            "/setting":"qrc:/SettingWindow.qml",
            "/":"qrc:/MainWindow.qml",
        }
        var token = SettingsHelper.getToken()
        if(token && token!==""){
            FluApp.initialRoute = "/"
        }else{
            FluApp.initialRoute = "/login"
        }
        FluApp.run()
    }
}
