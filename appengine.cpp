#include "appengine.h"


MyAppEngine::MyAppEngine(QQmlApplicationEngine *engine, QObject *parent)
    : QObject{parent}
{
    this->rootContext = engine->rootContext();
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


    networkManager.ReadConversation(*openConv);
    rootContext->setContextProperty("messagesModel", conversations.getModelMessagesOfConversation(openConv));
    pushPage("Conversation.qml");

/*
   if(openConv->MessagesSize() <= 1)
    {
         }
    else
    {
       networkManager.UpdateConversation(*openConv);
       rootContext->setContextProperty("messagesModel", conversations.getModelMessagesOfConversation(openConv));
       pushPage("Conversation.qml");    }

    //popPage();
    //clearStack();
*/

}

void MyAppEngine::openConversations()
{
    //popPage();
    //clearStack();

    if(conversations.size()==0)
    {
        networkManager.ReadExistConversations(conversations.getConversations());
    }


    rootContext->setContextProperty("conversationsModel", conversations.getModelConversations());
    rootContext->setContextProperty("currentConversation", &nullconv);

    pushPage("ConversationsList.qml");
}

void MyAppEngine::searchMessage(int convID, QString text)
{
    rootContext->setContextProperty("messagesModel", conversations.searchMessage(convID,text));
}

void MyAppEngine::searchConvs(QString text)
{
    rootContext->setContextProperty("conversationsModel", conversations.searchConversations(text));
}

bool MyAppEngine::updateConv(int convID)
{
    Conversation* openConv = conversations.getConversationById(convID);
    if(openConv==nullptr)
    {
        qDebug() << "Can't find conv to open with id " << convID << "\n";
        return false;
    }

    rootContext->setContextProperty("currentConversation", openConv);


    //networkManager.ReadConversation(*openConv);
    rootContext->setContextProperty("messagesModel", conversations.getModelMessagesOfConversation(openConv));

    return true;
}

void MyAppEngine::updateConvs()
{
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
    pushPage("DialogLoad.qml");
    networkManager.ReadExistConversations(conversations.getConversations());
    for(int i=0;i<conversations.size()/2;i++)
        networkManager.ReadConversation(*conversations[i]);


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

void MyAppEngine::reconnecting()
{
    isConnection();
    clearStack();
    pushPage("Authorization.qml");
    isConnection();
}

