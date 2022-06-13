#include "src/profiles/account.h"

Account::Account()
{

}
//-----------set func
void Account::SetLogin(const QString &Login)
{
    this->Login = Login;
}

void Account::SetPassword(const QString &Password)
{
    this->Password = Password;
}

void Account::SetLoginToken(const QString &LoginToken)
{
    this->LoginToken = LoginToken;
}

void Account::SetSessKey(const QString &SessKey)
{
    this->SessKey = SessKey;
}


//---------------------get func
const QString& Account::GetLogin()
{
    return Login;
}

const QString& Account::GetPassword()
{
    return Password;
}

const QString& Account::GetLoginToken()
{
    return LoginToken;
}

const QString& Account::GetSessKey()
{
    return SessKey;
}


