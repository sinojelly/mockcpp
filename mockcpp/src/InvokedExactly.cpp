
#include <InvokedExactly.h>
#include <Asserter.h>
#include <Formatter.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////////
InvokedExactly::InvokedExactly(const unsigned int times)
   : expectedInvokedTimes(times)
{
}

/////////////////////////////////////////////////////////
bool InvokedExactly::matches(const Invocation& inv) const
{
	return getInvokedTimes() < expectedInvokedTimes;
}

/////////////////////////////////////////////////////////
std::string
InvokedExactly::toString(void) const
{
	 oss_t ss;

    ss << "exactly(" << expectedInvokedTimes << ")";

    return ss.str();
}

/////////////////////////////////////////////////////////
void InvokedExactly::verify(void)
{
	 oss_t oss;
   
    MOCKCPP_ASSERT_TRUE_MESSAGE(
			"Expected invocation times and actual invoked time mismatch" 
         , getInvokedTimes() == expectedInvokedTimes );
}

MOCKCPP_NS_END


