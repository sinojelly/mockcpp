
#include <InvokedAtLeast.h>
#include <Asserter.h>
#include <Formatter.h>

MOCKCPP_NS_START

InvokedAtLeast::InvokedAtLeast(const unsigned int times)
	: lowLimit(times)
{
}

///////////////////////////////////////////////////////
bool InvokedAtLeast::matches(void) const
{
	return true;
}

///////////////////////////////////////////////////////
std::string
InvokedAtLeast::describeSelf(void) const
{
	 std::ostringstream ss;

    ss << ".expects(atLeast(" << lowLimit << "))";

    return ss.str();
}

///////////////////////////////////////////////////////
void InvokedAtLeast::verify(void)
{
    MOCKCPP_ASSERT_TRUE_MESSAGE(
			"Invoked too few times" 
         , invokedTimes >= lowLimit);
}

MOCKCPP_NS_END


