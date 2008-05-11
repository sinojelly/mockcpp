
#include <InvokedOnce.h>
#include <Asserter.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////
InvokedOnce::InvokedOnce()
{
}

///////////////////////////////////////////////////////
bool InvokedOnce::matches(const Invocation& inv) const
{
    return getInvokedTimes() == 0;
}

///////////////////////////////////////////////////////
std::string
InvokedOnce::toString(void) const
{
    return "once()";
}

///////////////////////////////////////////////////////
void InvokedOnce::verify(void)
{
    MOCKCPP_ASSERT_TRUE_MESSAGE(
         "Expected invocation was never invoked!"
         , getInvokedTimes() > 0);
}

MOCKCPP_NS_END


