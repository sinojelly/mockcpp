
#include <InvokedAtMost.h>
#include <Asserter.h>
#include <Formatter.h>

MOCKCPP_NS_START

InvokedAtMost::InvokedAtMost(const unsigned int times)
   : highLimit(times)
{
}

///////////////////////////////////////////////////////
bool InvokedAtMost::matches(const Invocation& inv) const
{
	return getInvokedTimes() < highLimit;
}

///////////////////////////////////////////////////////
std::string InvokedAtMost::toString(void) const
{
	 oss_t oss;

    oss << "atMost(" << highLimit << ")";

    return oss.str();
}

///////////////////////////////////////////////////////
void InvokedAtMost::verify(void)
{
    MOCKCPP_ASSERT_TRUE_MESSAGE(
			"Invoked too many times" 
         , getInvokedTimes() >= highLimit);
}

MOCKCPP_NS_END


