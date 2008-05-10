
#include <InvocationRecorder.h>
#include <Asserter.h>
#include <Formatter.h>

MOCKCPP_NS_START

InvocationRecorder::InvocationRecorder()
      : invokedTimes(0)
{}

bool InvocationRecorder::hasBeenInvoked(void) const
{
    return invokedTimes > 0;
}

void InvocationRecorder::increaseInvoked(void) 
{
    invokedTimes++;
}

std::string
InvocationRecorder::toString(void) const
{
    std::ostringstream ss;
    ss << describeSelf() << ".invoked("  << invokedTimes << ")";
    return ss.str();
}

MOCKCPP_NS_END


