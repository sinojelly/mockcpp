#ifndef __TESTCPP_TEST_CASE_FILTER_H
#define __TESTCPP_TEST_CASE_FILTER_H

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestCaseInfoReader;

////////////////////////////////////////////////////
struct TestCaseFilter
{
   virtual bool isCaseMatch(const TestCaseInfoReader* testcase) const = 0;

   virtual ~TestCaseFilter() {}
};

////////////////////////////////////////////////////

TESTCPP_NS_END

#endif

