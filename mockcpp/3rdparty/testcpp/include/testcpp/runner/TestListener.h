
#ifndef __TESTCPP_TEST_LISTENER_H
#define __TESTCPP_TEST_LISTENER_H

#include <testcpp/testcpp.h>

#include <testcpp/runner/TestSuiteResultCollector.h>

TESTCPP_NS_START

struct TestListener
   : public TestSuiteResultCollector
{
   virtual ~TestListener() {}
};

TESTCPP_NS_END

#endif

