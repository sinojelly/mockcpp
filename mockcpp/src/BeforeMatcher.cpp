
#include <BeforeMatcher.h>
#include <Namespace.h>
#include <InvocationMocker.h>
#include <Asserter.h>
#include <Invocation.h>
#include <InvocationId.h>
#include <ChainableMockMethodCore.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////
BeforeMatcher::BeforeMatcher(
        InvocationMocker* prev
		)
		: previousCall(prev)
{
}

//////////////////////////////////////////////////////
bool BeforeMatcher::matches(const Invocation& inv) const
{
    return previousCall? !previousCall->hasBeenInvoked() : false;
}

//////////////////////////////////////////////////////
void BeforeMatcher::increaseInvoked(const Invocation& inv)
{
}

//////////////////////////////////////////////////////
std::string BeforeMatcher::toString() const
{
    return "before";
}

//////////////////////////////////////////////////////
bool BeforeMatcher::isComplete(void) const
{
    return previousCall != 0;
}

//////////////////////////////////////////////////////
void BeforeMatcher::setOrderingInvocationMocker(InvocationMocker* mocker)
{
    previousCall = mocker;
}

MOCKCPP_NS_END

