#include "src/profiles/member.h"

Member::Member()
{
  isOnline = false;
}

//----------Set
void Member::SetOnline(bool Online)
{
    this->isOnline = Online;
}

//-------------Get
bool Member::GetOnline()
{
    return isOnline;
}
