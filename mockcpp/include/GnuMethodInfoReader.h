#ifndef __MOCKCPP_GNU_METHOD_INFO_READER_H
#define __MOCKCPP_GNU_METHOD_INFO_READER_H

#include <mockcpp.h>

#include <MethodTypeTraits.h>
#include <Asserter.h>
#include <TypeString.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
struct GnuMethodDescription
{
   union {
	  void* addr;
     int index;
   }u;
 
   int delta;
};

///////////////////////////////////////////////////////////
template <typename Method>
union MethodDescriptionUnion
{
    GnuMethodDescription desc;
    Method method;
};

///////////////////////////////////////////////////////////
template <typename Method>
void* getAddrOfMethod(Method input)
{
	MethodDescriptionUnion<Method> m;
	m.method = input;

   oss_t oss;
   oss << "Method address should be even, please make sure the method ",
       << getDemangledName(typeid(Method)) << " is not an virtual method";
 
	MOCKCPP_ASSERT_TRUE_MESSAGE(
		oss.str(),
	   !(m.desc.u.index%2));


   return m.desc.u.addr;
}

///////////////////////////////////////////////////////////
template <class C, typename Method>
GnuMethodDescription getGnuDescOfVirtualMethod(Method input)
{
   typedef typename MethodTypeTraits<C, Method>::MethodType ExpectedMethodType; 
	MethodDescriptionUnion<ExpectedMethodType> m;
	m.method = input;

   oss_t oss;
   oss << "Virtual method address should be odd, please make sure the method ",
       << getDemangledName(typeid(Method)) << " is an virtual method";
 
	MOCKCPP_ASSERT_TRUE_MESSAGE(
		oss.str(),
	   (m.desc.u.index%2));

	return m.desc;
}

///////////////////////////////////////////////////////////
template <class C, typename Method>
int getIndexOfMethod(Method method)
{
   return (getGnuDescOfVirtualMethod(method).u.index - 1)/sizeof(void*);
}

///////////////////////////////////////////////////////////
template <class C, typename Method>
int getDeltaOfMethod(Method input)
{
   return getGnuDescOfVirtualMethod(method).delta/sizeof(void*);
}
///////////////////////////////////////////////////////////

MOCKCPP_NS_END

#endif

