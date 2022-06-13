#include "src/conversation/conversation.h"
#include <QList>

Conversation::Conversation(QObject *parent)
    : QObject{parent}
{
}

//----------set func
void Conversation::SetId(int Id)
{
    this->Id = Id;
}
//---------Get func
int Conversation::GetId() const
{
    return Id;
}

Message* Conversation::GetMessageFromList(int index)
{
    if(index>=0 && index < Messagies.size()) return Messagies[index];
    else return nullptr;
}

Member* Conversation::GetMember(int index)
{
    if(index>=0 && index < Members.size()) return Members[index];
    else return nullptr;
}

QString Conversation::getFullNameFirstMember()
{
    for(int i=0;i<MembersSize();i++)
    {
        qDebug() << Members[i]->GetFullName();
    }
    if(Members.size()>0) return Members[0]->GetFullName();
    return "undefinded";

}

QString Conversation::lastMsgText()
{
    if(Messagies.size()>0)
    {
        QString lastMsgText = Messagies[0]->GetText();

        if(lastMsgText.size() > 63)
        {
            lastMsgText = lastMsgText.left(62);
            return lastMsgText.append("...");
        }
        else
        {
            if(lastMsgText.contains("\n"))
            {
              //тут могут быть траблы если текст начинается сразу с \n
              //поправить
              return lastMsgText.left((lastMsgText.indexOf("\n"))).append("...");
            }
            return lastMsgText;
        }
    }

    return "...";
}

QString Conversation::lastMsgTime()
{
    if(Messagies.size()>0) return Messagies[0]->GetTimeCreatedUTC();

    return "00-00-00 00:00";
}


int Conversation::MessagesSize()
{
    return Messagies.size();
}


int Conversation::MembersSize()
{
    return Members.size();
}

//------------List func
void Conversation::AddMessage(Message* NewMessage)
{
    if(NewMessage!=nullptr) Messagies.append(NewMessage);
    //else qDebug() << "nullptr!\n";
}

void Conversation::AddMember(Member* NewMember)
{
    if(NewMember!=nullptr) Members.append(NewMember);
    //else qDebug() << "nullptr!\n";
}


void Conversation::ClearAllMessages()
{
    Messagies.clear();
}

void Conversation::ClearAllMembers()
{
    //хранятся указатели на память, сделать очистку памяти по ним
    Members.clear();
}

Message* Conversation::operator[](int index)
{
    return GetMessageFromList(index);
}
