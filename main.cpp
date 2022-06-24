#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSslSocket>
#include "appengine.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
//MoodleNetworkManager/MoodleNetworkManager.qml
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/MoodleSurguMessenger.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);


    QString result = "false";

    if(QSslSocket::supportsSsl()) result = "true";
    qDebug() << "Device supports OpenSSL: " << QSslSocket::supportsSsl();

    engine.rootContext()->setContextProperty("InetResult",result);

    MyAppEngine appEngine(&engine);
    appEngine.authorisation("vladislavyakubchick","RmTeERuL");
    appEngine.openConversations();
    //appEngine.checkConnection();

    //
    return app.exec();
}
