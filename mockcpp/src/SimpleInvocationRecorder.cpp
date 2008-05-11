
#include <SimpleInvocationRecorder.h>
#include <Asserter.h>
#include <Formatter.h>
#include <Invocation.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////
SimpleInvocationRecorder::SimpleInvocationRecorder()
      : invokedTimes(0)
{
}

//////////////////////////////////////////////////////
void SimpleInvocationRecorder::increaseInvoked(void) 
{
    invokedTimes++;
}

//////////////////////////////////////////////////////
unsigned int SimpleInvocationRecorder::getInvokedTimes(void) const
{
    return invokedTimes;
}

MOCKCPP_NS_END


