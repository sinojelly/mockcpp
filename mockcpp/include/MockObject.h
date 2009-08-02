
#ifndef __MOCKCPP_MOCK_OBJECT_H
#define __MOCKCPP_MOCK_OBJECT_H

#include <mockcpp.h>
#include <TypeString.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////////////
struct MockObjectBase : public InvocationMockerNamespace
{
   MockObjectBase(std::string name);
};

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
		: MockObjectBase(TypeString<Interface>::value(Interface))
	{}

	template <typename Method>
   InvocationMockBuilderGetter& method(Method m)
   {
	}
};

MOCKCPP_NS_END

#endif

