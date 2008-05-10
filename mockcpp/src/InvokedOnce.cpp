
#include <InvokedOnce.h>
#include <Asserter.h>

MOCKCPP_NS_START

InvokedOnce::InvokedOnce() {}

///////////////////////////////////////////////////////
bool InvokedOnce::matches(void) const
{
    return invokedTimes == 0;
}

///////////////////////////////////////////////////////
std::string
InvokedOnce::describeSelf(void) const
{
    return ".expects(once())";
}

///////////////////////////////////////////////////////
void InvokedOnce::verify(void)
{
    MOCKCPP_ASSERT_TRUE_MESSAGE(
         "Expected invocation was never invoked!"
         , hasBeenInvoked());
}

MOCKCPP_NS_END


