
#ifndef __TESTCPP_TEST_SUITE_RESULT_DISPATCHER_H
#define __TESTCPP_TEST_SUITE_RESULT_DISPATCHER_H

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestSuiteListener;

struct TestSuiteResultDispatcher
{
   virtual void registerTestSuiteListener(TestSuiteListener* listener) = 0;
   virtual TestSuiteListener* unregisterTestSuiteListener(TestSuiteListener* listener) = 0;

   virtual ~TestSuiteResultDispatcher() {}
};

TESTCPP_NS_END

#endif

