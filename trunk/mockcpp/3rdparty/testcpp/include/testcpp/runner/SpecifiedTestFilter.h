#ifndef __TESTCPP_SPECIFIED_TEST_FILTER_H
#define __TESTCPP_SPECIFIED_TEST_FILTER_H

#include <string>

#include <testcpp/testcpp.h>
#include <testcpp/runner/TestFilter.h>

TESTCPP_NS_START


////////////////////////////////////////////////////
struct SpecifiedTestFilter 
   : public TestFilter
{
   SpecifiedTestFilter(const std::string& fixtureName, const std::string& caseName);

   bool isFixtureMatch(const TestFixtureInfoReader* fixture) const;
   bool isCaseMatch(const TestCaseInfoReader* testcase) const;

private:
   std::string fixtureName;
   std::string caseName;
};

////////////////////////////////////////////////////

TESTCPP_NS_END

#endif

