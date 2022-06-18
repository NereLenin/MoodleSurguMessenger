#ifndef APPENGINE_H
#define APPENGINE_H

#include <QObject>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "src/conversation/conversationmanager.h"
#include "src/network/moodlenetworkmanager.h"

class MyAppEngine : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString myFullName READ getMyFullName)

private:
    ConversationMananger conversations;
    MoodleNetworkManager networkManager;

    QQmlContext *rootContext;
    QQmlApplicationEngine *engine;
    Conversation nullconv;

    QObject *stack;

    void pushPage(QString pageUrl);
    void popPage();
    void clearStack();

public:
    explicit MyAppEngine(QQmlContext *rootContext,QQmlApplicationEngine *engine, QObject *parent = nullptr);

    QString getMyFullName();
public slots:
    void openConversation(int id);
    void openConversations();

    void sendMessage(int convID, QString text);

    void checkConnection();

    void startAuthorisation();
    void startLoadDialog();

    bool authorisation(QString login, QString password);



    bool isConnection();

signals:

};

#endif // APPENGINE_H
