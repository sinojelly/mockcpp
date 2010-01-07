#ifndef __TESTCPP_WILDCARD_TEST_FILTER_H
#define __TESTCPP_WILDCARD_TEST_FILTER_H

#include <testcpp/testcpp.h>
#include <testcpp/runner/TestFilter.h>

TESTCPP_NS_START


////////////////////////////////////////////////////
struct WildcardTestFilter 
   : public TestFilter
{
   bool isFixtureMatch(const TestFixtureInfoReader* fixture) const;
   bool isCaseMatch(const TestCaseInfoReader* testcase) const;
};

////////////////////////////////////////////////////

TESTCPP_NS_END

#endif

