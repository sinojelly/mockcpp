
#ifndef __TESTCPP_TEST_LISTENER_H
#define __TESTCPP_TEST_LISTENER_H

#include <testcpp/testcpp.h>

#include <testcpp/runner/TestResultCollector.h>

TESTCPP_NS_START

struct TestListener
   : public TestResultCollector
{
   virtual ~TestListener() {}
};

TESTCPP_NS_END

#endif

