import QtQuick 2.15
import FluentUI 1.0

Item {
    id: app

    Component.onCompleted: {
        FluApp.init(app)
        FluApp.routes = {
            "/login":"qrc:/LoginWindow.qml",
            "/":"qrc:/MainWindow.qml",
        }
        FluApp.initialRoute = "/login"
        FluApp.run()
    }
}
