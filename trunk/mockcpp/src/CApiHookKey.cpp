/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

#include <mockcpp/CApiHookKey.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
CApiHookKey::CApiHookKey(const void* api, const void* stub)
   : apiAddress(api)
{
   hook = new CApiHook((CApiHook::Address)api, (CApiHook::Address)stub);
}

///////////////////////////////////////////////////////////
CApiHookKey::CApiHookKey(const void* api)
   : apiAddress(api), hook(0)
{
}
////////////////////////////////////////////////////////////
CApiHookKey::~CApiHookKey()
{
   if(hook != 0)
      delete hook;
}   

////////////////////////////////////////////////////////////
bool CApiHookKey::equals(
      const ChainableMockMethodKey* const rhs) const
{
    if(rhs == 0)
    {
       return false;
    }

    if(this == rhs)
    {
       return true;
    }

    CApiHookKey* key = \
          dynamic_cast<CApiHookKey*> \
             (const_cast<ChainableMockMethodKey*>(rhs));
    if(key == 0)
    {
       return 0;
    }
     
    return key->getApiAddress() == this->getApiAddress();
}

///////////////////////////////////////////////////////////
const void* CApiHookKey::getApiAddress() const
{
   return apiAddress;
}

MOCKCPP_NS_END
