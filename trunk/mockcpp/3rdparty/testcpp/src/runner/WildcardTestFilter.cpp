
#include <testcpp/runner/TestFilter.h>
#include <testcpp/runner/WildcardTestFilter.h>

TESTCPP_NS_START

////////////////////////////////////////////////////////
bool WildcardTestFilter::
isFixtureMatch(const TestFixtureInfoReader* fixture) const
{
   return true;
}

////////////////////////////////////////////////////
bool WildcardTestFilter::
isCaseMatch(const TestCaseInfoReader* testcase) const
{
   return true;
}

////////////////////////////////////////////////////////

TESTCPP_NS_END
