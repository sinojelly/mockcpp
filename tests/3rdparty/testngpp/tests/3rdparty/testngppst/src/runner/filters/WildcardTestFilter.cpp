
#include <testngppst/runner/TestFilter.h>
#include <testngppst/runner/WildcardTestFilter.h>

TESTNGPPST_NS_START

////////////////////////////////////////////////////////
bool WildcardTestFilter::
isFixtureMatch(const TestFixtureInfoReader* fixture) const
{
   return true;
}

////////////////////////////////////////////////////
bool WildcardTestFilter::
isCaseMatch(const TestCase* testcase) const
{
   return true;
}

////////////////////////////////////////////////////////

TESTNGPPST_NS_END
