#ifndef PROFILE_H
#define PROFILE_H
#include <QString>
#include <QList>
#include <QObject>

class Conversation;
class Profile: protected QObject
{
    Q_OBJECT
protected:
    int ID;
    QString FullName;//maybe name, surname, father'sname?
    QString ProfileURL;
    QString avatarURL;
    QList<Conversation*> InConversations;
public:
    explicit Profile(QObject *parent = nullptr);
    void SetId(int ID);
    void SetFullName(QString FullName);
    void SetProfileURL(QString ProfileURL);
    void SetAvatarURL(QString AvatarURL);

    int GetId() const;
    const QString& GetFullName() const;
    const QString& GetProfileURL() const;
    const QString& GetAvatarURL() const;

    void AddConversation(Conversation *Conv);
    Conversation *GetConversationFromList(int index);

    int ConversationsSize();
};

#endif // PROFILE_H
