
#include <InvokedExactly.h>
#include <Asserter.h>
#include <Formatter.h>

MOCKCPP_NS_START

InvokedExactly::InvokedExactly(const unsigned int times)
	: expectedInvokedTimes(times)
{
}

///////////////////////////////////////////////////////
bool InvokedExactly::matches(void) const
{
	return invokedTimes < expectedInvokedTimes;
}

///////////////////////////////////////////////////////
std::string
InvokedExactly::describeSelf(void) const
{
	 oss_t ss;

    ss << ".expects(exactly(" << expectedInvokedTimes << "))";

    return ss.str();
}

///////////////////////////////////////////////////////
void InvokedExactly::verify(void)
{
	 oss_t oss;
   
    MOCKCPP_ASSERT_TRUE_MESSAGE(
			"Expected invocation times and actual invoked time mismatch" 
         , invokedTimes == expectedInvokedTimes );
}

MOCKCPP_NS_END


