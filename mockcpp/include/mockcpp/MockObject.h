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

#ifndef __MOCKCPP_MOCK_OBJECT_H
#define __MOCKCPP_MOCK_OBJECT_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/TypeString.h>
#include <mockcpp/MockObjectBase.h>
#include <mockcpp/DelegatedMethodGetter.h>
#include <mockcpp/InterfaceInfo.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////////////
template <typename Interface>
struct MockObject : public MockObjectBase
{
	MockObject()
		: MockObjectBase(TypeString<Interface>::value()
      , getNumberOfVtbls<Interface>()
      , typeid(Interface))
	{}

   ~MockObject()
   {
   }

   operator Interface* ()
   {
      return (Interface*)toPointerToInterface();
   }

	template <typename Method>
   InvocationMockBuilderGetter method(Method m, const char* name = 0)
   {
     std::string methodName(name == 0? TypeString<Method>::value():name);

     unsigned int vptrIndex = getVptrIndex(m);
     unsigned int vtblIndex = getVtblIndex(m);
     void * addr = getDelegatedFunction<Interface, Method>(vptrIndex, vtblIndex, m);

     return createInvocationMockerBuilderGetter(
               methodName, addr, vptrIndex, vtblIndex);
	}

//////////////////////////////////////////////////////////////
// Template method we have to make it visible
private:

   template <typename Method>
   void* getAddrOfDelegatedMethod(Method m)
   { return getAddrOfMethod(m); }

   template <typename Method>
   unsigned int getVptrIndex(Method m)
   { return getDeltaOfMethod<Interface, Method>(m); }

   template <typename Method>
   unsigned int getVtblIndex(Method m)
   { return getIndexOfMethod<Interface, Method>(m); }

};

MOCKCPP_NS_END

#endif

