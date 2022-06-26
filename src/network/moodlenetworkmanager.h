#ifndef MOODLENETWORKMANAGER_H
#define MOODLENETWORKMANAGER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkCookieJar>
#include <QtNetwork/QNetworkReply>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QJsonParseError>

#include <QTimer>
#include <QEventLoop>
#include <QRegularExpression>


#include <src/conversation/conversation.h>
#include <src/profiles/account.h>
#include <iostream>
#include "src/courses/course.h"

//pars
bool ParsString(QString RegExp,QByteArray StringForPars,QString& result,int from=0);

class MoodleNetworkManager: protected QObject
{
    Q_OBJECT
private:

    //network
    QNetworkAccessManager manager;// rename network manager
    QNetworkCookieJar cookieJar;
    QNetworkRequest request;
    QUrl CurrentUrl;


    QTimer ResponseTimer;

    QEventLoop ResponseLoop;

    bool isGoodAuthorisation;

public://private
    void ReadJsonConversation(QJsonValue conv,Conversation &RewritedConv,bool parseMembers=true);
    void ReadJsonCourse(QJsonValue course, Course &newCourse);
    bool ReadJson(const QByteArray &pars,QList<Conversation*> &ConversationToRead);
    bool ReadJson(const QByteArray &pars,Conversation& WriteTo);
    bool ReadJson(const QByteArray &pars,QList<Course*> &courses);

public:
    bool CreateGetWaitiedResponse(QString url, QByteArray *GetReply=nullptr);
    bool CreatePostWaitiedResponse(QString url,QString data, QByteArray *PostReply=nullptr);
    bool CreatePostWaitiedResponse(QString url, QByteArray data,QByteArray *PostReply);
//private ^
    explicit MoodleNetworkManager(QObject *parent=nullptr);
    Account current_account;

    void SetLogin(const QString& Login);
    void SetPassword(const QString& Password);

    bool isNetworkAccessible();
    bool isLogIn();

    void Authorisation();

    void ReadExistConversations(QList<Conversation*> &ConversationToRead);
    void ReadCourses(QList<Course*> &courses);

    void ReadConversation(Conversation& WriteTo, int time=0, bool clear=true);

    void UpdateConversation(Conversation& WriteTo);

    void SendMessage(Conversation& Addressee, QString Text);
    void DeleteMessage(Message& DeletedMessage);
    void DeleteMessage(int MessageId);

    void LogOut();
};

#endif // MOODLENETWORKMANAGER_H
