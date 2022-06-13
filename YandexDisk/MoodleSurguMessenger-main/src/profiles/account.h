#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <src/profiles/profile.h>

class Account: public Profile
{
private:
    QString Login;
    QString Password;

    QString LoginToken;
    QString SessKey;

    void SetLoginToken(const QString& LoginToken);
    void SetSessKey(const QString& SessKey);
public:
    Account();

    void SetLogin(const QString& Login);
    void SetPassword(const QString& Password);

    const QString& GetLogin();
    const QString& GetPassword();
    const QString& GetLoginToken();
    const QString& GetSessKey();

    friend class MoodleNetworkManager;
};

#endif // ACCOUNT_H
