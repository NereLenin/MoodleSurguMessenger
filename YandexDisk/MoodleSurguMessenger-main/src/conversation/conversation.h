#ifndef CONVERSATION_H
#define CONVERSATION_H
#include <src/conversation/message.h>
#include <src/profiles/member.h>

class Conversation : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getFullNameFirstMember)
    Q_PROPERTY(int msgCount READ MessagesSize)
    Q_PROPERTY(QString lastMsgText READ lastMsgText)
    Q_PROPERTY(QString lastMsgTime READ lastMsgTime)
    Q_PROPERTY(int convID READ GetId)


private:
    int Id;

    QList <Member*> Members;
    QList <Message*> Messagies;
public:
    explicit Conversation(QObject *parent = nullptr);

    void SetId(int Id);
    int GetId() const;

    Message *GetMessageFromList(int index);
    Member *GetMember(int index);
    QString getFullNameFirstMember();
    QString lastMsgText();
    QString lastMsgTime();

    int MessagesSize();
    int MembersSize();

    void AddMessage(Message* NewMessage);
    void AddMember(Member* NewMember);

    void ClearAllMessages();
    void ClearAllMembers();

    Message* operator[] (int index);

    friend class MoodleNetworkManager;
};

#endif // CONVERSATION_H
