#include "appengine.h"


MyAppEngine::MyAppEngine(QQmlContext *rootContext,QQmlApplicationEngine *engine, QObject *parent)
    : QObject{parent}
{
    this->rootContext = rootContext;
    this->engine = engine;


    //networkManager.SetLogin("vladislavyakubchick");
    //networkManager.SetPassword("RmTeERuL");

    //networkManager.Authorisation();
    nullconv.SetId(0);

    rootContext->setContextProperty("appEngine",this);

    stack = engine->rootObjects()[0]->findChild<QObject*>("mainStack");
}

QString MyAppEngine::getMyFullName()
{
    return networkManager.current_account.GetFullName();
}

void MyAppEngine::pushPage(QString pageUrl)
{
    if(stack)
    {
        QMetaObject::invokeMethod(stack, "pushPage",Q_ARG(QString, pageUrl));
    }
}

void MyAppEngine::popPage()
{
    if(stack)
    {
        QMetaObject::invokeMethod(stack, "pop");
    }
}

void MyAppEngine::clearStack()
{
    if(stack)
    {
        QMetaObject::invokeMethod(stack, "clear");
    }
}
void MyAppEngine::openConversation(int id)
{
    Conversation* openConv = conversations.getConversationById(id);
    if(openConv==nullptr)
    {
        qDebug() << "Can't find conv to open with id " << id << "\n";
        return;
    }

    rootContext->setContextProperty("currentConversation", openConv);

    pushPage("Conversation.qml");

    networkManager.ReadConversation(*openConv);
    rootContext->setContextProperty("messagesModel", conversations.getModelMessagesOfConversation(openConv));

    //popPage();
    //clearStack();

}

void MyAppEngine::openConversations()
{
    //popPage();
    //clearStack();
    pushPage("ConversationsList.qml");
    networkManager.ReadExistConversations(conversations.getConversations());
    rootContext->setContextProperty("conversationsModel", conversations.getModelConversations());
    rootContext->setContextProperty("currentConversation", &nullconv);

}

void MyAppEngine::sendMessage(int convID, QString text)
{
    Conversation* sendConv = conversations.getConversationById(convID);
    if(sendConv==nullptr)
    {
        qDebug() << "Can't find conv to open with id " << convID << "\n";
        return;
    }
    qDebug() << "Text msg:" <<  text  << "\n";
    networkManager.SendMessage(*sendConv,text);
}


void MyAppEngine::checkConnection()
{
    clearStack();
    pushPage("CheckConnection.qml");
}

void MyAppEngine::startAuthorisation()
{
    clearStack();
    pushPage("Authorization.qml");
}

void MyAppEngine::startLoadDialog()
{
    //popPage("");
    networkManager.ReadExistConversations(conversations.getConversations());
    pushPage("DialogLoad.qml");
}

bool MyAppEngine::authorisation(QString login, QString password)
{
    networkManager.SetLogin(login);
    networkManager.SetPassword(password);
    networkManager.Authorisation();

    return networkManager.isLogIn();
}

bool MyAppEngine::isConnection()
{
    return networkManager.isNetworkAccessible();
}

