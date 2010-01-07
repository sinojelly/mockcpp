#ifndef __TESTCPP_TEST_FILTER_H
#define __TESTCPP_TEST_FILTER_H

#include <testcpp/testcpp.h>
#include <testcpp/runner/TestCaseFilter.h>

TESTCPP_NS_START

struct TestFixtureInfoReader;

////////////////////////////////////////////////////
struct TestFilter : public TestCaseFilter
{
   virtual bool isFixtureMatch(const TestFixtureInfoReader* fixture) const = 0;

   virtual ~TestFilter() {}
};

////////////////////////////////////////////////////

TESTCPP_NS_END

#endif

