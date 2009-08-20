#ifndef __TESTCPP_FIXTURE_NAME_ONLY_TEST_FILTER_H
#define __TESTCPP_FIXTURE_NAME_ONLY_TEST_FILTER_H

#include <string>

#include <testcpp/testcpp.h>
#include <testcpp/runner/TestFilter.h>

TESTCPP_NS_START

////////////////////////////////////////////////////
struct FixtureNameOnlyTestFilter 
   : public TestFilter
{
   FixtureNameOnlyTestFilter(const std::string& name);

   bool isFixtureMatch(const TestFixtureInfoReader* fixture) const;
   bool isCaseMatch(const TestCaseInfoReader* testcase) const;

private:

   std::string fixtureName;
};

////////////////////////////////////////////////////

TESTCPP_NS_END

#endif

