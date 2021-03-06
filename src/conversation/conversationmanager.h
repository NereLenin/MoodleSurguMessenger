#ifndef CONVERSATIONMANAGER_H
#define CONVERSATIONMANAGER_H
#include "src/conversation/conversation.h"
#include <QObject>

class ConversationMananger : public QObject
{
    Q_OBJECT

private:
    QList <Conversation*> conversationList;
    QList <QObject*> modelList;
    QVariant conversationsModel;
    QVariant messagesModel;

    QList<QObject*> searchList;
    QVariant searchModel;

public:
    explicit ConversationMananger(QObject *parent = nullptr);

    QList <Conversation*>& getConversations();
    Conversation* getConversation(int index);
    Conversation* getConversationById(int id);

    QVariant &getModelConversations();

    QVariant &getModelMessagesOfConversation(int ConversationIndex);
    QVariant &getModelMessagesOfConversation(Conversation* conversation);

    QVariant &searchMessage(int convID, QString searchText);
    QVariant &searchConversations(QString searchText);

    Conversation* operator[] (int index);

    int size();
signals:

};

#endif // CONVERSATIONMANAGER_H
