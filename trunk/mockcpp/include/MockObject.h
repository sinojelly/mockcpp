
#ifndef __MOCKCPP_MOCK_OBJECT_H
#define __MOCKCPP_MOCK_OBJECT_H

#include <mockcpp.h>
#include <TypeString.h>
#include <MockObjectBase.h>
#include <DelegatedMethodGetter.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////////////
template <typename Interface>
unsigned int getNumberOfVtbls()
{
	return sizeof(Interface)/sizeof(void*);
}

////////////////////////////////////////////////////////////////
template <typename Interface>
struct MockObject : public MockObjectBase
{
	MockObject()
		: MockObjectBase(TypeString<Interface>::value()
      , getNumberOfVtbls<Interface>())
	{}

   ~MockObject()
   {
      verify();
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

