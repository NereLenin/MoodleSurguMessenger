#include "src/conversation/message.h"

Message::Message(Profile *sender, QObject *parent)
    : QObject{parent}
{
    this->sender = sender;
    isMine = false;
}


///------------Set func--------------

void Message::SetSender(Profile *sender)
{
    if(sender!=nullptr && sender != this->sender)
    {
        emit senderChanged();
        this->sender = sender;
    }
}

void Message::SetId(const QString& Id)
{
    if(this->Id!=Id)
    {
        this->Id = Id;
        emit idChanged();
    }

}

void Message::SetText(const QString& Text)
{
    if(this->Text!=Text)
    {
        this->Text = Text;
        emit textChanged();
    }
}


bool Message::getIsMine()
{
    return isMine;
}


void Message::SetTimeCreated(int TimeCreated)
{
    if(this->timecreated!=TimeCreated)
    {
        timecreated = TimeCreated;
        timecreatedUTC.setSecsSinceEpoch(TimeCreated);
        emit timeChanged();
    }

}

void Message::setIsMine(bool isMine)
{
    this->isMine = isMine;
}


///------------Get func--------------
QString const& Message::GetId()
{
    return Id;
}

QString const& Message::GetText()
{
    return Text;
}

const QString &Message::GetSenderFullname()
{
    if(sender!=nullptr)
        return sender->GetFullName();
    else
    {
        QString *emptysender = new QString("undefined sender");
        return *emptysender;
    }
}

int Message::GetTimeCreated()
{
    return timecreated;
}

QString Message::GetTimeCreatedUTC()
{
    return timecreatedUTC.toString("dd.MM.yyyy hh:mm");
}

const Profile* Message::Sender() const
{
    return sender;
}
