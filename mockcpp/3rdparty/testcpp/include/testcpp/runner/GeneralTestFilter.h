#ifndef __TESTCPP_GENERAL_TEST_FILTER_H
#define __TESTCPP_GENERAL_TEST_FILTER_H

#include <testcpp/testcpp.h>
#include <testcpp/runner/TestFilter.h>

TESTCPP_NS_START

struct NameMatcher;
struct GeneralTestFilterImpl;

////////////////////////////////////////////////////
struct GeneralTestFilter 
   : public TestFilter
{
   GeneralTestFilter(NameMatcher* fixtureMatcher, NameMatcher* caseMatcher);
   ~GeneralTestFilter();

   bool isFixtureMatch(const TestFixtureInfoReader* fixture) const;
   bool isCaseMatch(const TestCaseInfoReader* testcase) const;

private:
   GeneralTestFilterImpl * This;
};

////////////////////////////////////////////////////

TESTCPP_NS_END

#endif

