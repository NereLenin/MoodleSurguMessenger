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


    QList <Course*> courses;

    MoodleNetworkManager nm;
    ConversationMananger convs;

    nm.SetLogin("vladislavyakubchick");
    nm.SetPassword("RmTeERuL");
    nm.Authorisation();

    nm.ReadCourses(courses);

    qDebug() << courses.size();

    for(int i=0;i<courses.size();i++)
        qDebug() << "\n" << courses[i]->getFullName() << " : " << courses[i]->getId() << " : " << courses[i]->getURL();



    /*
    nm.ReadExistConversations(convs.getConversations());

    qDebug() << convs[2]->getFullNameFirstMember() << ":" << convs[2]->GetId();
    qDebug() << convs[2]->GetMember(0)->GetFullName();
    qDebug() << convs[2]->GetMember(0)->GetAvatarURL();
    */


    //engine.load(url);

    //MyAppEngine appEngine(&engine);
    //appEngine.authorisation("vladislavyakubchick","RmTeERuL");
    //appEngine.openConversations();
    //appEngine.checkConnection();

    return app.exec();
}
