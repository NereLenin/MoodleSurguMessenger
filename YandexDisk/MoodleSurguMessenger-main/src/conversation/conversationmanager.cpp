#include "conversationmanager.h"

ConversationMananger::ConversationMananger(QObject *parent)
    : QObject{parent}
{

}

QList<Conversation *> &ConversationMananger::getConversations()
{
    return conversationList;
}



QVariant &ConversationMananger::getModelConversations()
{
    modelList.clear();
    conversationsModel.clear();

    for(int i=0;i<conversationList.size();i++)
        modelList.append(conversationList[i]);

    conversationsModel.setValue(modelList);

    return conversationsModel;
}

QVariant &ConversationMananger::getModelMessagesOfConversation(int ConversationIndex)
{

    modelList.clear();
    messagesModel.clear();

    if(ConversationIndex<0||ConversationIndex>=conversationList.size()||conversationList.size() == 0)
    {
        qDebug() << "wrong index or empty convList\n";
        return messagesModel;
    }

    //inverse List and add to QObject
    for(int i=conversationList[ConversationIndex]->MessagesSize()-1;i>=0;i--)
        modelList.append((*conversationList[ConversationIndex])[i]);

    messagesModel.setValue(modelList);
    return messagesModel;
}

QVariant &ConversationMananger::getModelMessagesOfConversation(Conversation *conversation)
{
    return getModelMessagesOfConversation(conversationList.indexOf(conversation));
}

Conversation *ConversationMananger::getConversationById(int id)
{

    for(int i=0;i<conversationList.size();i++)
        if(conversationList[i]->GetId() == id)
            return conversationList[i];

    return nullptr;
}

Conversation *ConversationMananger::operator[](int index)
{

    if(index >=0&& index < conversationList.size()) return conversationList[index];
    else return nullptr;
}


int ConversationMananger::size()
{
    return conversationList.size();
}
