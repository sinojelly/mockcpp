
#include <InvokedAtMost.h>
#include <Asserter.h>
#include <Formatter.h>

MOCKCPP_NS_START

InvokedAtMost::InvokedAtMost(const unsigned int times)
	: highLimit(times)
{
}

///////////////////////////////////////////////////////
bool InvokedAtMost::matches(void) const
{
	return invokedTimes < highLimit;
}

///////////////////////////////////////////////////////
std::string
InvokedAtMost::describeSelf(void) const
{
	 oss_t oss;

    oss << ".expects(atMost(" << highLimit << "))";

    return oss.str();
}

///////////////////////////////////////////////////////
void InvokedAtMost::verify(void)
{
    MOCKCPP_ASSERT_TRUE_MESSAGE(
			"Invoked too many times" 
         , invokedTimes >= highLimit);
}

MOCKCPP_NS_END


