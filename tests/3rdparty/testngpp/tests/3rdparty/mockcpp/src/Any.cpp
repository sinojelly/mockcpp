/***
   mockcpp is a C/C++ mock framework.
   Copyright [2008] [Darwin Yuan <darwin.yuan@gmail.com>]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
***/

#include <mockcpp/mockcpp.h>

#include <mockcpp/types/Any.h>

MOCKCPP_NS_START

Any::Any() {}

#if 0
Any::Any(const char* value)
   : AnyBase(new ValueHolder<const char*>(value))
{
}
#endif

Any::Any(const Any & other)
   : AnyBase(other.getContent() ? other.getContent()->clone() : 0)
{
}

Any& Any::operator=(const Any & rhs)
{
   Any(rhs).swap(*this);
   return *this;
}

/////////////////////////////////////////////////////////////////
Any& getEmptyAny()
{
    return const_cast<Any&>(EmptyAny);
}

Any& getVoidAny()
{
    return const_cast<Any&>(VoidAny);
}

bool isVoidAny(const Any& val)
{
    return val.type() == VoidAny.type();
}

/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END


