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

QVariant &ConversationMananger::searchMessage(int convID, QString searchText)
{


    Conversation *searchInConv = getConversationById(convID);

    if(searchInConv)
    {
        searchList.clear();
        searchModel.clear();


        for(int i=0;i<searchInConv->MessagesSize();i++)
        {
            if(searchInConv->GetMessageFromList(i)->GetText().toLower().contains(searchText.toLower()))
               searchList.append(searchInConv->GetMessageFromList(i));
        }

        searchModel.setValue(searchList);
        return searchModel;
    }
    else
        return messagesModel;
}

QVariant &ConversationMananger::searchConversations(QString searchText)
{
    if(size()>1)
    {
        searchList.clear();
        searchModel.clear();


        for(int i=0;i<size();i++)
        {
            if(conversationList[i]->getFullNameFirstMember().toLower().contains(searchText.toLower()))
               searchList.append(conversationList[i]);
        }

        searchModel.setValue(searchList);
        return searchModel;
    }
    else
        return conversationsModel;
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
