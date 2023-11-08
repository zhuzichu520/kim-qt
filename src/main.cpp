#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QQuickWindow>
#include <QNetworkProxy>
#include <QProcess>
#include <manager/IMManager.h>
#include <manager/DBManager.h>
#include <model/MessageListModel.h>
#include <model/SessionListModel.h>
#include <model/ContactListModel.h>
#include <model/SessionModel.h>
#include <provider/UserProvider.h>
#include <model/UserModel.h>
#include <model/ImageModel.h>
#include <helper/SettingsHelper.h>
#include <component/CircularReveal.h>

int main(int argc, char *argv[])
{
    QNetworkProxy::setApplicationProxy(QNetworkProxy::NoProxy);
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
#endif
    qputenv("QT_QUICK_CONTROLS_STYLE","Basic");
    QGuiApplication::setOrganizationName("ZhuZiChu");
    QGuiApplication::setOrganizationDomain("https://zhuzichu520.github.io");
    QGuiApplication::setApplicationName("KIM");
    SettingsHelper::getInstance()->init(argv);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("IMManager",IMManager::getInstance());
    engine.rootContext()->setContextProperty("DBManager",DBManager::getInstance());
    engine.rootContext()->setContextProperty("UserProvider",UserProvider::getInstance());
    engine.rootContext()->setContextProperty("SettingsHelper",SettingsHelper::getInstance());
    qmlRegisterType<IMCallback>("IM", 1, 0, "IMCallback");
    qmlRegisterType<MessageListModel>("IM", 1, 0, "MessageListModel");
    qmlRegisterType<SessionListModel>("IM", 1, 0, "SessionListModel");
    qmlRegisterType<ContactListModel>("IM", 1, 0, "ContactListModel");
    qmlRegisterType<SessionModel>("IM", 1, 0, "SessionModel");
    qmlRegisterType<ImageModel>("IM", 1, 0, "ImageModel");
    qmlRegisterType<UserModel>("IM", 1, 0, "UserModel");
    qmlRegisterType<CircularReveal>("IM", 1, 0, "CircularReveal");
    const QUrl url(QStringLiteral("qrc:/App.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);
    const int exec = QGuiApplication::exec();
    if (exec == 931) {
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }
    return exec;
}
