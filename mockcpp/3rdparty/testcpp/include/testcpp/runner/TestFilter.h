#ifndef __TESTCPP_TEST_FILTER_H
#define __TESTCPP_TEST_FILTER_H

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestFixtureInfoReader;
struct TestCaseInfoReader;

////////////////////////////////////////////////////
struct TestFilter
{
   virtual bool isFixtureMatch(const TestFixtureInfoReader* fixture) const = 0;
   virtual bool isCaseMatch(const TestCaseInfoReader* testcase) const = 0;

   virtual ~TestFilter() {}
};

////////////////////////////////////////////////////

TESTCPP_NS_END

#endif

