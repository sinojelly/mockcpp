
#include <mockcpp.h>

#include <Matcher.h>
#include <TypelessMatcherAdapter.h>
#include <InvokedOnce.h>
#include <InvokedAtLeast.h>
#include <InvokedAtMost.h>
#include <InvokedExactly.h>
#include <TestFailureMatcher.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////////
Matcher* once()
{
	return new TypelessMatcherAdapter(new InvokedOnce);
}

//////////////////////////////////////////////////////////////////
Matcher* exactly(unsigned int times)
{
	return new TypelessMatcherAdapter(new InvokedExactly(times));
}

//////////////////////////////////////////////////////////////////
Matcher* atLeast(unsigned int times)
{
	return new TypelessMatcherAdapter(new InvokedAtLeast(times));
}

//////////////////////////////////////////////////////////////////
Matcher* atMost(unsigned int times)
{
	return new TypelessMatcherAdapter(new InvokedAtMost(times));
}

//////////////////////////////////////////////////////////////////
Matcher* atLeastOnce()
{
	return atLeast(1);
}

//////////////////////////////////////////////////////////////////
Matcher* atMostOnce()
{
	return atMost(1);
}

//////////////////////////////////////////////////////////////////
Matcher* never()
{
   return new TypelessMatcherAdapter(
		new TestFailureMatcher(
				"Invoking an invocation which should never be invoked",
            ".expects(never())"));
}

MOCKCPP_NS_END
