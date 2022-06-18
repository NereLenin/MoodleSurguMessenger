#include "src/profiles/profile.h"

Profile::Profile(QObject *parent)
    : QObject{parent}
{
    ID=0;
}

//--------set
void Profile::SetId(int ID)
{
    this->ID = ID;
}

void Profile::SetFullName(QString FullName)
{
    this->FullName = FullName;
}

void Profile::SetProfileURL(QString ProfileURL)
{
    this->ProfileURL = ProfileURL;
}

void Profile::SetAvatarURL(QString AvatarURL)
{
    this->avatarURL = AvatarURL;
}

//---------get
int Profile::GetId() const
{
    return ID;
}


const QString& Profile::GetFullName() const
{
    return FullName;
}


const QString& Profile::GetProfileURL() const
{
    return ProfileURL;
}


const QString &Profile::GetAvatarURL() const
{
    return avatarURL;
}


void Profile::AddConversation(Conversation *Conv)
{
    InConversations.append(Conv);
}

Conversation* Profile::GetConversationFromList(int index)
{
    if(index >=0 && index < InConversations.size())
        return (InConversations[index]);
    else return nullptr;
}

int Profile::ConversationsSize()
{
    return InConversations.size();
}

