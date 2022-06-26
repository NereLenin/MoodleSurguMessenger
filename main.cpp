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
    QList <Member*> members;

    MoodleNetworkManager nm;
    ConversationMananger convs;

    nm.SetLogin("vladislavyakubchick");
    nm.SetPassword("RmTeERuL");
    nm.Authorisation();

    nm.ReadCourses(courses);

    QByteArray pars;

    QString GetMessagiesUrl = QString("https://moodle.surgu.ru/lib/ajax/service.php?sesskey=%1&info=core_course_get_recent_courses").arg(nm.current_account.GetSessKey());
    //QString GetMessagiesPostData = QString(("[{\"index\":0,\"methodname\":\"core_enrol_search_users\",\"args\":{\"userid\":%1,\"courseid\":%2}}]")).arg(nm.current_account.GetId()).arg("4130");
    QString GetMessagiesPostData = QString(("[{\"index\":0,\"methodname\":\"core_course_get_recent_courses\",\"args\":{\"userid\":\"%1\",\"limit\":0}}]")).arg(nm.current_account.GetId());

    if(!nm.CreatePostWaitiedResponse(GetMessagiesUrl,GetMessagiesPostData,&pars))
    {
        qDebug() << "Ошибка получения диалогов. Проверте подключение к сети";
    } else

    qDebug() << pars;

    nm.ReadJson(pars,courses);

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
