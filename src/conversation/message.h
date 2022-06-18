#ifndef MESSAGE_H
#define MESSAGE_H

#include <src/profiles/profile.h>
//#include "conversation.h"
#include <QDate>

//class MoodleNetworkManager;

class Message : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString msgId READ GetId NOTIFY idChanged)
    Q_PROPERTY(QString msgContent READ GetText NOTIFY textChanged)
    Q_PROPERTY(QString msgTime READ GetTimeCreatedUTC NOTIFY timeChanged)

    Q_PROPERTY(QString senderName READ GetSenderFullname NOTIFY senderChanged)
    Q_PROPERTY(bool isMsgMine READ getIsMine)
private:
    Profile *sender;
    QString Id;

    int timecreated;
    QDateTime timecreatedUTC;
    QString Text;
    bool isMine;
public:
    explicit Message(Profile *sender=nullptr, QObject *parent = nullptr);

    void SetSender(Profile *sender);

    void SetId(const QString& Id);
    void SetTimeCreated(int TimeCreated);
    void setIsMine(bool isMine);
    void SetText(const QString& Text);

    bool getIsMine();

    const QString& GetId();
    const QString& GetText();
    const QString& GetSenderFullname();

    int GetTimeCreated();
    QString GetTimeCreatedUTC();
    const Profile* Sender() const;

    friend class MoodleNetworkManager;
signals:
    void idChanged();
    void textChanged();
    void timeChanged();
    void senderChanged();
};

#endif // MESSAGE_H
