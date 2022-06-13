#ifndef MEMBER_H
#define MEMBER_H
#include <src/profiles/profile.h>

class Member : public Profile
{
private:
    bool isOnline;
public:
    Member();

    void SetOnline(bool Online);
    bool GetOnline();
};

#endif // MEMBER_H
