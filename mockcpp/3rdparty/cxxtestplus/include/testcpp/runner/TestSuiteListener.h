
#ifndef __TESTCPP_TEST_SUITE_LISTENER_H
#define __TESTCPP_TEST_SUITE_LISTENER_H

#include <testcpp/testcpp.h>

#include <testcpp/runner/TestSuiteResultCollector.h>

TESTCPP_NS_START

struct TestSuiteListener
   : public TestSuiteResultCollector
{
   virtual ~TestSuiteListener() {}
};

TESTCPP_NS_END

#endif

