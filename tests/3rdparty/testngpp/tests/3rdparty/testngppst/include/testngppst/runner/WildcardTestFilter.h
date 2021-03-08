#ifndef __TESTNGPPST_WILDCARD_TEST_FILTER_H
#define __TESTNGPPST_WILDCARD_TEST_FILTER_H

#include <testngppst/testngppst.h>
#include <testngppst/runner/TestFilter.h>

TESTNGPPST_NS_START


////////////////////////////////////////////////////
struct WildcardTestFilter 
   : public TestFilter
{
   bool isFixtureMatch(const TestFixtureInfoReader* fixture) const;
   bool isCaseMatch(const TestCase* testcase) const;
};

////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif

