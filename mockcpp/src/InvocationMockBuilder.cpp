
#include <InvocationMockBuilder.h>
#include <InvocationMocker.h>

MOCKCPP_NS_START

InvocationMockBuilder::InvocationMockBuilder(InvocationMocker* mocker)
	: invocationMocker(mocker)
{}

InvocationMocker*
InvocationMockBuilder::getMocker() const
{
    return invocationMocker;
}

MOCKCPP_NS_END


