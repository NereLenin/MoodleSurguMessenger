#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "appengine.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
//MoodleNetworkManager/MoodleNetworkManager.qml
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/MoodleNetworkManager.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    /*
    MoodleNetworkManager nm;
    ConversationMananger conv;

    nm.SetLogin("vladislavyakubchick");nm.SetPassword("RmTeERuL");
    nm.Authorisation();

    nm.ReadExistConversations(conv.getConversations());

    for(int i=0;i<conv.getConversations().size();i++)
    {
        qDebug() << "id: " << conv[i]->GetId() << " name:"<< conv[i]->getFullNameFirstMember() << "\n";
    }
    */

    MyAppEngine appEngine(&engine);
    appEngine.checkConnection();




/*
    QObject *stack = engine.rootObjects()[0]->findChild<QObject*>("mainStack");
    if(stack)
    {
        qDebug() << "we found it \n";
        QString msg = "DialogLoad.ui.qml";
        QMetaObject::invokeMethod(stack, "pushPage",Q_ARG(QString, msg));
        //QMetaObject::invokeMethod(stack,"myQmlFunction",)
    }

*/

    return app.exec();
}
