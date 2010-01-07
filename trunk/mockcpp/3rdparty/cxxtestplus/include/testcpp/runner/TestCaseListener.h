
#ifndef __TESTCPP_TEST_CASE_LISTENER_H
#define __TESTCPP_TEST_CASE_LISTENER_H

#include <testcpp/testcpp.h>

#include <testcpp/runner/TestCaseResultCollector.h>

TESTCPP_NS_START

struct TestCaseListener
   : public TestCaseResultCollector
{
   virtual ~TestCaseListener() {}
};

TESTCPP_NS_END

#endif

