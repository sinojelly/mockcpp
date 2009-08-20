#ifndef __TESTCPP_CASE_NAME_ONLY_TEST_FILTER_H
#define __TESTCPP_CASE_NAME_ONLY_TEST_FILTER_H

#include <string>

#include <testcpp/testcpp.h>
#include <testcpp/runner/TestFilter.h>

TESTCPP_NS_START

////////////////////////////////////////////////////
struct CaseNameOnlyTestFilter 
   : public TestFilter
{
   CaseNameOnlyTestFilter(const std::string& name);

   bool isFixtureMatch(const TestFixtureInfoReader* fixture) const;
   bool isCaseMatch(const TestCaseInfoReader* testcase) const;

private:

   std::string caseName;
};

////////////////////////////////////////////////////

TESTCPP_NS_END

#endif

